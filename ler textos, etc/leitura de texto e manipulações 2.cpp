#include <iostream>
#include <fstream>
using namespace std;

int main(){
  string a = "jorge4";
  ofstream arquivo; // esse método indica operação de saida
  // logo so podemos armazenar coisas em nosso arquivo de texto que foi criado.
  arquivo.open("keny.txt",ios::app);// cria o arquivo, ios::app serve para posicionar o cursor no final do arquvio
  // dai ele vai escrever os textos na sequencia, caso contrario, ele sobrescreve-rá no nosso arquivo-substituit.

  arquivo << " "+a;


  arquivo.close();


return 0;
}
