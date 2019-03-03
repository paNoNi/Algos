#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

#define max 2147483647

struct Vertex {
    int distance = max ;
    std::vector<int> vertofedge;
    std::string direction;
};

void bfs(Vertex *vertex,const int& start,const int& finish) {
    std::queue<int> queue;
    queue.push(start);
    vertex[start].distance = 0;



    while (!queue.empty()) {
        int next = queue.front();
        queue.pop();

        for (int i = 0; i < vertex[next].vertofedge.size(); ++i) {
            if (vertex[vertex[next].vertofedge[i]].distance == max) {
                if ( next - vertex[next].vertofedge[i] == 1 ) {
                    vertex[vertex[next].vertofedge[i]].direction = vertex[next].direction +  'L';
                }

                if ( next - vertex[next].vertofedge[i] == -1 ) {
                    vertex[vertex[next].vertofedge[i]].direction = vertex[next].direction +  'R';
                }

                if ( next - vertex[next].vertofedge[i] == 4 ) {
                    vertex[vertex[next].vertofedge[i]].direction = vertex[next].direction +  'U';
                }

                if ( next - vertex[next].vertofedge[i] == -4 ) {
                    vertex[vertex[next].vertofedge[i]].direction = vertex[next].direction + 'D';
                }

                vertex[vertex[next].vertofedge[i]].distance = vertex[next].distance + 1;
                queue.push(vertex[next].vertofedge[i]);
            }
        }
    }
}

int main() {

    std::ifstream infile("input.txt");

    unsigned int height , width;

    int start = int();
    int finish = int();

    infile >> height >> width;

    std::vector<bool> matrixoflabirint( height * width , false);
    auto *vert= new Vertex[height * width];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            char symbol;
            infile >> symbol;

            if (symbol == '.' || symbol == 'S' || symbol == 'T') {
                matrixoflabirint[i * width + j] = true;

                if (j > 0 && matrixoflabirint[i * width + j - 1]) {
                    vert[i * width + j].vertofedge.push_back(i * width + j - 1);
                    vert[i * width + j - 1].vertofedge.push_back(i * width + j);
                }

                if (i > 0 && matrixoflabirint[(i - 1) * width + j]) {
                    vert[i * width + j].vertofedge.push_back((i - 1) * width + j);
                    vert[(i - 1) * width + j].vertofedge.push_back(i * width + j);
                }

                if (symbol == 'S')
                    start = i * width + j;

                if (symbol == 'T')
                    finish = i * width + j;

            }
        }
    }
    infile.close();

    bfs(vert, start, finish);

    std::ofstream outfile("output.txt");

    if ( vert[finish].distance == max) {
        outfile << -1 ;
    } else {
        outfile << vert[finish].distance << "\n";
        outfile << vert[finish].direction;
    }

    outfile.close();

    delete[] vert;

    return 0;
}