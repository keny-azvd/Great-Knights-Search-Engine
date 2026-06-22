#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <chrono>
#include <thread>

std::string aDocs (int aIndex) // Função para procurar o texto referente ao dbindex aIndex.
{
    int aNumber = aIndex/10000; aNumber *= 10000;
    std::ifstream aFile ("aTexts/aDocs_" + std::to_string(aNumber) + "_" + std::to_string(aNumber+10000));
    std::string aLine;
    std::string aText ("");
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

int main()
{
    std::cout << "--> Welcome to the Best Burger Kingdom! Here you can... Well, type something. May ya? <--\n\n";
    while (1)
    {
        std::string aInner;
        int aIndex;
        std::cout << "-> Type the dbindex number of article [type n to finish the program]: ";
        std::cin >> aInner;

        if (aInner == "n") break;
        else
        {
            try // Se ver mais outra Exception, por favor, me avise.
            {
                aIndex = std::stoi(aInner);
            }
            catch (const std::invalid_argument &aWrong)
            {
                std::cerr << " > Ooops. It's an invalid argument.\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                break;
            }
            catch (const std::out_of_range &aWrong)
            {
                std::cerr << " > Ooops. This can't be converted to an integer. It's too large!\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                break;
            }
        }

        if (aIndex > 1561761)
        {
            std::cout << " > Ooops, this is a very curious query. We can't make it with our data."
                      << " Maybe a lower number?\n\n";
            continue;
        }
        std::chrono::high_resolution_clock::time_point aStart = std::chrono::high_resolution_clock::now();
        int aNumber = aIndex/10000; // Essa divisão sempre retornará um inteiro.
        aNumber *= 10000;           // E deixamos aNumber igual ao primeiro artigo do intervalo referente.

        std::ifstream aFile ("aNames/aTitles_" + std::to_string(aNumber) + "_" + std::to_string(aNumber+10000));
        std::string aLine;
        if (aFile.is_open())
        {
            while (getline(aFile, aLine))
            {
                if (aLine == "We all have an start...")
                {
                    std::chrono::high_resolution_clock::time_point aEnd = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> aTime = std::chrono::duration_cast<std::chrono::duration<double>>(aEnd-aStart);
                    std::cout << " > It took " << aTime.count() << " seconds.\n\n";
                    std::cout << " > Ooops, we can't find this query. Maybe it doesn't exist?\n" << std::endl;
                    break;
                }
                else if (aNumber == aIndex)
                {
                    if (aLine == "") // Para o caso em que o título não exista.
                    {
                        std::chrono::high_resolution_clock::time_point aEnd = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> aTime = std::chrono::duration_cast<std::chrono::duration<double>>(aEnd-aStart);
                        std::cout << " > It took " << aTime.count() << " seconds.\n\n";
                        std::cout << " > Ooops, we can't find this query. Maybe it doesn't exist?\n" << std::endl;
                        break;
                    }

                    std::string aStringNumber = std::to_string(aNumber);  // Isso é para comtar os algarismos de aNumber.
                    int aNumberLength = 0;
                    while (aStringNumber[aNumberLength]) aNumberLength++; // Conta o número de algarismos.
                    aLine.erase(0, aNumberLength + 1);                    // E apaga a mesma quantidade de aLine.

                    std::string aText (" --- " + aLine + " ---\n\n" + aDocs(aNumber));
                    std::chrono::high_resolution_clock::time_point aEnd = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> aTime = std::chrono::duration_cast<std::chrono::duration<double>>(aEnd-aStart);

                    std::cout << " > It took " << aTime.count() << " seconds.\n\n" << aText + "\n";
                    aFile.close();
                    break;
                }
                else aNumber += 1;
            }
        }
        else
        {
            std::chrono::high_resolution_clock::time_point aEnd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> aTime = std::chrono::duration_cast<std::chrono::duration<double>>(aEnd-aStart);
            std::cout << " > It took " << aTime.count() << " seconds.\n\n";
            std::cout << " > Ooops, we can't open the source text.\n";
        }

        std::cout << "-> Another query [y/n]? "; // Recomeça a busca.
        std::cin >> aLine;                         //
        if (aLine != "y") break;                   // Ou acaba com ela.
    }
    return 0;
}
