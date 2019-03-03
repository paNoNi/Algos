#include <iostream>
#include<fstream>
#include <string>

using std::ifstream;
using std::ofstream;
using std::string;

class PriorityQueue {
public:

    PriorityQueue()
    {
        counter_push = 0;
        it = 0;
        size_array = 10;
        p_queue = new data[size_array];
    }

    ~PriorityQueue()
    {
        delete[] p_queue;
    }

    void set_counter_push() {
    this->counter_push++;
}

    void push(int value);

    bool check_empty();

    void resize_data();

    int extract_min();

    void decrease_key(int x, int y);

private:

    typedef struct
    {
        int value;
        int counter;
    } data ;

    int it;

    int counter_push;

    data *p_queue;

    int size_array;
};

void PriorityQueue::decrease_key(int x, int y){
    for (int i = 0; i < it; ++i) {
        if (p_queue[i].counter == x){
            p_queue[i].value = y;
            break;
        }
    }
}

int PriorityQueue::extract_min()
{
    int temp_min = p_queue[0].value;
    int i_temp = 0;
    for(int i = 0 ; i < it ; ++i) {
        if (p_queue[i].value < temp_min) {
            temp_min = p_queue[i].value;
            i_temp = i;
        }
    }

    for (int j = i_temp; j < it-1 ; ++j) {
        p_queue[j] = p_queue[j+1];
    }
    --it;
    return temp_min;
}

bool PriorityQueue::check_empty()
{
    if (it == 0){
        return 1;
    } else {
        return 0;
    }
}

void PriorityQueue::push(int value)
{
    if (it == size_array){
        resize_data();
    }
    p_queue[it].value = value;
    p_queue[it].counter = counter_push;
    ++it;
}
void PriorityQueue::resize_data()
{
    size_array = 2 * size_array;
    data *temp = new data[size_array];
    for (int i = 0; i < this->it; ++i)
    {
        temp[i] = p_queue[i];
    }
    data *temp_2 = p_queue;
    this->p_queue = temp;
    delete[] temp_2;
}


int main() {
    string str;
    PriorityQueue pqueue;
    ifstream inFile("priorityqueue.in");
    ofstream outFile("priorityqueue.out");
     while (inFile >> str )
    {
         pqueue.set_counter_push();

        if (str == "push")
        {
            long long value;

            inFile >> value;
            pqueue.push(value);
        }
        if (str == "extract-min")
        {
            if (pqueue.check_empty())
            {

                outFile << '*' << "\n";
            }
            else
            {
                outFile << pqueue.extract_min() << "\n";
            }
        }
        if (str == "decrease-key")
        {
            int it;
            long value;
            inFile >> it >> value;
            pqueue.decrease_key(it, value);
        }
    }
    inFile.close();
    outFile.close();
    return 0;
}

