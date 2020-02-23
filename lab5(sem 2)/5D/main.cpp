#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <utility>


#define INPUT_FILE "circulation.in"
#define OUTPUT_FILE "circulation.out"


class Graph {
private:

    class Vertex {
    public:
        std::vector<int> incident_edges_num;
        int lvl;
        int unused_incident_edge;

        Vertex();
    };

    class Edge {
    public:
        int v_start;
        int v_end;
        int capacity;
        int flow;
        bool in_net;
        long rev_edge;

        Edge(int _v_from, int _v_to, int _capacity, bool _in_net);

        int changeFlow() ;
    };

private:
    unsigned int vertex_count, edge_count;
    std::vector<Vertex> inc_list;
    std::vector<Edge> list_edge;

    void updateLVL();

    void updateUnusedEdge();

    bool updateBFS(int source, int sink) {
        updateLVL();

        std::queue<int> queue;
        queue.push(source);
        inc_list[source].lvl = 0;

        while (!queue.empty() && inc_list[sink].lvl == -1) {
            int vertex = queue.front();
            queue.pop();

            for (int edge_num : inc_list[vertex].incident_edges_num) {
                int v_next = list_edge[edge_num].v_end;
                if (inc_list[v_next].lvl == -1 && list_edge[edge_num].changeFlow() > 0) {
                    queue.push(v_next);
                    inc_list[v_next].lvl = inc_list[vertex].lvl + 1;
                }
            }
        }

        return (inc_list[sink].lvl != -1);
    }

    long long DFS(int v_start, int sink, long long inflow) {
        if (inflow == 0 || v_start == sink) {
            return inflow;
        }

        std::vector<int> &incident_edges = inc_list[v_start].incident_edges_num;
        int unused_edge_index = inc_list[v_start].unused_incident_edge;


        for (int i = unused_edge_index; i < incident_edges.size(); ++i) {

            int num_edge = incident_edges[i];
            int v_end = list_edge[num_edge].v_end;

            if (inc_list[v_end].lvl - inc_list[v_start].lvl == 1) {
                long long min_flow = inflow;
                if (list_edge[num_edge].changeFlow() < min_flow) {
                    min_flow = list_edge[num_edge].changeFlow();
                }

                long long delta = DFS(v_end, sink, min_flow);
                if (delta != 0) {
                    long revers_edge_num = list_edge[num_edge].rev_edge;
                    list_edge[num_edge].flow += delta;
                    list_edge[revers_edge_num].flow -= delta;
                    return delta;
                }
                ++inc_list[v_start].unused_incident_edge;
            }

        }
        return 0;
    }

    long long getMaxFlow(int source, int sink);

    void addEdge(int v_start, int v_end, int capacity, bool in_net) ;

public:
    typedef std::vector<std::pair<int, long long>> flowList;

    explicit Graph(int _vertex_count) ;

    void pushEdge(int v_start, int v_end, int min_flow, int capacity);

    bool getCirculation(flowList &edge_flow_list);
};

Graph::Graph(int _vertex_count){
    vertex_count = _vertex_count + 2;
    edge_count = 0;
    inc_list = std::vector<Vertex>(vertex_count + 2);
}

void Graph::addEdge(int v_start, int v_end, int capacity, bool in_net){
    ++edge_count;
    list_edge.emplace_back(v_start, v_end, capacity, in_net);
    inc_list[v_start].incident_edges_num.emplace_back(list_edge.size() - 1);

    list_edge.emplace_back(v_end, v_start, 0, false);
    inc_list[v_end].incident_edges_num.emplace_back(list_edge.size() - 1);

    list_edge[list_edge.size() - 1].rev_edge = list_edge.size() - 2;
    list_edge[list_edge.size() - 2].rev_edge = list_edge.size() - 1;
}

void Graph::pushEdge(int v_start, int v_end, int min_flow, int capacity)  {
    ++v_start;
    ++v_end;

    addEdge(0, v_end, min_flow, false);
    addEdge(v_start, v_end, capacity - min_flow, true);
    addEdge(v_start, vertex_count - 1, min_flow, false);
}

bool Graph::getCirculation(Graph::flowList &edge_flow_list){
    getMaxFlow(0, vertex_count - 1);
    for (auto &edge : list_edge) {
        if (edge.v_start == 0 && edge.flow < edge.capacity) {
            return false;
        }
    }

    edge_flow_list.clear();
    int counter = 0;
    for (int i = 0; i < list_edge.size(); ++i) {
        if (list_edge[i].in_net) {
            long long flow = list_edge[i].flow + list_edge[i - 2].capacity;

            edge_flow_list.emplace_back(counter, flow);
        }
    }
    return true;
}

void Graph::updateLVL()  {
    for (auto &elem : inc_list) {
        elem.lvl = -1;
    }
}

void Graph::updateUnusedEdge() {
    for (auto &item : inc_list) {
        item.unused_incident_edge = 0;
    }
}

long long Graph::getMaxFlow(int source, int sink)  {
    long long max_flow = 0;

    while (true) {
        if (!updateBFS(source, sink)) {
            return max_flow;
        }

        updateUnusedEdge();
        long long flow = DFS(source, sink, std::numeric_limits<long long>::max());
        while (flow != 0) {
            max_flow += flow;
            flow = DFS(source, sink, std::numeric_limits<long long>::max());
        }
    }
}

Graph::Vertex::Vertex()  {
    lvl = -1;
    unused_incident_edge = 0;

}

Graph::Edge::Edge(int _v_from, int _v_to, int _capacity, bool _in_net)  {
    v_start = _v_from;
    v_end = _v_to;
    in_net = _in_net;
    flow = 0;
    capacity = _capacity;
    rev_edge = -1;
}

int Graph::Edge::changeFlow(){
    return capacity - flow;
};

int main() {
    std::ifstream infile(INPUT_FILE);

    int vertex_count, edge_count;
    infile >> vertex_count >> edge_count;

    Graph flows(vertex_count + 2);
    for (int i = 0; i < edge_count; ++i) {
        int v_start, v_end;
        int min_flow, capacity;
        infile >> v_start >> v_end >> min_flow >> capacity;
        flows.pushEdge(v_start - 1, v_end - 1, min_flow, capacity);
    }
    infile.close();

    std::ofstream outfile(OUTPUT_FILE);

    Graph::flowList flow_list;
    if (flows.getCirculation(flow_list)) {
        outfile << "YES\n";
        for (auto &elem : flow_list) {
            outfile << elem.second << '\n';
        }
    }
    else {
        outfile << "NO\n";
    }

    outfile.close();

    return 0;
}