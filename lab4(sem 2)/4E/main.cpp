#include <fstream>
#include <map>
#include <limits>
#include <vector>
#include <algorithm>


#define INPUT_FILE "negcycle.in"
#define OUTPUT_FILE "negcycle.out"


class Graph {
private:
    struct Vertex {
        long long distance;
        int parent;

        Vertex() {

            distance = std::numeric_limits<int>::max();
            parent = -1;

        };
    };

    std::vector<int> cycle;

    std::map< std::pair<int, int>, long long > edge_list;

    std::vector<Vertex> graph;

public:

    std::vector<int> getCycle();

    void pushEdge(int s_edge, int e_edge, long long weight);

    int getSizeCycle();

    explicit Graph(unsigned int size) {
        graph.resize(size);
    }

    bool bellmanFordCycle();
};

    bool Graph::bellmanFordCycle() {

        int finish_cycle = -1;
        graph[0].distance = 0;

        for (int i = 0; i < graph.size(); ++i) {
            for (auto &edge : edge_list) {
                int s_edge = edge.first.first;
                int e_edge = edge.first.second;
                long long weight = edge.second;

                if (graph[e_edge].distance > graph[s_edge].distance + weight) {
                    graph[e_edge].distance = graph[s_edge].distance + weight;
                    graph[e_edge].parent = s_edge;

                    if (i == graph.size() - 1) {
                        finish_cycle = e_edge;
                    }
                }
            }
        }

        cycle.clear();

        if (finish_cycle != -1) {

            for (int i = 0; i < graph.size(); ++i) {
                finish_cycle = graph[finish_cycle].parent;
            }

            int v_look = finish_cycle;
            while (v_look != graph[finish_cycle].parent || cycle.size() <= 1) {
                cycle.push_back(v_look);
                v_look = graph[v_look].parent;
            }

            std::reverse(cycle.begin(), cycle.end());
            return true;
        }
        return false;
    }

int Graph::getSizeCycle() {
    return cycle.size();
}

void Graph::pushEdge(int s_edge, int e_edge,long long weight) {
    edge_list.emplace(std::make_pair(s_edge, e_edge), weight);
}

std::vector<int> Graph::getCycle() {
    return cycle;
}

int main() {
    std::ifstream infile(INPUT_FILE);

    unsigned int vertex_count;
    infile >> vertex_count;

    Graph graph(vertex_count);

    for (int i = 0; i < vertex_count; ++i) {
        for (int j = 0; j < vertex_count; ++j) {;
            long long weight;
            infile >> weight;

            if (abs(weight) <= 10000) {
                graph.pushEdge(i, j ,weight);
            }
        }
    }

    infile.close();

    std::ofstream outfile(OUTPUT_FILE);
    if (graph.bellmanFordCycle()) {
        outfile << "YES\n" << graph.getSizeCycle() << '\n';
        std::vector<int> cycle = graph.getCycle();
        for (int i = 0; i < graph.getSizeCycle() ; ++i) {
            outfile << cycle[i] + 1 << ' ';
        }
    }
    else {
        outfile << "NO\n";
    }
    outfile.close();
    return 0;
}
