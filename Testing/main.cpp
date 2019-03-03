#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

std::string get_key(std::vector<std::string> &);

void generation(std::string &word, std::vector<std::string> & arr_word , bool flag){
    int counter = 1 + std::rand()%20;
    if(arr_word.size() == 0) {
        for (int i = 0; i < counter; ++i) {
            char sym = 66 + rand() % 25;
            word += sym;
        }
        if(flag)
        arr_word.push_back(word);
    } else{
        int rand_var = 1 + rand()%2;
        switch (rand_var){
            case 1:{
                word = get_key(arr_word);
            }
            case 2: {
                for (int i = 0; i < counter; ++i) {
                    char sym = 66 + rand() % 25;
                    word += sym;
                }
                if(flag)
                arr_word.push_back(word);
            }
        }
    }
}

void save(std::string &word ){
    std::vector<std::string> arr_word;
    arr_word.push_back(word);
}

std::string get_key(std::vector<std::string> &arr_word){
    int key = std::rand()%arr_word.size();
    return arr_word[key];
}


int main() {
    std::ofstream outFile("multimap.in");
    srand( time(0));
    std::vector<std::string> arr_word {"A"};
    for (int i = 0 ; i < 10000 ; ++i){
        int rand = std::rand()%5;
        switch (rand){
            case 0:{
                std::string x;
                generation(x, arr_word, false);
                outFile << "delete " << x << "\n" ;
            }
            case 1:{
                std::string x;
                std::string y;
                generation(x, arr_word, 1);
                generation(y, arr_word, 0);
                outFile << "put " << x << " " << y << "\n";
            }
            case 2:{
                std::string x;
                generation(x, arr_word, 1);
                outFile << "get " << x << "\n" ;
            }
            case 3:{
                std::string x = arr_word[std::rand()%arr_word.size()];
                outFile << "next " << x << "\n" ;
            }
            case 4:{
                std::string x = arr_word[std::rand()%arr_word.size()];
                outFile << "prev " << x << "\n" ;
            }
        }
    }
    outFile.close();
    return 0;
}