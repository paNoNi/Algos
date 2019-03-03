#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#define NUM 1000000

using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;
using std::pair;

class Map
{
private:
    typedef struct
    {
        string key;
        string value;
        bool flag;
    }cell;

    vector<cell> data;
public:
    Map()
    {
        data.resize(NUM);
        for (int i = 0; i < NUM ; ++i) {
            data[i].flag = 0;
        }
    }

    int hash(string key);

    void put(string key , string value);

    void delete_key(string key);

    string get_key(string key);

};

string Map::get_key(string key)
{
    if (data[hash(key)].flag == 0)
    {
        return "none";
    } else
    {
        return data[hash(key)].value;
    }
}

void Map::delete_key(string key)
{
    data[hash(key)].flag = 0;
}

void Map::put(string key , string value)
{
    data[hash(key)].value = value;
}

int Map::hash(string key)
{
    int key_temp;
    int counter = 0;
    char temp;
    for(auto c:key)
    {
        key+=c;
        ++counter;
        temp = c;
    }
    return ( key_temp = key_temp/counter*temp);
}

int main() {
    ifstream inFile("map.in");
    ofstream outFile("map.out");
    Map cont;
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
            outFile << cont.get_key(key);
        }
    }
    inFile.close();
    outFile.close();
    return 0;
}