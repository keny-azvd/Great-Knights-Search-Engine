#include "lib/server_http.hpp" //Chamando pacotes do Simple Web Server
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include "teste.cpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;



Trie GKSE;
void start(){
	inicializa(GKSE);
}


int main(){
	start();
    
//sabemos que it->second armazena nossa palavra do formulario e 
// stream << "{\"res\":\"" <<  it->second << img_button << "\"}"; é responsavel por mostra ela
	HttpServer server;
	server.config.port = 8080; //porta do servidor será localhost/8080
	//server.init
	//função que recebe query do tipo localhost:8080/query?text={text}
	server.resource["^/query$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request){
		//Trecho do código para obter a query (consulta)
		
		auto query_fields = request->parse_query_string(); //Recebe o conteúdo de "entrada"
		auto it = query_fields.find("text"); // Obtem o texto do conteudo
		cout << it->second << endl;
		
		
    
		
		//A resposta para o servidor vai ser um JSON do formato
		//{"res": "O seu projeto final vai ser incrível, [texto]!"}	
		//JSON
		// {"atributo1":"valor1",
		//	"atributo2": {"sub-atributo": "valor2"}} 
		string img_button = "</br> <input id = 'btn_img' type = 'button' onclick='print_img()' value ='Me clique!'> </br>";
		vector<std::string> resultado;
		stringstream res;
               vector<Pair> rest = pesquisa(it->second,GKSE); 
               int tamanho = rest.size();
               ifstream arquivoE;
               string linha;
			   string preffix="./../aNames/";
			  if(rest[0][0]==-1){
            resultado.push_back("Não Encontrado");
          }else{
     /////////////////////////////////////          //função find + transforma em string
                for(int k = 0;k<min(20,tamanho);k++){//só pega 20 resultados
					int number = rest[k][0] / 10000;
					 string name = "aTitles_" + to_string(number*10000) + "_" + to_string((number+1)*10000) + ".txt";
               arquivoE.open(preffix+name);
                int i = 0;
                number = number*10000;
                if(arquivoE.is_open()){
              while(getline(arquivoE,linha)){
					//aqui podemos fazer operaões linha a linha
					//stringstream geek(linha);
					if (rest[k][0]==number){
						resultado.push_back(linha);
					}
					number++;            
                }
  			}arquivoE.close();
				}};
  //////////////////////////////////////////////////////
  //resultado =string com os titulos
               /*std::string resultado = " ";
               resultado = resultado +std::to_string(rest[0]); */
			   res << "{\"res\":\"";
        if(it->second == "sleep"){
			cout<<"sleep";
		res << resultado[0] << "\"}";
		response->write(res);
		}
		
		else{ 
			
		for(int k=0;k<resultado.size();k++){
			res << resultado[k] <<"</BR>";
		}
		res<< "\"}";
		cout << res.str();
		response->write(res);
		}
	};
	
	
	
	//O método default do server é abrir um arquivo na pasta web/
	//vai receber querys do tipo localhost:8080/{text}
  	server.default_resource["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
		auto path = "./web/"+request->path; //caminho até os arquivos do tipo HTML
		SimpleWeb::CaseInsensitiveMultimap header;
		std::ifstream ifs(path, ifstream::in | ios::binary | ios::ate); //abrindo o arquivo dentro da pasta /web
		auto length = ifs.tellg();
       	ifs.seekg(0, ios::beg);
       	stringstream stream;
       	stream << ifs.rdbuf(); //salvando o conteúdo em uma stringstream

        header.emplace("Content-Length", to_string(length));
        response->write(header);
        response->write(stream.str().c_str(), length); //e inserindo na resposta do servidor
    };

	//função para lidar com erros (não necessário)
    server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
		//code
	};


    thread server_thread([&server]() {
        // Start server
        server.start();
    });

    // Wait for server to start so that the client can connect
    this_thread::sleep_for(chrono::seconds(1));

	server_thread.join();
}
