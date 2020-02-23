#include <iostream>
#include <fstream>
#include <vector>
#include <set>

#define INPUT_FILE "cond.in"
#define OUTPUT_FILE "cond.out"

enum {White, Green, Black};

struct Graph;
void dfs(std::vector<Graph>& , const int&, std::vector<int>& );
void dfs(std::vector<Graph>& , const int&, std::vector<int>&, int&);


struct Graph {
    int check_on_cycle = White;
    std::set<int> child;
    int component = -1;
};


void topologicalSort(std::vector<Graph> &graph, std::vector<int> &topological_sort) {
    for (int i = 0; i < graph.size() ; ++i) {
        if(graph[i].check_on_cycle != Black) {
            dfs(graph, i, topological_sort);
            }
        }
}

void topologicalSort(std::vector<Graph> &reverse_graph, std::vector<int> &main_topological_sort, int &col) {
    for (int i = reverse_graph.size() - 1; i >= 0 ; --i) {
        if(reverse_graph[main_topological_sort[i]].component == -1) {
            dfs(reverse_graph, main_topological_sort[i], main_topological_sort, col);
            ++col;
        }
    }
}

void dfs(std::vector<Graph> &main_graph , const int &vertix, std::vector<int> &main_topological_sort ) {
    main_graph[vertix].check_on_cycle = Green ;
    auto it = main_graph[vertix].child.begin();
    for (int i = 0; i < main_graph[vertix].child.size() ; ++i , ++it) {
        if ( main_graph[*it].check_on_cycle == White) {
            dfs( main_graph, *it, main_topological_sort);
            }
        }
    main_graph[vertix].check_on_cycle = Black;
    main_topological_sort.push_back(vertix);
}

void dfs(std::vector<Graph> &reverse_graph , const int &vertix, std::vector<int> &reverse_topological_sort, int &col) {
    if (reverse_graph[vertix].component == -1) {
        reverse_graph[vertix].component = col;
    }
    auto it = reverse_graph[vertix].child.begin();
    for (int i = 0; i < reverse_graph[vertix].child.size() ; ++i , ++it) {
        if ( reverse_graph[*it].component == -1) {
            dfs( reverse_graph, *it, reverse_topological_sort, col);
        }
    }
}

void readFile(std::ifstream &infile , std::vector<Graph> &main_graph, std::vector<Graph> &reverse_graph) {
    int number_of_vertixes = int();
    int number_of_edges = int();
    infile >> number_of_vertixes >> number_of_edges;
    main_graph.resize(number_of_vertixes);
    reverse_graph.resize(number_of_vertixes);
    for (int i = 0; i < number_of_edges ; ++i) {
        int temp_first_vertix, temp_second_vertix;
        infile >> temp_first_vertix >> temp_second_vertix;
        main_graph[temp_first_vertix - 1].child.insert(temp_second_vertix - 1);
        reverse_graph[temp_second_vertix - 1].child.insert(temp_first_vertix - 1);
        }
}

void outputToFile(std::ofstream &outfile, std::vector<Graph>& graph  , int number, int &col) {
    outfile << --col << '\n' ;
    for (int i = 0; i < number ; ++i) {
        outfile << graph[i].component  << ' ';
    }
}

int main() {

    std::ifstream infile(INPUT_FILE);
    if(!infile) {
        std::cout << "Could not open INPUT FILE!";
        return -1;
        }
    std::vector<Graph> main_graph;
    std::vector<Graph> reverse_graph;
    readFile(infile, main_graph, reverse_graph);
    std::vector<int> main_topological_sort;
    infile.close();

    std::ofstream outfile(OUTPUT_FILE);
    if (!outfile) {
        std::cout << "Could not open OUTPUT FILE!";
        return -1;
        }

    topologicalSort(main_graph, main_topological_sort );
    int col = 1;
    topologicalSort(reverse_graph, main_topological_sort , col );

    outputToFile(outfile, reverse_graph, main_graph.size() , col);


    outfile.close();

    return 0;
}