#include <iostream>
#include <fstream>
#include <string>


class Stack {
public:

    Stack() {
        size = 10;
        data = new int[size];
        it = 0;
    }

    ~Stack()
    {
        delete[] data;
    }
    void push_back(int Value) {
        if(it == size){
            resize();
        }
        data[it] = Value;
        ++it;
    }

    int eraseAndGet() {
        int temp = data[--it];
        return temp;
    }

    void resize();

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
    int *data;
    int it;
    int size;
};

void Stack::resize()
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

int main() {
    std::ifstream inFile("stack.in");
    int N = 0;
    inFile >> N;
    Stack stack;
    std::ofstream outFile("stack.out");
    for (int i = 0; i < N; ++i) {
        char sign;
        inFile >> sign;
        if (sign == '+') {
            int Value = 0;
            inFile >> Value;
            stack.push_back(Value);
        }
        else {
            if (!stack.checkEmpty()) {
                outFile << stack.eraseAndGet() << "\n";
            }
        }
    }
    inFile.close();
    outFile.close();
    return 0;
}