#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <limits>
#include <queue>


#define INPUT_FILE "decomposition.in"
#define OUTPUT_FILE "decomposition.out"


class Graph {
private:
    struct Vertex {
        std::vector<int> list_num_edges;
        int level;
        int unused_incident_edge;

        Vertex() {
            level = -1;
            unused_incident_edge = 0;

        }
    };

    struct Edge {
        int v_start;
        int v_end;
        int capacity;
        int flow;
        int rev_edge;
        int ind;

        int changeFlow();

        Edge(int _v_start, int _v_end, int _ind, int _capacity);

    };

private:
    unsigned int vertex_count;
    unsigned int edge_count;
    std::vector<Vertex> inc_list;
    std::vector<Edge> edge_list;

    void updateLVL();

    void updateUnusedEdge();

    void updateFlows();

    bool upgradeBFS(int source, int sink);

    long long DFS(int v_start, int sink, long long inflow);

    long long getMaxFlow(int source, int sink);

public:
    explicit Graph(unsigned int _v_count);

    void pushEdge(int v_start, int v_end, int capacity);

    void decomposition(int source, int sink, std::vector<std::pair<long long, std::list<int>>>& decomp);
};

void Graph::updateLVL() {
    for (auto &elem : inc_list) {
        elem.level = -1;
    }
}

void Graph::updateUnusedEdge() {
    for (auto &elem : inc_list) {
        elem.unused_incident_edge = 0;
    }
}

void Graph::updateFlows() {
    for (int i = 0; i < edge_list.size(); ++i) {
        edge_list[i].flow = 0;
        if (i % 2) {
            edge_list[i].capacity = 0;
        }
    }
}

bool Graph::upgradeBFS(int source, int sink)  {
    updateLVL();

    std::queue<int> queue;
    queue.push(source);
    inc_list[source].level = 0;

    while (!queue.empty() && inc_list[sink].level == -1) {
        int vertex = queue.front();
        queue.pop();

        for (int edge_num : inc_list[vertex].list_num_edges) {
            int v_next = edge_list[edge_num].v_end;
            if (inc_list[v_next].level == -1 && edge_list[edge_num].changeFlow() > 0) {
                queue.push(v_next);
                inc_list[v_next].level = inc_list[vertex].level + 1;
            }
        }
    }

    return (inc_list[sink].level != -1);
}

long long Graph::DFS(int v_start, int sink, long long inflow)  {
    if (inflow == 0 || v_start == sink) {
        return inflow;
    }

    std::vector<int> &incident_edges = inc_list[v_start].list_num_edges;
    int unused_edge_index = inc_list[v_start].unused_incident_edge;


    for (int i = unused_edge_index; i < incident_edges.size(); ++i) {

        int num_edge = incident_edges[i];
        int v_end = edge_list[num_edge].v_end;

        if (inc_list[v_end].level - inc_list[v_start].level == 1) {
            long long min_flow = inflow;
            if (edge_list[num_edge].changeFlow() < min_flow) {
                min_flow = edge_list[num_edge].changeFlow();
            }

            long long delta = DFS(v_end, sink, min_flow);
            if (delta != 0) {
                long _num_rev_edge = edge_list[num_edge].rev_edge;
                edge_list[num_edge].flow += delta;
                edge_list[_num_rev_edge].flow -= delta;
                return delta;
            }
            ++inc_list[v_start].unused_incident_edge;
        }

    }
    return 0;
}

Graph::Graph(unsigned int _v_count) {
    vertex_count = _v_count;
    edge_count = 0;
    inc_list = std::vector<Vertex>(vertex_count);
}

long long Graph::getMaxFlow(int source, int sink) {
    long long max_flow = 0;

    while (true) {
        if (!upgradeBFS(source, sink)) {
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

void Graph::pushEdge(int v_start, int v_end, int capacity) {
    ++edge_count;

    edge_list.emplace_back(v_start, v_end, edge_count, capacity);
    inc_list[v_start].list_num_edges.emplace_back(edge_list.size() - 1);

    edge_list.emplace_back(v_end, v_start, -edge_count, 0);
    inc_list[v_end].list_num_edges.emplace_back(edge_list.size() - 1);

    edge_list[edge_list.size() - 1].rev_edge = edge_list.size() - 2;
    edge_list[edge_list.size() - 2].rev_edge = edge_list.size() - 1;
}

void Graph::decomposition(int source, int sink, std::vector<std::pair<long long, std::list<int>>> &decomp) {
    getMaxFlow(source, sink);

    long long decomp_flow = 0;
    std::list<int> decomp_e_list;

    do {
        decomp_flow = 0;  // flow
        int v_start = source;
        std::vector<bool> in_decomp(vertex_count);

        while (!in_decomp[v_start]) {
            if (v_start == sink) {
                break;
            }

            int edge_id = 0;
            for (auto item : inc_list[v_start].list_num_edges) {
                if (edge_list[item].flow > 0 && edge_list[item].ind > 0) {
                    edge_id = edge_list[item].ind;
                }
            }

            if (!edge_id) {
                decomp_e_list.clear();
                break;
            }

            decomp_e_list.push_back(edge_id);
            in_decomp[v_start] = true;
            v_start = edge_list[(edge_id - 1) * 2].v_end;
        }

        if (in_decomp[v_start]) {
            while (edge_list[(decomp_e_list.front() - 1) * 2].v_start != v_start) {
                decomp_e_list.pop_front();
            }
        }

        if (decomp_e_list.empty()) {
            break;
        }

        decomp_flow = std::numeric_limits<long long>::max();
        for (int edge_id : decomp_e_list) {
            if (edge_list[(edge_id - 1) * 2].flow < decomp_flow) {
                decomp_flow = edge_list[(edge_id - 1) * 2].flow;
            }
        }

        for (int edge : decomp_e_list) {
            edge_list[(edge - 1) * 2].flow -= decomp_flow;
        }

        if (decomp_flow != std::numeric_limits<long long>::max()) {
            decomp.emplace_back(decomp_flow, std::move(decomp_e_list));
            decomp_e_list = std::list<int>();
        }
    } while (true);

    updateUnusedEdge();
    updateLVL();
    updateFlows();
}

int Graph::Edge::changeFlow() {
        return capacity - flow;
}

Graph::Edge::Edge(int _v_start, int _v_end, int _ind, int _capacity) {
        v_start = _v_start;
        v_end = _v_end;
        ind = _ind;
        flow = 0;
        capacity = _capacity;
        rev_edge = -1;
}

int main() {
    std::ifstream infile(INPUT_FILE);

    unsigned int vertex_count, edge_count;
    infile >> vertex_count >> edge_count;

    Graph flows(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int v_start, v_end;
        int capacity;
        infile >> v_start >> v_end >> capacity;

        flows.pushEdge(--v_start, --v_end, capacity);
    }
    infile.close();

    std::ofstream outfile(OUTPUT_FILE);

    std::vector<std::pair<long long, std::list<int>>> dec_list;
    flows.decomposition(0, --vertex_count, dec_list);

    outfile << dec_list.size() << '\n';

    for (auto &elem : dec_list) {
        outfile << elem.first << ' ' << elem.second.size() << ' ';
        for (auto &edge : elem.second) {
            outfile << edge << ' ';
        }
        outfile << '\n';
    }
    outfile.close();

    return 0;
}