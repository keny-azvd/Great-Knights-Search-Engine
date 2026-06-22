#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;



int main(){
  int tamanho;
  string r;
  ifstream arquivoE;
  string linha;
  arquivoE.open("keny.txt");
  if(arquivoE.is_open()){
    while(getline(arquivoE,linha)){
        //aqui podemos fazer operaões linha a linha
        tamanho =  linha.length();
        for(int i =0;i<tamanho;i++){
            r = linha[i];
            if(1 == 0){

            }else{
            cout << linha[i] << endl;}
        }

    }
  }else{
  cout << "nao foi possivel abrir o arquivo" << endl;

  }


return 0;

}
