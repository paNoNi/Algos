#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <iterator>

#define INPUT_FILE "bipartite.in"
#define OUTPUT_FILE "bipartite.out"

enum {White, Green, Black};

struct Graph;
void dfs(std::vector<Graph>& , int , int , bool&);

struct Graph {
    int check_on_cycle = White;
    std::set<int> child;
    int part = 0;
    int prev = -1;
};

void condition(std::vector<Graph> &graph , int vertix, bool &dichotomy) {
    if (graph[vertix].part == 0 && vertix != 0) {
        if (graph[graph[vertix].prev].part == 1) {
            graph[vertix].part = graph[graph[vertix].prev].part + 1;
        } else {
            graph[vertix].part = graph[graph[vertix].prev].part - 1;
        }
    } else {
        if (graph[vertix].part == graph[graph[vertix].prev].part && graph[vertix].prev != -1) {
            dichotomy = false;
            return;
        }
    }
}

void topologicalSort(std::vector<Graph> &graph , bool &dichotomy) {
    for (int i = 0; i < graph.size() ; ++i) {
        if(graph[i].check_on_cycle != Black) {
            dfs(graph, i , i , dichotomy);
        }
    }
}

void dfs(std::vector<Graph> &graph , int start , int vertix , bool &dichotomy) {
    graph[vertix].check_on_cycle = Green;
    auto it = graph[vertix].child.begin();
    graph[start].part = 1;
    if (graph[vertix].child.empty()) {
        condition( graph , vertix , dichotomy );
    }
    for (int i = 0; i < graph[vertix].child.size() ; ++i, ++it) {
        graph[*it].prev = vertix;
        condition( graph , vertix , dichotomy );
        if ( graph[*it].check_on_cycle != Black && *it != graph[vertix].prev && ( graph[*it].part == 0 || graph[*it].part == graph[vertix].part)) {
            dfs( graph, start , *it , dichotomy);
            }
        }
    graph[vertix].check_on_cycle = Black;
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

int main() {

    std::ifstream infile(INPUT_FILE);
    if(!infile) {
        std::cout << "Could not open INPUT FILE!";
        return -1;
        }
    std::vector<Graph> graph;
    readFile(infile, graph);
    infile.close();

    std::ofstream outfile(OUTPUT_FILE);
    if (!outfile) {
        std::cout << "Could not open OUTPUT FILE!";
        return -1;
        }
    bool dichotomy = true;
    topologicalSort( graph , dichotomy );

    if (dichotomy) {
        outfile << "YES";
    } else {
        outfile << "NO";
        }

    outfile.close();

    return 0;
}