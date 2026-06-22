#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <exception>
#include <thread>
#include "Pair.cpp"

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
char index2char(int index)
{
    if (index>=0 &&index<=9)
    { // Algarismos 0-9.
        return (char)(index+48);
    }
    // Letras minusculas a-z.
    return (char)(index+87);
}
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

    vector<str_dt> suggest(string word,int maxCost,int maxlen){
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        vector<str_dt> results;
        int sz = word.size();
        string nodeword = "";
        vector<int> current_row(sz + 1);
        int cut=0;
        // Inicialização da primeira linha (Programação dinâmica)
        for (int i = 0; i < sz; ++i) current_row[i] = i;
        current_row[sz] = sz;

        for(int i = 0;i<36;i++){
            if(aRoot->aChild[i]){
                nodeword+=index2char(i);
                recurse_levenshtein(aRoot->aChild[i], index2char(i), current_row, word, maxCost,nodeword,results, maxlen, cut);
                cut+=1;

            }
            int s = nodeword.size();
            int c=cut;
            for(int k=0;k<c;k++) {
                nodeword.pop_back();
                cut--;
                }
        }
        return results;
    }
  void Serialize()
    {// Autoria da função Sertialize/Deserialize e auxiliares: Jorge Costa
        ofstream TextSerialize ("trieSerial");
        string Text = Serialize(aRoot);
        cout << "Aqui foi.\n";
        TextSerialize << Text;
        cout << "Aqui também.\n";
        TextSerialize.close();
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
    void recurse_levenshtein(Node*& pNode, char ch, vector<int> last_row, const string& word,int maxCost,string& nodeword,vector<str_dt>&results,int maxlen,int&cut)
    {
        // Referencias: http://stevehanov.ca/blog/index.php?id=114
        //              https://murilo.wordpress.com/2011/02/01/fast-and-easy-levenshtein-distance-using-a-trie-in-c/

    int sz = last_row.size();
    vector<int> current_row(sz);
    current_row[0] = last_row[0] + 1;
    // Calcula o custo de inserir, deletar ou substituir uma letra;
    int insert_or_del, replace;
    for (int i = 1; i < sz; ++i) {
        insert_or_del = min(current_row[i-1] + 1, last_row[i] + 1);
        replace = (word[i-1] == ch) ? last_row[i-1] : (last_row[i-1] + 1);

        current_row[i] = min(insert_or_del, replace);
    }

    if (current_row[sz-1] <= maxCost && !(pNode->docs.empty()))
    {
        int l = (pNode->docs).size();
        str_dt s(nodeword,l);
        results.push_back(s);
    }

    if (results.size()>=maxlen)
    {
        return;
    }
    // Se há algum elemento na current_row menor do que nosso maxCost,
    // fazemos a recursão pelos filhos do pNode atual, pois pode haver algum
    // sufixo cuja distancia de levenshtein seja menor
    if (*min_element(current_row.begin(), current_row.end()) <= maxCost) {
        for (int i = 0;i<36;++i) {


            if(pNode->aChild[i]){
                ch=index2char(i);
                nodeword+=ch;
                recurse_levenshtein(pNode->aChild[i],ch, current_row, word,maxCost,nodeword,results,maxlen,cut);
                cut+=1;

            }
                int s = nodeword.size();
                int c=cut;
                for(int k=0;k<c;k++) {
                nodeword.pop_back();
                cut--;
                }
        }
    }
    }
    string Serialize(Node *Current) // Auxilia a Serialize().
    {
        string Text ("");
        int Count = 0;
        for (int i = 0; i < 36; i++)
        {
            if (Current->aChild[i] != nullptr)
            {
                for (int j = 0; j < Count; j++)
                {
                    Text += "n";
                }
                Count = 0;
                Text += "+";
                Text += Serialize(Current->aChild[i]);
            }
            else Count += 1;
        }
        if (Current->docs.empty()) Text += "/";
        else
        {
            for (Pair Par : Current->docs)
            {
                Text += to_string(Par[0]) + ",";
                Text += to_string(Par[1]) + ",";
            }
            Text.pop_back();
            Text += "/";
        }
        return Text;
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

string print_title(int x)
{
    string title = "";
    int number = x / 10000;
    string name = "aNames/aTitles_" + to_string(number*10000) + "_" + to_string((number+1)*10000) + ".txt";
    string line;
    ifstream file (name);
    number = number*10000;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (x == number)
            {
                stringstream split;
                split<<line;
                string words;
                split>>words;//este passo tira o ID da sstream
                while(split>>words){
                    //este loop salva o título
                    title= title+words+" ";
                }
            }
            number += 1;
        }
    }
    file.close();
    return title;
}
void print_vector(vector<Pair> v,int couting)
{
    int i = couting+1;
    for(int j=0;j<v.size();j++)
    {
        cout << " > ["<< i <<"] " << print_title(v[j][0]) << endl;
        i+=1;
    }
}
std::string aDocs (int aIndex) // Função para procurar o texto referente ao dbindex aIndex.
{
    int aNumber = aIndex/10000; aNumber *= 10000;
    std::ifstream aFile ("aTexts/aDocs_" + std::to_string(aNumber) + "_" + std::to_string(aNumber+10000)+".txt");
    std::string aLine;
    std::string aText ("");
    //std::cout<<"aTexts/aDocs_" + std::to_string(aNumber) + "_" + std::to_string(aNumber+10000)<<endl;
    if (aFile.is_open())
    {
        bool aIsText (false); // Este aIsText indica se é o texto que procuramos.
        while(getline(aFile, aLine)) // E sim. Ainda não achei um jeito menos doloroso de procurar pelo texto.
        {
            std::string aNotherLine (aLine);
            aLine.erase(aLine.begin()+21, aLine.end()); // Isso deixa aLine com os primeiros caracteres. E se for igual a
            if (aLine == "Marked: low fidelity ")       // "Marked: low fidelity ", o programa reconhece um novo artigo.
            {
                if (aIsText) break;
                aNotherLine.erase(aNotherLine.begin(), aNotherLine.begin()+21);
                int aDataBaseIndex = std::stoi(aNotherLine);
                if (aDataBaseIndex == aIndex)
                {
                    aIsText = true;
                    continue;
                }
                else continue;
                break;
            }
            else if (aIsText) aText += aNotherLine + "\n";
        }
        aFile.close();
    }
    else return " > The text couldn't be openned.";
    return aText;
}
class OutOfRange : public exception
{
protected:
    const char* msg = "Ooops! Try a lower number!\n\n";

public:

    const char *what() const throw()
    {
        return msg;
    }
};

string ShowText(string aInner,vector<Pair> res,int counting){
    int aIndex = std::stoi(aInner);
    if (aIndex > counting+20)
    {
        throw OutOfRange();
    }
    return aDocs(res[aIndex-1][0]);

}





