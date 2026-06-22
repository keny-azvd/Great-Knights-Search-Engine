#include <bits/stdc++.h>

using namespace std;

struct Node
{
    char aChar;
    bool aEnd;
    Node *aChild[28];

    Node(char aLetter)
    {
        this->aChar = aLetter;
        this->aEnd = false;

        // Esta parte separa os caracteres. Os de 0 a 9 são os números, e os de 10 a 35 são as letras.
        aChild[0] = aChild[1] = aChild[2] = aChild[3] = aChild[4] = aChild[5] = aChild[6] = aChild[7] = aChild[8]
        = aChild[9] = aChild[10] = aChild[11] = aChild[12] = aChild[13] = aChild[14] = aChild[15] = aChild[16] = aChild[17]
        = aChild[18] = aChild[19] = aChild[20] = aChild[21] = aChild[22] = aChild[23] = aChild[24] = aChild[25] = aChild[26]
        = aChild[27] = aChild[28] = aChild[29] = aChild[30] = aChild[31] = aChild[32] = aChild[33] = aChild[34] = aChild[35]
        = nullptr;
    }
};

class Trie
{
private:
    Node *aRoot;

public:
    Trie()
    {
        cout << endl << "-> Starting trie build..." << endl;
    }
    ~Trie()
    {
        cout  << "-> Build finished." << endl;
    }

    void insert(string aWord)
    {
        // A ideia inicia é transformar a palavra numa sequência de caracteres, para depois transformá-los em índices
        // para serem identificados nos nós.

        char aWord_Char[aWord.length()];
        int aKey;

        strcpy(aWord_Char, aWord.c_str());

        cout << "-> Indexing word: " << aWord << "..." << endl;
        for (int i = 0; i < aWord.length(); i++)
        {
            cout << aWord_Char[i] << endl;
        }

        cout << "-> The pointer is in keys: " << endl;
        // Esta parte mosta as chaves dos caracteres. Isso serve para anexá-los nos nós-filhos.
        // (nada mais que testes maneiros)
        for (int i = 0; i < aWord.length(); i++)
        {
            if ((int)aWord_Char[i] < 90)
            {
                aKey = (int)aWord_Char[i] - 48;
                cout << aKey << endl;
            }
            else
            {
                aKey = (int)aWord_Char[i] - 87;
                cout << aKey << endl;
            }
        }
        cout << endl;
    }
};

int main()
{
    cout << "-----> Wellcome to the GK'SE, the Search Engine of the Great Knights! (build mode) <-----" << endl;

    Trie arvore;
    arvore.insert("aoba");
    arvore.insert("bacate");
    arvore.insert("1948");
    arvore.insert("autism");

    return 0;
}
