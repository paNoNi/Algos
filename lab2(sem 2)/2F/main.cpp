#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <stack>


#define IN_FILE_NAME "game.in"
#define OUT_FILE_NAME "game.out"


enum { White, Gray, Black };
enum { Fail, Win };

struct Graph {
    int status = Win;
    int color = White;

    std::set<int> children;
};

void gameDFS(int vertex, std::vector<Graph> &graph) {
    if (graph[vertex].color != White)
        return;

    typedef std::pair<int, std::set<int>::iterator> dfs_pair;
    std::stack<dfs_pair> stack;

    graph[vertex].color = Gray;
    stack.emplace(vertex, graph[vertex].children.begin());

    while (!stack.empty()) {
        dfs_pair temp_pair = stack.top();
        stack.pop();


        if (temp_pair.second == graph[temp_pair.first].children.end()) {
            graph[temp_pair.first].color = Black;

            graph[temp_pair.first].status = Fail;
            for (auto it = graph[temp_pair.first].children.begin();
                 it != graph[temp_pair.first].children.end(); ++it ) {
                if (graph[*it].status == Fail) {
                    graph[temp_pair.first].status = Win;
                    break;
                }
            }
        }
        else {
            stack.emplace(temp_pair.first, next(temp_pair.second));
            if (graph[*(temp_pair.second)].color == White) {
                graph[*(temp_pair.second)].color = Gray;
                stack.emplace(*(temp_pair.second), graph[*(temp_pair.second)].children.begin());
            }
        }
    }
}

int main() {
    std::ifstream infile(IN_FILE_NAME);
    if (!infile.is_open()) {
        std::cerr << "Input file open error\n";
        return -1;
    }

    int number_of_vertexes, number_of_edges, vertex_start;
    infile >> number_of_vertexes >> number_of_edges >> vertex_start;

    std::vector<Graph> graph(number_of_vertexes);
    for (int i = 0; i < number_of_edges; ++i) {
        int edge_start, edge_finish;
        infile >> edge_start >> edge_finish;
        graph[edge_start - 1].children.emplace(edge_finish - 1);
    }
    infile.close();

    std::ofstream outfile(OUT_FILE_NAME);
    if (!outfile.is_open()) {
        std::cerr << "Output file open error\n";
        return -1;
    }


    gameDFS(vertex_start - 1, graph);

    if (graph[vertex_start - 1].status == Win)
        outfile << "First player wins\n";
    else
        outfile << "Second player wins\n";

    outfile.close();

    return 0;
}

