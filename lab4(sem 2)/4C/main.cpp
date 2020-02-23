#include <fstream>
#include <vector>
#include <limits>
#include <set>

#define INPUT_FILE "pathbgep.in"
#define OUTPUT_FILE "pathbgep.out"



class Graph {
private:
    struct Vertex {
        unsigned long long way_dist = std::numeric_limits<unsigned long long>::max();
        std::vector< std::pair<int, unsigned int> > weight;
    };

    std::vector<Vertex> graph;

public:

    explicit Graph(unsigned int size);

    void pushEdge(int, int, unsigned long long);

    void dijkstraSPF(int);

    unsigned long long getDistance(int vertex);

};


void Graph::dijkstraSPF(int s_vertex) {
    std::set< std::pair<unsigned long long, int> > queue;
    graph[s_vertex].way_dist = 0;
    queue.insert(std::make_pair(0,s_vertex));

    while(!queue.empty()) {

        auto min_edge = *queue.begin();
        queue.erase(queue.begin());

        for (auto &child : graph[min_edge.second].weight) {

            unsigned long long way_dist_temp = graph[min_edge.second].way_dist + child.second;

            if (way_dist_temp < graph[child.first].way_dist) {
                queue.erase(std::make_pair(graph[child.first].way_dist, child.first));
                graph[child.first].way_dist = way_dist_temp;
                queue.insert(std::make_pair(graph[child.first].way_dist, child.first));
            }
        }

    }
}

void Graph::pushEdge(int s_vertex, int e_vertex, unsigned long long weight) {
    graph[s_vertex].weight.emplace_back(e_vertex,weight);
}

Graph::Graph(unsigned int size) {
    graph.resize(size);
}

unsigned long long Graph::getDistance(int vertex) {
    return graph[vertex].way_dist;
}

int main() {
    std::ifstream infile(INPUT_FILE);

    unsigned int vertex_count, edge_count;
    infile >> vertex_count >> edge_count ;

    Graph graph(vertex_count);


    for (int i = 0; i < edge_count; ++i) {
        unsigned long long weight;
        unsigned int s_edge, e_edge;
        infile >> s_edge >> e_edge >> weight;
        graph.pushEdge(--e_edge, --s_edge, weight);
        graph.pushEdge(s_edge, e_edge, weight);
    }

    infile.close();

    graph.dijkstraSPF(0);

    std::ofstream outfile(OUTPUT_FILE);
    for (int k = 0; k < vertex_count; ++k) {
        outfile << graph.getDistance(k) << ' ';
    }

    outfile.close();
    return 0;
}