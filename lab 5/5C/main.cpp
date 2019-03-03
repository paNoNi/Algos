#include <fstream>
#include <string>
#include <cmath>
#include <vector>


#define NUM 100000

using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;

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

    Node* push(const string &key, const string &value){
        Node* temp = new Node();
        temp->key = key;
        temp->value = value;

        if(pHead == nullptr){
            pHead = temp;
            pEnd = temp;
            return temp;
        }

        temp->pPrev = pEnd;
        pEnd->pNext = temp;
        pEnd = temp;

        return temp;
    }

    bool set_value(const string &key, const string &value){
        Node *temp = find(key);
        if(temp != nullptr) {
            temp->value = value;
            return true;
        }
        return false;
    }

    Node* find(string key){
        Node *temp = pHead;
        while(temp != nullptr){
            if(temp->key == key){
                return temp;
            }
            temp = temp->pNext;
        }
        return temp;
    }

    bool delete_key(const string &key){
        Node* temp = find(key);
        if(temp != nullptr) {
            if (temp == pEnd) {
                pEnd = temp->pPrev;
                if (pEnd != nullptr)
                    pEnd->pNext = nullptr;
            }
            if (temp == pHead) {
                pHead = temp->pNext;
                if (pHead != nullptr)
                    pHead->pPrev = nullptr;
            }
            if (temp->pPrev != nullptr) {
                temp->pPrev->pNext = temp->pNext;
            }
            if (temp->pNext != nullptr) {
                temp->pNext->pPrev = temp->pPrev;
            }
            delete temp;
            return true;
        }
        return false;
    }

    string get_value(const string &key){
        Node* temp = find(key);
        if (temp != nullptr ) {
            return temp->value;
        }
        return "none";
    }


};


class LinkedMap{
private:
    List table[NUM];

    List *listOfPoiners = new List();


public:
    int hash(const string &key){
        int key_value = 0;
        int counter = 1;
        for(auto c:key){
            key_value += abs((c+1)%53*counter);
            key_value%=NUM;
            ++counter;
        }
        return key_value;
    }

    void put(const string &key, const string &value){
        int key_t = hash(key);
        if(!table[key_t].set_value(key,value) && !listOfPoiners->set_value(key,value)){
            table[key_t].push(key, value);
            listOfPoiners->push(key, value);
        }
    }

    void delete_key(const string &key){
        listOfPoiners->delete_key(key);
        table[hash(key)].delete_key(key);
    }

    string get(const string &key){
        return table[hash(key)].get_value(key);
    }

    string get_pPrev(const string &key){
        List::Node* pPrev_key = listOfPoiners->find(key);
        if(pPrev_key != nullptr) {
            if (pPrev_key->pPrev != nullptr) {
                return pPrev_key->pPrev->value;
            }
        }
        return "none";
    }

    string get_pNext(const string &key) {
        List::Node *pNext_key = listOfPoiners->find(key);
        if(pNext_key != nullptr) {
            if (pNext_key->pNext != nullptr) {
                return pNext_key->pNext->value;
            }
        }
        return "none";
    }
};

int main() {
    ifstream inFile("linkedmap.in");
    ofstream outFile("linkedmap.out");
    LinkedMap cont;
    string str;
    while (inFile >>  str)
    {
        if(str == "put")
        {
            string key, value;
            inFile >> key >> value;
            cont.put(key,value);
        }
        if(str == "delete")
        {
            string key;
            inFile >> key;
            cont.delete_key(key);
        }
        if (str == "get")
        {
            string key;
            inFile >> key;
            outFile << cont.get(key) << "\n";
        }
        if (str == "prev")
        {
            string key;
            inFile >> key;
            outFile << cont.get_pPrev(key) << "\n";
        }
        if (str == "next")
        {
            string key;
            inFile >> key;
            outFile << cont.get_pNext(key) << "\n";
        }
    }
    inFile.close();
    outFile.close();
    return 0;
}