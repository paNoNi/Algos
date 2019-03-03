#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <ctime>
#include <iostream>
#include <synchapi.h>
#include <stdlib.h>
#include <cstdlib>

#define NUM 10

using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;

string random_name() {
    string name;
    srand( time(0));
    int counter = 1 + rand() % 10;
    for (int i = 0; i < counter ; ++i) {
        Sleep(100);
        if (!i){
            name+= (char )(65 + rand()%26);
        } else
            name+= (char)(97 + rand()%26);
    }
    return name;
}

string random_number() {
    string number;
    srand(time (0));
    int counter = 1 + rand() % 10;
    for (int i = 0; i < counter ; ++i) {
        Sleep(100);
        number += (char)(48 + rand()%10);
    }
    return number;
}

void writer_of_number() {
    ofstream file("list.in");
    long count = 1 + rand()%NUM*50;
    for (int i = 0; i < count ; ++i) {
        file << random_name() << " " << random_number() << "\n";
    }
}

class List {
public:
  class Node{
  public:
      Node *pNext = nullptr;
      Node *pPrev = nullptr;

      string value = "";
      string key = "";
  };

  Node *pHead = nullptr;
  Node *pEnd = nullptr;

  ~List() {
      Node *temp = pHead;
      while(temp != nullptr){
          Node *temp_2 = temp;
          temp = temp->pNext;
          delete temp_2;
      }
  }

  void push(const string &key, const string &value){
      Node* temp = new Node();
      temp->key = key;
      temp->value = value;

      if(pHead == nullptr){
          pHead = temp;
          pEnd = temp;
          return;
      }

      temp->pPrev = pEnd;
      pEnd->pNext = temp;
      pEnd = temp;

  }

  bool set_value(const string &key, const string &value){
      Node *temp = pHead;
      while (temp != nullptr){
          if(temp->key == key){
              temp->value = value;
              return true;
          } else {
              temp = temp->pNext;
          }
      }
      return false;
  }

  bool delete_key(const string &key){
      Node* temp = pHead;
      while (temp != nullptr){
          if(temp->key == key){
              if (temp == pEnd){
                  pEnd = temp->pPrev;
                  if (pEnd != nullptr)
                    pEnd->pNext = nullptr;
              }
              if (temp == pHead){
                  pHead = temp->pNext;
                  if (pHead != nullptr)
                      pHead->pPrev = nullptr;
              }
              if(temp->pPrev != nullptr){
                  temp->pPrev->pNext = temp->pNext;
              }
              if(temp->pNext!= nullptr){
                  temp->pNext->pPrev = temp->pPrev;
              }
              delete temp;
              return true;
          }
          temp = temp->pNext;
      }
      return false;
  }

  string get_value(const string &key){
      Node* temp = pHead;
      while (temp != nullptr ) {
          if (temp->key == key){
              return temp->value;
          }
          temp = temp->pNext;
      }
      return "none";
  }
};


class Map{
private:
    List tablehash1[NUM];
    List tablehash2[NUM];

    int counthash1[NUM] = {0};
    int counthash2[NUM] = {0};

public:
    int hash1(const string &key){
        int key_value = 0;
        int counter = 1;
        for(auto c:key){
            key_value += abs((c+1)%53*counter);
            key_value%=NUM;
            ++counter;
        }
        return key_value;
    }

    int hash2(const string &key){
        int key_value = 0;
        int counter = 1;
        for(auto c:key){
            key_value += c;
            key_value%=NUM;
            ++counter;
        }
        return key_value;
    }

    void put(const string &key, const string &value){
        int key_t1 = hash1(key);
        int key_t2 = hash2(key);
        if(!tablehash1[key_t1].set_value(key,value)){
            tablehash1[key_t1].push(key, value);
            ++counthash1[key_t1];
        }
        if(!tablehash2[key_t2].set_value(key,value)){
            tablehash2[key_t2].push(key, value);
            ++counthash2[key_t2];
        }
    }

    void delete_key(const string &key){
        tablehash1[hash1(key)].delete_key(key);
        tablehash2[hash2(key)].delete_key(key);
    }

    string get_hash1(const string &key){
        return tablehash1[hash1(key)].get_value(key);
    }

    int get_count_hash1(int count) {
        return counthash1[count];
    }

    int get_count_hash2(int count) {
        return counthash2[count];
    }

};

int main() {
    ifstream inFile("list.in");
    ofstream outFile("data.out");
    if (!inFile)
        std::cout << "\nCant find this file : " << "list.in";
    Map cont;
    string name;
    writer_of_number();
    while (inFile >>  name)
    {
            string number;
            inFile >> number;
            cont.put(number,name);
    }
    inFile.close();

    outFile << "1 hash" << "\t\t\t" << "2 hash\n\n";
    for (int i = 0; i < NUM ; ++i) {
        outFile << "list number " << i << " = " << cont.get_count_hash1(i) << "\t" << "list number" << i << " = " << cont.get_count_hash2(i) << "\n";
    }

    system("pause");

    outFile << "\t\t Commands \t\t\n";
    ifstream comFile("commands.in");
    string namestr;
    while(comFile >> namestr) {
        outFile <<"\t" << namestr << "\t\t - \t\t" << cont.get_hash1(namestr) << "\n";
    }

    comFile.close();
    outFile.close();
    return 0;
}