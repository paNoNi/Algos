#include <iostream>
#include <fstream>
#include <string>


class Queue {
public:

    Queue() {
        size = 10;
        data = new int[size];
        it = 0;
    }

    ~Queue()
    {
        delete[] data;
    }

    void push(int Value) {
        if(it == size)
        {
            resize();
        }
        int* temp = new int[size];
        for(int i = 0 ; i < it ; ++i)
        {
            temp[i+1] = data[i];

        }
        delete[] data;
        data = temp;
        data[0] = Value;
        ++it;
    }

    int eraseAndGet() {
        int temp = data[--it];
        return temp;
    }

    void resize()
    {
        size = 2 *size;
        int *temp = new int[size];
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
    int size;
    int* data;
    int it;
};

int main() {
    std::ifstream inFile("queue.in");
    int N = 0;
    inFile >> N;
    Queue queue;
    std::ofstream outFile("queue.out");
    for (int i = 0; i < N; ++i) {
        char sign;
        inFile >> sign;
        if (sign == '+') {
            int Value = 0;
            inFile >> Value;
            queue.push(Value);
        }
        else {
            if (!queue.checkEmpty()) {
                outFile << queue.eraseAndGet() << "\n";
            }
        }
    }
    inFile.close();
    outFile.close();
    return 0;
}