#include "trie_builder.cpp"
#include <chrono>
#include <iostream>
#include <algorithm>


using namespace std;
int main(){
    
    //Trie GKSE=build(63); //Essa é a construção normal que depende de sorted_words2/
    Trie GKSE;
    auto Start = chrono::high_resolution_clock::now();
    GKSE.Deserialize();    //Aqui ocorre a contrução via desserialização                          
    auto End = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> Tempo = End - Start;
    cout << "-> Deserialization finished in " << Tempo.count()/1000 << " seconds!"<<endl;
    while(1)
    {
        cout<<"-> Type your query: ";
        string input;
        string query;
        vector<Pair>res;
        while(cin){//Passo para capturar mais de uma palavra.
            cin >> input;
            query+=input;
            query+=" ";
            if (cin.get()=='\n'){
                query.pop_back();
                break;
            }
        }
        if(query=="0")
        {
            return 0;
        }
            auto time1 = chrono::high_resolution_clock::now();
            res = GKSE.find(query);
            auto time2 = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> t_search = time2 - time1;
            cout << "-> " << res.size() << " results found in " << t_search.count()/1000 << " seconds "<<"("<<t_search.count()<<" ms)." << endl;
        
            stringstream split2;
            split2<<query;
            string wrong_word;
            split2>>wrong_word;
            if(res.empty())
            {
                if(split2>>wrong_word){//só iremos sugerir no caso de busca de palavra única
                    cout<<"Query Not Found !! We can't suggest multiple queries yet;\nTry typing a single word ;)"<<endl;
                }
                else{
                    auto time1 = chrono::high_resolution_clock::now();
                    vector<str_dt> suggested = GKSE.suggest(wrong_word,2,25000);
                    auto time2 = chrono::high_resolution_clock::now();
                    chrono::duration<double, milli> t_sugg = time2 - time1;
                    int count = 0;
                    sort(suggested.begin(),suggested.end());
                    cout<<" > "<<suggested.size()<<" suggestions found in "<<t_sugg.count()<< " ms."<<endl;
                    while(1){
                        
                        for(int i=count;i<min(count+10,(int)suggested.size());i++){
                            string s = (suggested[i]).str;
                            cout<<" > ["<< i+1 <<"] "<<s<<" ("<<suggested[i].len<<" results)"<<endl;
                        }
                        string num;
                        cout<<"-> Do you want do search any of above? [n or the number]? ";
                        cin>>num;
                        if(num!="n"){
                            try{
                                auto time1 = chrono::high_resolution_clock::now();
                                res=GKSE.find(suggested[stoi(num)-1].str);
                                auto time2 = chrono::high_resolution_clock::now();
                                chrono::duration<double, milli> t_search = time2 - time1;
                                cout << "-> " << res.size() << " results found in " << t_search.count()/1000 << " seconds "<<"("<<t_search.count()<<" ms)." << endl;
                                break;
                            }
                            catch (const std::invalid_argument &aWrong)
                            {
                                std::cerr << " > Ooops. It's an invalid argument.\n";
                                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                                continue;
                            }
                            catch (const std::out_of_range &aWrong)
                            {
                                std::cerr << " > Ooops. This can't be converted to an integer. It's too large!\n";
                                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                                continue;
                            }

                        }if (suggested.size() > count + 10) 
                        {                               
                            cout << "-> More suggestions [y/n]? ";
                            cin >> num;
                            if (num == "y") count += 10;
                            else break;
                        } else break;
                    }
                }
            }
            
        
        
        if(!res.empty())
        {
            
            cout << "-> Results:" << endl;
            sort(res.begin(),res.end());//Faz a ordenação por frequência;
            int counting = 0;
            vector<Pair> res20;
            while (1) // Hehe, de novo eim.
            {
                if (res.size() > counting + 20)
                {
                    res20=vector<Pair>(res.begin()+counting,res.begin()+counting+20);
                } else {
                    res20=vector<Pair>(res.begin()+counting,res.end());
                }
                print_vector(res20,counting);
                cout << endl << "-> Do you want to open any result [n or result number]? ";
                string answer;
                cin >> answer;
                if (answer != "n")
                {
                    try{
                    string Text = ShowText(answer,res,counting);
                    std::cout<<Text;
                    }
                    catch(const OutOfRange &e){//Colocarei mais exceptions futuramente;
                        std::cerr<<e.what();
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        continue;
                    }
                    catch (const std::invalid_argument &aWrong)
                    {
                        std::cerr << " > Ooops. It's an invalid argument.\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        continue;
                    }
                    catch (const std::out_of_range &aWrong)
                    {
                        std::cerr << " > Ooops. This can't be converted to an integer. It's too large!\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        continue;
                    }
                }
                if (res.size() > counting + 20) 
                {                               
                    cout << "-> More results [y/n]? ";
                    cin >> answer;
                    if (answer == "y") counting += 20;
                    else break;
                } else break;
            }
        }
        cout<< endl << "-> (To exit, enter the number 0)" << endl << endl;
    }
}
           