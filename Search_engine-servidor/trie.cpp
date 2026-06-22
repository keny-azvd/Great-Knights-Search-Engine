#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <exception>
#include <thread>
#include "./../Pair.cpp"

using namespace std;

struct Node
{

    Node *aChild[36];
    vector<Pair> docs;
   /* agora o vetor docs é do tipo (id,freq)*/

    Node(){
        this->docs ={};
        for(int i=0;i<36;i++){
            this->aChild[i]=nullptr;
        }
    }

    void put_doc(Pair P)
    {
        /*Função recebe um par (id,freq) e coloca no final da vetor*/
        this->docs.push_back(P);
    }

};

vector<int> convert(string aWord)
{
    vector<int> indexes;
    int aKey;
    for (char& aLetter:aWord)
    {
        if((int)aLetter < 123 && (int)aLetter>96)
        { // Letras minúsculas.
            aKey = (int)aLetter - 87;
            indexes.push_back(aKey);
        }
        else if ((int)aLetter < 58 && (int)aLetter>47)
        { // Números de 0 a 9.
            aKey = (int)aLetter - 48;
            indexes.push_back(aKey);
        }
        else if((int)aLetter < 91 && (int)aLetter>64)
        { // Letras maiúsculas.
            aKey = (int)aLetter - 55;
            indexes.push_back(aKey);
        }
    }
    return indexes;
}

vector<Pair> inter2sorted(vector<Pair>v1,vector<Pair>v2){

    int j=0;
    int i=0;
    vector<Pair>res;
    if(v1.empty() || v2.empty()){
        res={};
        return res;
    }
    while(i < v1.size() && j<v2.size()){
        if(v1[i][0]<v2[j][0]) i++;
        else if(v1[i][0]>v2[j][0])j++;
        else{
            res.push_back(v1[i]);
            j++;
            i++;
            }
    }
    return res;
}
class Trie
{
protected:
    Node *aRoot;
public:
    Trie()
    {
        aRoot = new Node();//  Usa-se o contrutor Node() para criar a raiz;
        cout << endl << "-> Starting trie build..." << endl;
    }

    Node* insert(string aWord)//retorna um ponteiro ao nó final
    {
        Node**p = &(aRoot);
        insert(convert(aWord),p);
        return *p;
    }

    vector<Pair> find(string aPhrase){
        cout << endl << "-> Finding: " << aPhrase << "..." << endl;
        stringstream split_query;
        split_query<<aPhrase;
        string word;
        split_query>>word;
        vector<Pair> res = this->find(convert(word));
        while(split_query>>word){
            res=inter2sorted(res,this->find(convert(word)));
        }
        return res;
    }

    
  
    void Deserialize()
    {
        Node *Current = aRoot; unsigned long int Number = 0; unsigned long int *Position = &Number;
        ifstream TextDeserialize ("trieSerial");
        string Rain;
        TextDeserialize >> Rain;               // Copiamos o texto para Line.
        string *Line = &Rain;

        ShootingChars(Line, Position, Current);
        TextDeserialize.close();
    }
private:
    void insert(vector<int> indexes,Node**&p){
        for(int i:indexes){
            if((*p)->aChild[i]==nullptr)
            {//Caso o filho i não exista, cria-se um novo Nó;
                (*p)->aChild[i]=new Node();
            }

            p=&((*p)->aChild[i]);
        }
    }
    vector<Pair> find(vector<int> word)
    {
        Node **p = &aRoot;
        for (int i:word)
        {
            if (!((*p)->aChild[i])) {return {};
            } else {
            p = &((*p)->aChild[i]);
            }
        }
        return (*p)->docs;
    }
    
    
    void ShootingChars(string *List, unsigned long int *&Position, Node *&Current)
    {
        Node *NextNode;
        for (int Count = 0; Count < 36; Count++)
        {
            if ((*List)[*Position] == 'n') *Position += 1;
            else if ((*List)[*Position] == '+')
            {
                Current->aChild[Count] = new Node();
                NextNode = Current->aChild[Count];
                *Position += 1;
                ShootingChars(List, Position, NextNode);
            }
            else
            {
                break;
            }
        }
        if ((*List)[*Position] == '/')
        {
            *Position += 1;
            return;
        }
        string CurrentID ("");
        int DBIndex;
        int Frequency;
        bool Where (false);
        while (true)
        {
            if ((*List)[*Position] == ',')
            {
                if (Where)
                {
                    Frequency = stoi(CurrentID);
                    CurrentID = "";
                    *Position += 1;
                    Where = false;
                    Current->put_doc(make_pair(DBIndex, Frequency));
                    continue;
                }
                DBIndex = stoi(CurrentID);
                CurrentID = "";
                *Position += 1;
                Where = true;
                continue;
            }
            else if ((*List)[*Position] == '/')
            {
                Frequency = stoi(CurrentID);
                Current->put_doc(make_pair(DBIndex, Frequency));
                *Position += 1;
                break;
            }
            CurrentID += (*List)[*Position];
            *Position += 1;
        }
    }

};

