#include <iostream>
#include <fstream>
#include <vector>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

struct Vertix {
    std::vector<int> child;
};

int main() {

    std::ifstream infile(INPUT_FILE);
    if(!infile.is_open()){
        std::cerr << "Could not open INPUT FILE";
    }

    int number_of_vertexes = int();
    int number_of_edges = int();
    infile >> number_of_vertexes >> number_of_edges;

    std::vector<Vertix> graph(number_of_vertexes);
    for (int i = 0; i < number_of_edges ; ++i) {
        int first_vert, second_vert;
        infile >> first_vert >> second_vert;
        graph[first_vert - 1].child.push_back(second_vert - 1);
        graph[second_vert - 1].child.push_back(first_vert - 1);
    }
    infile.close();

    std::ofstream outfile(OUTPUT_FILE);
    if (!outfile.is_open()) {
        std::cerr << "Could not open OUTPUT FILE";
    }

    for (auto &vertex : graph) {
        outfile << vertex.child.size() << ' ';
    }
    outfile.close();

    return 0;
}