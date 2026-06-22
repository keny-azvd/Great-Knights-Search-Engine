#include "trie.cpp"
#include <chrono>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

string json_escape(const string& s) {
    string r;
    for (char c : s) {
        switch (c) {
            case '"':  r += "\\\""; break;
            case '\\': r += "\\\\"; break;
            case '\n': r += "\\n"; break;
            case '\r': r += "\\r"; break;
            case '\t': r += "\\t"; break;
            default:
                if (c >= 0 && c < 32) {
                    char buf[8];
                    snprintf(buf, sizeof(buf), "\\u%04x", (unsigned char)c);
                    r += buf;
                } else {
                    r += c;
                }
        }
    }
    return r;
}

int main() {
    Trie GKSE;
    auto Start = chrono::high_resolution_clock::now();
    GKSE.Deserialize();
    auto End = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> Tempo = End - Start;

    cout << "READY " << Tempo.count() << endl;
    cout.flush();

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        if (line == "EXIT") break;

        auto t1 = chrono::high_resolution_clock::now();
        vector<Pair> res = GKSE.find(line);
        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> t_search = t2 - t1;

        sort(res.begin(), res.end());

        int limit = min((int)res.size(), 50);

        cout << "{\"total\":" << res.size()
             << ",\"time_ms\":" << t_search.count()
             << ",\"results\":[";

        for (int i = 0; i < limit; i++) {
            if (i > 0) cout << ",";
            string title = json_escape(print_title(res[i][0]));
            cout << "{\"id\":" << res[i][0]
                 << ",\"freq\":" << res[i][1]
                 << ",\"title\":\"" << title << "\"}";
        }
        cout << "]";

        if (res.empty()) {
            stringstream split;
            split << line;
            string word;
            split >> word;
            string extra;
            if (!(split >> extra)) {
                auto st1 = chrono::high_resolution_clock::now();
                vector<str_dt> suggested = GKSE.suggest(word, 2, 25000);
                auto st2 = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> t_sugg = st2 - st1;

                sort(suggested.begin(), suggested.end());

                int slimit = min((int)suggested.size(), 15);
                cout << ",\"suggestions\":[";
                for (int i = 0; i < slimit; i++) {
                    if (i > 0) cout << ",";
                    cout << "{\"word\":\"" << json_escape(suggested[i].str)
                         << "\",\"count\":" << suggested[i].len << "}";
                }
                cout << "],\"suggestion_time_ms\":" << t_sugg.count();
            }
        }

        cout << "}" << endl;
        cout.flush();
    }

    return 0;
}
