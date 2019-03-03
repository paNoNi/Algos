#include <iostream>
#include <fstream>
#include <string>

class Stack {
public:

    Stack() {
        size = 10;
        it = 0;
        data = new int[size];
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

    void resize()
    {
        size =2 *size;
        int *temp = new int[size];
        for(int i = 0; i < it; ++i)
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }

    int eraseAndGet() {
        int temp = data[--it];
        return temp;
    }

    int getLast() {
        return data[it - 1];
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

    int getSize() {
        return it;
    }


private:
    int size;
    int* data;
    int it;
};


int main() {
    std::ifstream inFile("postfix.in");
    std::ofstream outFile("postfix.out");
    Stack stack;
    char symbol ;
    inFile >> symbol;
    while (symbol != EOF ) {
        if (symbol == '+' || symbol == '-' || symbol == '*') {
            if (stack.getSize()>1)
            {
                if (symbol == '+')
                {
                    stack.push_back(stack.eraseAndGet() + stack.eraseAndGet());
                }
                if (symbol == '-')
                {
                    int temp = stack.eraseAndGet() - stack.eraseAndGet();
                    temp = -temp;
                    stack.push_back(temp);
                }
                if (symbol == '*')
                {
                    stack.push_back(stack.eraseAndGet() * stack.eraseAndGet());
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            stack.push_back(symbol - '0');
        }
        inFile >> symbol;
    }
    outFile << stack.getLast();
    inFile.close();
    outFile.close();
    return 0;
}