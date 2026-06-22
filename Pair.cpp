#include <vector>
#include <iostream>
#include <string>
/*#include <algorithm>
#include <boost/sort/spreadsort/spreadsort.hpp>*/

class Pair //Criei com letra maiúscula pois já existe std::pair no C++
{
public:
    int core[2];

    Pair(){//construtor vazio
        core[0]=0;
        core[1]=0;
    }
    Pair(int id,int freq){
        /*construtor com dois dados:
        ID vem primeiro, depois a frequencia
        Uso: Pair P(id,freq)
        */
        core[0]=id;
        core[1]=freq;    
    }
    
    Pair(int data,bool index){
        core[index]=data;
        /*contrutor com apenas um dado:
        este dado é colocado no index passado pelo boleano
        se foi false, coloca em primeira, e verdadeiro em segundo;
        
        Talvez seja útil caso queira insertar 
        uma coisa de cada vez na deserialização*/
       
    }
    bool operator<(const Pair &p2){//operador usado por std::sort;
        if(core[1]>p2.core[1]) return true;
        //Invertemos o sinal pra > pois queremos mais frequentes primeiro
        else return false;
    }
    int operator[](int i){
        return core[i];
    }
    void set(int data, bool index){
        this->core[index]=data;
    }

};
Pair make_pair(int id,int freq){
        Pair P(id,freq);
        return P;
    }
void printvp(std::vector<Pair> v){
    std::cout<<"\n";
    for(int i=0;i<v.size();i++){
        std::cout<<v[i][0]<<","<<v[i][1]<<" ";
    }
    std::cout<<"\n";
}

class str_dt{//Classe que auxilia a sugestão de palavras
    //Armazena uma string e a quantidade de documentos
    public:
    std::string str; //Palavra
    int len; //Tamaho do vetor de documentos
    str_dt(std::string s,int l){
        this->str=s;
        this->len=l;   
    }
    bool operator<(const str_dt &s2){//Operador usado por std::sort;
        if(len>s2.len) return true;
        else return false;
    }
    void operator=(const str_dt &s2){//Operador usado por std::sort;
        this->str=s2.str;
        this->len=s2.len;
    }
    
};