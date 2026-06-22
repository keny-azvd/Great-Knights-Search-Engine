#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <fstream>

using namespace std;

struct Node
{
    Node *aChild[36];
    vector<int> docs;

    void put_doc(int doc_id)
    {
        this->docs.push_back(doc_id);
    }

    Node(){
        this->docs ={};
        for(int i = 0; i < 36; i++)
        {
            this->aChild[i] = nullptr;
        }
    }
};

vector<int> convert(string aWord)
    {
        vector<int> indexes;
        int aKey;
        for (char& aLetter:aWord)
        {
            if((int)aLetter < 123 && (int)aLetter > 96)
            {// Letras minúsculas.
                aKey = (int)aLetter - 87;
                indexes.push_back(aKey);
            }
            else if ((int)aLetter < 58 && (int)aLetter > 47)
            {// Números de 0 a 9.
                aKey = (int)aLetter - 48;
                indexes.push_back(aKey);
            }

            else if((int)aLetter < 91 && (int)aLetter > 64)
            {// Letras maiúsculas.
                aKey = (int)aLetter - 55;
                indexes.push_back(aKey);
            }
        }
    return indexes;
    }

class Trie
{
protected:
    Node *aRoot;
public:
    Trie()
    {
        aRoot = new Node();
        cout << endl << "-> Starting trie build..." << endl;
    }

    Node* insert(string aWord)
    {
        Node**p = &(aRoot);
        insert(convert(aWord), p);
        return *p;
    }
    vector<int> find(string aWord)
    {
        cout << endl << "-> Finding: " << aWord << "..." << endl;
        return find(convert(aWord));
    }
    void suggest(string query)
    {
        cout<<"-> Sorry. Word not found.  ;-;";
    }

    ////////////////////////////////////////////////////////
    // Essa parte de baixo eu incluí para o assunto da
    // serialização.
    //

    void Serialize()
    {
        ofstream TextSerialize ("trieSerial"); // Se quiser outro nome, também mude
        if (TextSerialize.is_open())               // no Deserialization() abaixo.
        {
            string Text = Serialize(aRoot);
            TextSerialize << Text;
            TextSerialize.close();
        }
    }
    void Deserialize()
    {
        Node *Current = aRoot; unsigned long int Number = 0; unsigned long int *Position = &Number;
        ifstream TextDeserialize ("trieSerial"); // Sim, com esse nome mesmo.
        string Rain;
        TextDeserialize >> Rain;                 // Copiamos o texto para Line.
        string *Line = &Rain;

        ShootingChars(Line, Position, Current);
        TextDeserialize.close();
    }
private:
    void insert(vector<int> indexes,Node**&p)
    {
        for(int i : indexes)
        {
            if((*p)->aChild[i] == nullptr)
            {
                (*p)->aChild[i]=new Node();
            }
            p=&((*p)->aChild[i]);
        }
    }
    vector<int> find(vector<int> word)
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
            for (int Int : Current->docs)
            {
                Text += to_string(Int) + ",";
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
        while (true)
        {
            if ((*List)[*Position] == ',')
            {
                Current->put_doc(stoi(CurrentID));
                CurrentID = "";
                *Position += 1;
                continue;
            }
            else if ((*List)[*Position] == '/')
            {
                Current->put_doc(stoi(CurrentID));
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
                split << line;
                string words;
                split >> words; // Este passo tira o ID da stringstream.
                while (split >> words)
                {
                    // Este loop salva o título.
                    title = title + words + " ";
                }
            }
            number += 1;
        }
    }
    file.close();
    return title;
}
void print_vector(vector<int> v,int couting)
{
    int i = couting+1;
    for(int x:v)
    {
        cout << " > ["<< i <<"] " << print_title(x) << endl;
        i+=1;
    }
}
std::string aDocs (int aIndex) // Função para procurar o texto referente ao dbindex aIndex.
{
    int aNumber = aIndex/10000; aNumber *= 10000;
    std::ifstream aFile ("aTexts/aDocs_" + std::to_string(aNumber) + "_" + std::to_string(aNumber+10000));
    std::string aLine;
    std::string aText ("");
    if (aFile.is_open())
    {
        bool aIsText (false);        // Este aIsText indica se é o texto que procuramos.
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
