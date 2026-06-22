#include <iostream>
#include <vector>
#include "trie.cpp"

void insert_file(Trie T,const char* file)
{
    ifstream arquivoE;
    string linha;
    string r;
    arquivoE.open(file);
    Node *p;
    if(arquivoE.is_open())
    {
        while(getline(arquivoE,linha))
        {
            //Aaqui podemos fazer operaões linha a linha.
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
                    if(pos){
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
void inicializa(Trie GKSE){
  
   /*for(int i=0;i<=2;i++)
    {
        cout << "\r-> Inserting File " << i+1 << " of 64."; // Esse "\r" é um símbolo
        string prefix = "./sorted_words/sorted_words_";     // parecido com o "\n". Mas
        string number = to_string(i*50000);                 // ao invés dele criar uma
        string sufix = ".txt";                              // linha, ele reseta a
        string a = prefix + number + sufix;                 // linha, meio que
        const char *arq = a.c_str();                        // reescrevendo ela.
        insert_file(GKSE,arq);
    }*/
    //A inicialização acima se dá por insersão normal
    //Abaixo fazemos deserialização
    GKSE.Deserialize();

}

vector<Pair> pesquisa(string query,Trie GKSE){
    vector<Pair> g1;
    g1.push_back(Pair(-1,-1));
    
    auto time1 = chrono::high_resolution_clock::now();
    vector<Pair> res = GKSE.find(query);
    auto time2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> t_search = time2 - time1;
    sort(res.begin(),res.end());//Ordenação por frequência
    cout << "-> " << res.size() << " results found in " << t_search.count()/1000 << " seconds." << endl;

    if(res.empty())
    {
        return g1;
    }
    else
    {
        cout << "-> Results:" << endl;
        long unsigned int counting = 0;
        vector<Pair> res20;

        if (res.size() > counting + 20){res20=vector<Pair>(res.begin()+counting,res.begin()+counting+20);}
        else{res20=vector<Pair>(res.begin()+counting,res.end());}
        return res20;
    }
}
