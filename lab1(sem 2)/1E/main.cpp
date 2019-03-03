#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define max 2147483647

struct Vertex {
    int distance = max ;
    std::vector<int> vertofedge;
};

void bfs(Vertex *vertex) {
    std::queue<int> queue;
    queue.push(0);
    vertex[0].distance = 0;

    while (!queue.empty()) {
        int next = queue.front();
        queue.pop();

        for (int i = 0; i < vertex[next].vertofedge.size(); ++i) {
            if (vertex[vertex[next].vertofedge[i]].distance == max) {
                vertex[vertex[next].vertofedge[i]].distance = vertex[next].distance + 1;
                queue.push(vertex[next].vertofedge[i]);
            }
        }
    }
}

int main() {

    std::ifstream infile("pathbge1.in");

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

    std::ofstream outfile("pathbge1.out");

    bfs(vert);

    for (int j = 0; j < n ; ++j) {
        outfile << vert[j].distance << ' ';
    }

    outfile.close();

    delete[] vert;

    return 0;
}