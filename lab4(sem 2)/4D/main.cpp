#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <limits>
#include <vector>
#include <stack>


#define INPUT_FILE "path.in"
#define OUTPUT_FILE "path.out"


class Graph {
private:
    struct Vertex {
    public:
        std::vector<int> child;
        __int64 length_min_way;
        bool min_way;

        Vertex() {
            length_min_way = std::numeric_limits<__int64>::max();
            min_way = true;
        }
    };


    std::map< std::pair<int, int>, long long > list_edges;

    std::vector<Vertex> graph;

public:

    bool checkMinWay(int vertex);

    __int64 getLength(int vertex);

    void pushEdge(int s_vertex, int e_vertex, long long weight);

    explicit Graph(unsigned int vertex_count) {
        graph.resize(vertex_count);
    }

    void bellmanFord(int);
};


void Graph::bellmanFord(int s_vertex) {

    graph[s_vertex].length_min_way = 0;

    std::stack<int> stack;

    for (int i = 0; i < graph.size(); ++i) {
        for (auto &edge : list_edges) {

            if (graph[edge.first.first].length_min_way != std::numeric_limits<__int64>::max() &&
                graph[edge.first.second].length_min_way > graph[edge.first.first].length_min_way + edge.second) {

                graph[edge.first.second].length_min_way = std::max(std::numeric_limits<__int64>::min(),
                                                    graph[edge.first.first].length_min_way + edge.second);

                if (i == graph.size() - 1) {
                    stack.push(edge.first.second);
                }
            }
        }
    }

    std::vector<bool> used(graph.size(), false);
    while(!stack.empty()) {
        int use_vertex = stack.top();
        stack.pop();

        used[use_vertex] = true;
        graph[use_vertex].min_way = false;

        for (auto vertex : graph[use_vertex].child) {
            if (!used[vertex]) {
                stack.push(vertex);
            }
        }
    }
}

void Graph::pushEdge(int s_vertex, int e_vertex, long long weight) {
    auto temp_pair = std::make_pair(s_vertex - 1, e_vertex - 1);

    auto it = list_edges.find(temp_pair);
    if (it == list_edges.end()) {
        list_edges.emplace(temp_pair, weight);
        graph[s_vertex - 1].child.push_back(e_vertex - 1);
    }
    else if (it->second > weight) {
        list_edges[temp_pair] = weight;
    }
}


__int64 Graph::getLength(int vertex ) {
    return graph[vertex].length_min_way;
}

bool Graph::checkMinWay(int vertex) {
    return graph[vertex].min_way;
}

int main() {
    std::ifstream infile(INPUT_FILE);

    unsigned int vertex_count, edge_count, s_vertex;
    infile >> vertex_count >> edge_count >> s_vertex;

    Graph graph(vertex_count);

    for (int i = 0; i < edge_count; ++i) {
        unsigned int s_edge, e_edge;
        long long weight;

        infile >> s_edge >> e_edge >> weight;

        graph.pushEdge(s_edge,e_edge,weight);

    }
    infile.close();

    graph.bellmanFord(--s_vertex);

    std::ofstream outfile(OUTPUT_FILE);
    for (int i = 0; i < vertex_count; ++i) {
        if (graph.getLength(i) == std::numeric_limits<__int64>::max()) {
            outfile << '*' << '\n';
        }
        else if (graph.checkMinWay(i)) {
            outfile << graph.getLength(i) << '\n';
        }
        else {
            outfile << '-' << '\n';
        }
    }
    outfile.close();
    return 0;
}
