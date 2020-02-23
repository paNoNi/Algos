#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>


#define INPUT_FILE "maxflow.in"
#define OUTPUT_FILE "maxflow.out"


class Graph {
private:


    struct Vertex {
        std::vector<int> list_num_edge;
    };

    class Edge {
    public:

        int v_start;
        int v_end;
        int flow;
        int capacity;
        int rev_edge;


        int changeFlow();

        Edge(int _v_start, int _v_end, int _capacity);

    };


private:
    unsigned int v_count, e_count;
    std::vector<Vertex> vertex_list;
    std::vector<Edge> edge_list;

    std::vector<int> findPath(int vert_u, int finish);

public:
    explicit Graph(unsigned int _v_count) {
            v_count =_v_count;
            e_count= 0;
            vertex_list = std::vector<Vertex>(v_count) ;
    }

    void pushEdge(int v_start, int v_end, int capacity);

    long long searchMaxFlow(int vertex, int finish);
};

int Graph::Edge::changeFlow() {
    return capacity - flow;
}

std::vector<int> Graph::findPath(int vert_u, int finish) {
    {
        std::queue<int> queue;
        std::vector<bool> v_used(v_count, false);
        std::vector<int> path_parent_edge(v_count, -1);
        queue.push(vert_u);

        v_used[vert_u] = true;
        bool end_flag = false;
        while(!end_flag && !queue.empty()) {
            int use = queue.front();
            queue.pop();

            for (auto _edge : vertex_list[use].list_num_edge) {

                if (!v_used[edge_list[_edge].v_end] && edge_list[_edge].changeFlow() > 0) {
                    v_used[edge_list[_edge].v_end] = true;
                    path_parent_edge[edge_list[_edge].v_end] = _edge;

                    queue.push(edge_list[_edge].v_end);
                    if (edge_list[_edge].v_end == finish) {
                        end_flag = true;
                        break;
                    }
                }
            }
        }

        if (path_parent_edge[finish] == -1) {
            return std::vector<int>(0);
        }

        std::vector<int> path;

        int use_v = finish;
        while (path_parent_edge[use_v] != -1) {
            path.push_back(path_parent_edge[use_v]);
            use_v = edge_list[path_parent_edge[use_v]].v_start;
        }
        return path;
    }
}

void Graph::pushEdge(int v_start, int v_end, int capacity) {
    ++e_count;

    edge_list.emplace_back(v_start, v_end, capacity);
    vertex_list[v_start].list_num_edge.emplace_back(edge_list.size() - 1);

    edge_list.emplace_back(v_end, v_start, 0);
    vertex_list[v_end].list_num_edge.emplace_back(edge_list.size() - 1);

    edge_list[edge_list.size() - 1].rev_edge = edge_list.size() - 2;
    edge_list[edge_list.size() - 2].rev_edge = edge_list.size() - 1;
}

long long Graph::searchMaxFlow(int vertex, int finish) {

    if (finish >= v_count || vertex < 0 || vertex >= v_count || finish < 0) {
        return -1;
    }

    std::vector<int> path = findPath(vertex, finish);
    while (!path.empty()) {

        int min_capacity = edge_list[path[0]].capacity;

        for (auto _edge : path) {
            if (edge_list[_edge].changeFlow() < min_capacity) {
                min_capacity = edge_list[_edge].changeFlow();
            }
        }

        for (auto edge_num : path) {
            long reverse_edge = edge_list[edge_num].rev_edge;

            edge_list[edge_num].flow += min_capacity;
            edge_list[reverse_edge].flow -= min_capacity;
        }

        path = findPath(vertex, finish);
    }

    int max_flow = 0;
    for (auto edge_num : vertex_list[vertex].list_num_edge) {
        max_flow += edge_list[edge_num].flow;
    }

    for (int i = 0; i < edge_list.size(); ++i) {
        edge_list[i].flow = 0;
        if (i % 2) {
            edge_list[i].capacity = 0;
        }
    }
    return max_flow;
}

Graph::Edge::Edge(int _v_start, int _v_end, int _capacity) {
    v_start = _v_start,
    v_end = _v_end,
    flow = 0 ;
    capacity = _capacity;
    rev_edge = -1;
}

int main() {
    std::ifstream infile(INPUT_FILE);

    unsigned int v_count, e_count;
    infile >> v_count >> e_count;

    Graph flows(v_count);
    for (int i = 0; i < e_count; ++i) {

        int v_start, v_end;
        int capacity;
        infile >> v_start >> v_end >> capacity;

        flows.pushEdge(v_start - 1, v_end - 1, capacity);
    }
    infile.close();

    std::ofstream outfile(OUTPUT_FILE);
    outfile << flows.searchMaxFlow(0, v_count - 1) << '\n';
    outfile.close();

    return 0;
}