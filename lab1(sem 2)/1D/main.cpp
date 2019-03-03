#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define max 2147483647

struct Vertex {
    int component = -1 ;
    std::vector<int> vertofedge;
};

void bfs(Vertex *vertex, int inc, int &num_comp) {
    std::queue<int> queue;
    queue.push(inc);

    if (vertex[inc].component == -1) {
        vertex[inc].component = ++num_comp;
    }

    while (!queue.empty()) {
        int next = queue.front();
        queue.pop();

        for (int i = 0; i < vertex[next].vertofedge.size(); ++i) {
            if (vertex[vertex[next].vertofedge[i]].component == -1) {
                vertex[vertex[next].vertofedge[i]].component = num_comp;
                queue.push(vertex[next].vertofedge[i]);
            }
        }
    }
}

int main() {

    std::ifstream infile("components.in");

    int n , m;

    infile >> n >> m;

    auto *vert = new Vertex[n];

    for (int i = 0; i < m ; ++i) {
        int ai, bi;
        infile >> ai >> bi;
        vert[--ai].vertofedge.push_back(--bi) ;
        vert[bi].vertofedge.push_back(ai);
    }

    infile.close();

    std::ofstream outfile("components.out");

    int num_comp = 0;
    for (int k = 0; k < n ; ++k) {
        bfs(vert, k, num_comp);
    }

    outfile << num_comp << "\n";
    for (int j = 0; j < n ; ++j) {
        outfile << vert[j].component << ' ';
    }

    outfile.close();

    delete[] vert;

    return 0;
}