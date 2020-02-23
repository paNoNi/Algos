#include <fstream>
#include <vector>
#include <limits>

#define INPUT_FILE "pathsg.in"
#define OUTPUT_FILE "pathsg.out"


class Graph {
private:

    std::vector<std::vector<unsigned long long >> graph;

public:

    explicit Graph(unsigned int size);

    void pushEdge(int, int, unsigned long long);

    void floydWarshall();

    unsigned long long getWeight(int line, int column);

};


void Graph::floydWarshall() {
    for (int k = 0; k < graph.size(); ++k) {
        for (auto &line : graph) {
            for (int j = 0; j < graph.size(); ++j) {
                line[j] = std::min(line[j], line[k] + graph[k][j]);
            }
        }
    }
}

void Graph::pushEdge(int s_vertex, int e_vertex, unsigned long long weight) {
    graph[s_vertex][e_vertex] = weight;
}

Graph::Graph(unsigned int size) {
    graph.resize(size);
    for (int i = 0; i < size ; ++i) {
        graph[i].resize(size, std::numeric_limits<long long>::max());
        graph[i][i] = 0;
    }
}

unsigned long long Graph::getWeight(int line, int column) {
    return graph[line][column];
}

int main() {
    std::ifstream infile(INPUT_FILE);

    unsigned int vertex_count, edge_count;
    infile >> vertex_count >> edge_count ;

    Graph graph(vertex_count);



    for (int i = 0; i < edge_count; ++i) {
        unsigned int s_edge, e_edge;
        unsigned long long  weight;
        infile >> s_edge >> e_edge >> weight;
        if (weight < graph.getWeight(--s_edge, --e_edge)) {
            graph.pushEdge(s_edge, e_edge, weight);
        }
    }

    infile.close();

    graph.floydWarshall();

    std::ofstream outfile(OUTPUT_FILE);

    for (int i = 0; i < vertex_count; ++i) {
        for (int j = 0; j < vertex_count; ++j) {
            outfile << graph.getWeight(i, j) << ' ';
        }
        outfile << '\n';
    }

    outfile.close();
    return 0;
}