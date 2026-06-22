#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <chrono>
#include "trie.cpp"

using namespace std;

void insert_file(Trie T,const char* file){
    ifstream arquivoE;
    string linha;
    string r;
    arquivoE.open(file);
    Node *p;
    if(arquivoE.is_open())
    {
        while(getline(arquivoE,linha))
        {
            //Aaqui podemos fazer operações linha a linha.
            if(linha[0]=='$')
            {
                p = T.insert(linha.substr(1));
            }
            else
            {
                stringstream ids;
                ids<<linha;
                string data;//pode ser um Id ou frequencia, controlamos isso pelo bool
                Pair P;
                bool pos=false;
                while(ids>>data)
                {
                    P.set(stoi(data),pos);
                    if(pos){/*vai ser verdadeio quando pos=true(1), 
                        ou seja, o dado for frequencia; Neste caso 
                        insertaremos o Pair, na arvore;*/
                        p->put_doc(P);
                    }
                    pos=!pos;
                }

            }
        }
    }
    else
    {
        cout << "Não foi possível abrir o arquivo "<< file << endl;
    }
    arquivoE.close();
}

Trie build(int num_docs){//num_docs pode variar de 0 a 64
    Trie GKSE;
    auto start = chrono::high_resolution_clock::now();
    for(int i=0;i<=num_docs;i++)
    {
        cout << "\r-> Inserting File " << i+1 << " of 64."; // Esse "\r" é um símbolo
        string prefix = "./sorted_words2/sorted_words_";     // parecido com o "\n". Mas
        string number = to_string(i*50000);                 // ao invés dele criar uma
        string sufix = ".txt";                              // linha, ele reseta a
        string a = prefix + number + sufix;                 // linha, meio que
        const char *arq = a.c_str();                        // reescrevendo ela.
        insert_file(GKSE,arq);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> t_build = end - start;
    cout << "\n-> Build finished in " << t_build.count()/1000 << " seconds!\n" << endl;
    return GKSE;
}
