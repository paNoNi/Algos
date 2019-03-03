#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <stack>


#define IN_FILE_NAME "hamiltonian.in"
#define OUT_FILE_NAME "hamiltonian.out"


enum { White, Gray, Black };

struct Graph {
    int color = White;
    std::set<int> child;
};

bool dfsTopSort(int vertex, std::vector<Graph> &graph, std::vector<int> &visit_order) {
    if (graph[vertex].color != White)
        return true;

    typedef std::pair<int, std::set<int>::iterator> dfs_pair;
    std::stack<dfs_pair> stack;

    graph[vertex].color = Gray;

    bool cycle_flag = false;
    stack.emplace(vertex, graph[vertex].child.begin());
    while (!stack.empty()) {
        dfs_pair temp_pair = stack.top();
        stack.pop();

        if (temp_pair.second == graph[temp_pair.first].child.end()) {
            graph[temp_pair.first].color = Black;
            visit_order.push_back(temp_pair.first);
        }
        else {
            stack.emplace(temp_pair.first, next(temp_pair.second));

            if (graph[*(temp_pair.second)].color == White) {
                graph[*(temp_pair.second)].color = Gray;
                stack.emplace(*(temp_pair.second), graph[*(temp_pair.second)].child.begin());
            }
            else if (graph[*(temp_pair.second)].color == Gray) {
                cycle_flag = true;
            }
        }
    }

    return !cycle_flag;
}

int main() {
    std::ifstream infile(IN_FILE_NAME);
    if (!infile.is_open()) {
        std::cerr << "Input file open error\n";
        return -1;
    }

    int number_of_vertexes, number_of_edges;
    infile >> number_of_vertexes >> number_of_edges;

    std::vector<Graph> graph(number_of_vertexes);
    for (int i = 0; i < number_of_edges; ++i) {
        int temp_first_vert, temp_second_vert;
        infile >> temp_first_vert >> temp_second_vert;
        graph[temp_first_vert - 1].child.emplace(temp_second_vert - 1);
    }
    infile.close();

    std::ofstream outfile(OUT_FILE_NAME);
    if (!outfile.is_open()) {
        std::cerr << "Output file open error\n";
        return -1;
    }

    std::vector<int> visit_order;
    for (int i = 0 ; i < graph.size(); ++i) {
        dfsTopSort(i, graph, visit_order);
    }

    bool hamiltonian = true;
    for (auto it = visit_order.rbegin(); it != prev(visit_order.rend()); ++it) {
        if (graph[*it].child.find(*next(it)) == graph[*it].child.end()) {
            hamiltonian = false;
            break;
        }
    }

    outfile << (hamiltonian ? "YES" : "NO");

    outfile.close();

    return 0;
}
