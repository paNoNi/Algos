#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <stack>


#define IN_FILE_NAME "cycle.in"
#define OUT_FILE_NAME "cycle.out"


enum { White, Gray, Black };

struct Graph {
    int color = White;
    std::set<int> children;
};

bool DFSCycle(int vertex, std::vector<Graph> &graph, std::vector<int> &cycle_order) {
    if (graph[vertex].color != White)
        return false;
    cycle_order.clear();

    typedef std::pair<int, std::set<int>::iterator> dfs_pair;
    std::stack<dfs_pair> stack;

    std::stack<int> cycle;
    cycle.emplace(vertex);
    int cycle_finish = -1;

    graph[vertex].color = Gray;
    bool cycle_flag = false;

    stack.emplace(vertex, graph[vertex].children.begin());
    while (!stack.empty()) {
        dfs_pair temp_pair = stack.top();
        stack.pop();

        if (temp_pair.second == graph[temp_pair.first].children.end()) {
            graph[temp_pair.first].color = Black;
        }
        else {
            stack.emplace(temp_pair.first, next(temp_pair.second));

            if (graph[*(temp_pair.second)].color == White) {
                graph[*(temp_pair.second)].color = Gray;
                stack.emplace(*(temp_pair.second), graph[*(temp_pair.second)].children.begin());
                cycle.emplace(*(temp_pair.second));
            }
            else if (graph[*(temp_pair.second)].color == Gray) {
                cycle_flag = true;
                cycle_finish = *(temp_pair.second);
                break;
            }
        }
    }

    if (cycle_flag) {
        while (cycle.top() != cycle_finish) {
            cycle_order.push_back(cycle.top());
            cycle.pop();
        }
        cycle_order.push_back(cycle_finish);
    }

    return cycle_flag;
}



int main() {
    std::ifstream infile(IN_FILE_NAME);
    if (!infile.is_open()) {
        std::cout << "Input file open error\n";
        return -1;
    }

    int number_of_vertex, number_of_edges;
    infile >> number_of_vertex >> number_of_edges;

    std::vector<Graph> graph(static_cast<unsigned int>(number_of_vertex));
    for (int i = 0; i < number_of_edges; ++i) {
        int edge_start, edge_finish;
        infile >> edge_start >> edge_finish;
        graph[edge_start - 1].children.emplace(edge_finish - 1);
    }
    infile.close();

    bool cycle_flag = false;
    std::vector<int> cycle_order;
    for (int i = 0 ; i < graph.size(); ++i) {
        if (DFSCycle(i, graph, cycle_order)) {
            cycle_flag = true;
            break;
        }
    }

    std::ofstream outfile(OUT_FILE_NAME);
    if (!outfile.is_open()) {
        std::cout << "Output file open error\n";
        return -1;
    }

    if (cycle_flag) {
        outfile << "YES\n";
        for (auto it = cycle_order.rbegin(); it != cycle_order.rend(); ++it)
            outfile << *it + 1 << ' ';
    }
    else {
        outfile << "NO\n";
    }
    outfile.close();

    return 0;
}
