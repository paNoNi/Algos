#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

#define INPUT_FILE "spantree3.in"
#define OUTPUT_FILE "spantree3.out"

class Graph {
private:
    struct Edge {
        long long first_vertex;
        long long second_vertex;
        long long distance;
    };

    std::vector<Edge> edges;

public:

    void sortEdges(){
        std::sort(edges.begin(),edges.end(),[](Edge first, Edge second) {
            return first.distance < second.distance ;
        });
    }

    void pushEdge(long long first_vertex,long long second_vertex,long long distance) {
        edges.push_back({first_vertex,second_vertex,distance});
    }

    std::vector<Edge> getEdges() {
        return edges;
    }

};

class DSU
{
private:

    unsigned long long size;
    std::vector<unsigned long long> parents;
    std::vector<unsigned long long> set_size;


public:

    explicit
    DSU(unsigned long long size) : size(size)
    {
        parents.resize(size);
        set_size.resize(size, 0);
        for (size_t i = 0; i < size; ++i)
        {
            parents[i] = i;
        }
    }

    void setComp(unsigned long long first, unsigned long long second)
    {
        unsigned long long set_first = getComp(first);
        unsigned long long set_second = getComp(second);

        if (set_first == set_second)
        {
            return;
        }



        if (set_size[set_first] < set_size[set_second])
        {
            std::swap(set_first, set_second);
        }

        parents[set_second] = set_first;
        set_size[set_first] += set_size[set_second];
    }

    unsigned long long getComp(unsigned long long elem)
    {
        return elem == parents[elem] ? elem : parents[elem] = getComp(parents[elem]);
    }
};


int main()
{
    std::ifstream infile(INPUT_FILE);
    if (!infile.is_open()) {
        std::cerr << "Couldn't open the file";
    }

    Graph graph;

    unsigned long long vertex_count = 0, edge_count = 0;
    infile >> vertex_count >> edge_count;

    for (unsigned long long i = 0; i < edge_count; ++i) {
        unsigned long long first_vertex = 0, second_vertex = 0, distance = 0;
        infile >> first_vertex >> second_vertex >> distance;

        graph.pushEdge(first_vertex - 1,second_vertex-1,distance);
    }

    infile.close();

    DSU components(vertex_count);

    graph.sortEdges();

    unsigned long long minimum_st = 0;

    for (auto edge : graph.getEdges()) {
        long long first_vertex = edge.first_vertex;
        long long second_vertex = edge.second_vertex;
        long long distance = edge.distance;

        if (components.getComp(first_vertex) != components.getComp(second_vertex)) {
            components.setComp(first_vertex, second_vertex);

            minimum_st += distance;
        }
    }

    std::ofstream out_file(OUTPUT_FILE);
    out_file << minimum_st;
    out_file.close();

    return 0;
}