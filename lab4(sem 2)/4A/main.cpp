#include <fstream>
#include <vector>
#include <limits>
#include <set>

#define INPUT_FILE "pathmgep.in"
#define OUTPUT_FILE "pathmgep.out"


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

    long long dijkstraSPF(int, int);

    unsigned long long getDistance(int vertex);

};


long long Graph::dijkstraSPF(int s_vertex, int e_vertex) {
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

    return (graph[e_vertex].way_dist == std::numeric_limits<unsigned long long>::max()) ? -1 : graph[e_vertex].way_dist;
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

    unsigned int v_count, start_v, finish_v;
    infile >> v_count >> start_v >> finish_v;

    Graph graph(v_count);


    for (int i = 0; i < v_count; ++i) {
        for (int j = 0; j < v_count; ++j) {
            unsigned long long weight;
            infile >> weight;

            if (i != j && weight != -1) {
                graph.pushEdge(i,j,weight);
                graph.pushEdge(j, i, weight);
            }
        }
    }

    infile.close();

    std::ofstream outfile(OUTPUT_FILE);
    for (int k = 0; k < v_count; ++k) {
        outfile << graph.getDistance(k) << ' ';
    }

    outfile.close();
    return 0;
}