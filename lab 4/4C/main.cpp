#include <iostream>
#include <fstream>
#include <string>


class Stack {
public:

    Stack() {
        size = 10;
        it = 0;
        data = new char[size];
    }

    ~Stack()
    {
        delete[] data;
    }

    void push_back(int Value) {
        if (it == size) {
            resize();
        }
        data[it] = Value;
        ++it;
    }

    char eraseAndGet() {
        int temp = data[--it];
        return temp;
    }

    char GetLast() {
        return data[it - 1];
    }

    void resize()
    {
        size =2 *size;
        char *temp = new char[size];
        for(int i = 0; i < it; ++i)
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }

    bool checkEmpty() {
        if (it == 0)
        {
            return true;
        }
        else {
            return false;
        }
    }

private:
    char* data;
    int it;
    int size;
};

int main() {
    std::ifstream inFile("brackets.in");
    std::string str;
    std::ofstream outFile("brackets.out");
    while (std::getline(inFile,str)) {
        Stack stack;
        bool check = 1;
        for (int i = 0; i < str.size(); ++i) {
            if ((str[i] == ')' || str[i] == ']') && !stack.checkEmpty()) {
                if ((str[i] == ')' && stack.GetLast()=='(') || (str[i] == ']' && stack.GetLast() == '[')) {
                    stack.eraseAndGet();
                    continue;
                }
                else {
                    check = 0;
                    break;
                }
            }
            else {
                stack.push_back(str[i]);
            }
        }
        if (check && stack.checkEmpty()) {
            outFile << "YES\n";
        }
        else {
            outFile << "NO\n";
        }
    }
    inFile.close();
    outFile.close();
    return 0;
}
