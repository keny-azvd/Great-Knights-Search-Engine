#!/usr/bin/env python3
"""
GK Search Engine - Web Server
Wraps engine_server binary and serves a modern web interface.
"""

import os
import sys
import json
import re
import time
import select
import signal
import threading
import subprocess
from http.server import HTTPServer, BaseHTTPRequestHandler
from urllib.parse import urlparse, parse_qs
from pathlib import Path

PROJECT_DIR = Path(__file__).resolve().parent.parent
ENGINE_PATH = PROJECT_DIR / "engine_server"
PORT = 8080


class SearchEngine:
    def __init__(self):
        self.lock = threading.Lock()
        self.ready = False
        self.process = None
        self.load_time = 0

    def start(self):
        self.process = subprocess.Popen(
            ["stdbuf", "-oL", str(ENGINE_PATH)],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            cwd=str(PROJECT_DIR),
            bufsize=0,
        )

        print("Aguardando engine carregar a trie (pode levar alguns minutos)...")

        while True:
            line = self.process.stdout.readline().decode("utf-8", errors="replace")
            if not line:
                print("Engine encerrou inesperadamente!")
                sys.exit(1)
            line = line.strip()
            if line.startswith("READY"):
                parts = line.split()
                if len(parts) > 1:
                    self.load_time = float(parts[1])
                self.ready = True
                print(f"Engine pronto! Trie carregada em {self.load_time / 1000:.1f}s")
                break

    def search(self, query):
        with self.lock:
            if not self.ready:
                return {"error": "Engine ainda carregando"}

            query = query.strip()
            if not query:
                return {"total": 0, "time_ms": 0, "results": [], "query": ""}

            self.process.stdin.write(f"{query}\n".encode())
            self.process.stdin.flush()

            while True:
                raw = self.process.stdout.readline().decode("utf-8", errors="replace").strip()
                if not raw:
                    continue
                if raw.startswith("{"):
                    try:
                        data = json.loads(raw)
                        data["query"] = query
                        return data
                    except json.JSONDecodeError:
                        return {"error": "Resposta inválida do engine", "raw": raw}

    def get_document(self, doc_id):
        try:
            doc_id = int(doc_id)
        except ValueError:
            return {"error": "ID inválido"}

        number = (doc_id // 10000) * 10000
        filename = PROJECT_DIR / f"aTexts/aDocs_{number}_{number + 10000}.txt"

        if not filename.exists():
            return {"error": "Arquivo de documentos não encontrado"}

        with open(filename, "r", encoding="utf-8", errors="replace") as f:
            is_target = False
            text_lines = []

            for line in f:
                if len(line) >= 21 and line[:21] == "Marked: low fidelity ":
                    if is_target:
                        break
                    rest = line[21:].strip()
                    try:
                        idx = int(rest)
                        if idx == doc_id:
                            is_target = True
                            continue
                    except ValueError:
                        pass
                elif is_target:
                    text_lines.append(line)

        if text_lines:
            return {"text": "".join(text_lines), "id": doc_id}
        return {"error": "Documento não encontrado"}

    def stop(self):
        if self.process:
            try:
                self.process.stdin.write(b"EXIT\n")
                self.process.stdin.flush()
                self.process.wait(timeout=5)
            except Exception:
                self.process.terminate()


engine = SearchEngine()


class RequestHandler(BaseHTTPRequestHandler):
    def log_message(self, format, *args):
        pass

    def _cors(self):
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")

    def _json_response(self, data, status=200):
        body = json.dumps(data, ensure_ascii=False).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self._cors()
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def _serve_file(self, filepath, content_type):
        try:
            with open(filepath, "rb") as f:
                content = f.read()
            self.send_response(200)
            self.send_header("Content-Type", content_type)
            self.send_header("Content-Length", str(len(content)))
            self.end_headers()
            self.wfile.write(content)
        except FileNotFoundError:
            self.send_error(404)

    def do_OPTIONS(self):
        self.send_response(200)
        self._cors()
        self.end_headers()

    def do_GET(self):
        parsed = urlparse(self.path)
        path = parsed.path
        params = parse_qs(parsed.query)

        if path == "/" or path == "/index.html":
            self._serve_file(
                Path(__file__).parent / "index.html", "text/html; charset=utf-8"
            )

        elif path == "/api/search":
            query = params.get("q", [""])[0]
            if not query:
                self._json_response({"error": "Parâmetro 'q' é obrigatório"}, 400)
                return
            result = engine.search(query)
            self._json_response(result)

        elif path == "/api/document":
            doc_id = params.get("id", [""])[0]
            if not doc_id:
                self._json_response({"error": "Parâmetro 'id' é obrigatório"}, 400)
                return
            result = engine.get_document(doc_id)
            self._json_response(result)

        elif path == "/api/status":
            self._json_response(
                {
                    "ready": engine.ready,
                    "load_time_ms": engine.load_time,
                }
            )

        else:
            self.send_error(404)


def main():
    engine.start()

    server = HTTPServer(("0.0.0.0", PORT), RequestHandler)
    print(f"Servidor web rodando em http://localhost:{PORT}")

    def shutdown(sig, frame):
        print("\nEncerrando...")
        engine.stop()
        server.shutdown()

    signal.signal(signal.SIGINT, shutdown)
    signal.signal(signal.SIGTERM, shutdown)

    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        engine.stop()


if __name__ == "__main__":
    main()
