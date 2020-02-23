#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <set>
#include <iterator>

#define INPUT_FILE "topsort.in"
#define OUTPUT_FILE "topsort.out"

enum {White, Green, Black};

struct Graph;
void dfs(std::vector<Graph>& , const int&, std::stack<int>&, bool&);
void topologicalSort(std::vector<Graph>&, std::stack<int>&, bool&);

struct Graph {
    int check_on_cycle = White;
    std::set<int> child;
};


void topologicalSort(std::vector<Graph> &graph, std::stack<int> &topological_sort, bool &check_on_cycle) {
    for (int i = 0; i < graph.size() ; ++i) {
        if(graph[i].check_on_cycle != Black) {
            dfs(graph, i, topological_sort, check_on_cycle);
        }
    }
}

void dfs(std::vector<Graph> &graph , const int &vertix, std::stack<int> &topological_sort, bool &check_on_cycle) {
    graph[vertix].check_on_cycle = Green;
    auto it = graph[vertix].child.begin();
    for (int i = 0; i < graph[vertix].child.size() ; ++i, ++it) {
        if ( graph[*it].check_on_cycle == White) {
            dfs( graph, *it, topological_sort, check_on_cycle );
        }
    }
    graph[vertix].check_on_cycle = Black;
    topological_sort.push(vertix);
}

void readFile(std::ifstream &infile , std::vector<Graph> &graph) {
    int number_of_vertixes = int();
    int number_of_edges = int();
    infile >> number_of_vertixes >> number_of_edges;
    graph.resize(number_of_vertixes);
    for (int i = 0; i < number_of_edges ; ++i) {
        int temp_first_vertix, temp_second_vertix;
        infile >> temp_first_vertix >> temp_second_vertix;
        graph[temp_first_vertix - 1].child.insert(temp_second_vertix - 1);
        graph[temp_second_vertix - 1].child.insert(temp_first_vertix - 1);
    }
}

void outputToFile(std::ofstream &outfile, std::stack<int>& topological_sort, int number) {
    for (int i = 0; i < number ; ++i) {
        outfile << topological_sort.top() + 1 << ' ';
        topological_sort.pop();
    }
}

int main() {

    std::ifstream infile(INPUT_FILE);
    if(!infile) {
        std::cout << "Could not open INPUT FILE!";
        return -1;
    }
    std::vector<Graph> graph;
    readFile(infile, graph);
    std::stack<int> topological_sort;
    infile.close();

    bool  check_on_cycle = false;
    std::ofstream outfile(OUTPUT_FILE);
    if (!outfile) {
        std::cout << "Could not open OUTPUT FILE!";
        return -1;
    }
    topologicalSort(graph, topological_sort, check_on_cycle);

    if (check_on_cycle){
        outfile << -1;
    } else {
        outputToFile(outfile, topological_sort, graph.size());
    }

    outfile.close();

    return 0;
}