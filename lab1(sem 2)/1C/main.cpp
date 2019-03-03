#include <iostream>
#include <fstream>

int main() {
    int n, m;
    std::ifstream inFile("input.txt");
    inFile >> n >> m;
    bool matrix[100][100] = {false};
    std::ofstream outFile("output.txt");
    for (int i = 0; i < m ; ++i) {
        int ai, aj;
        inFile >> ai >> aj;
        if(matrix[aj-1][ai-1] || matrix[ai-1][aj-1]) {
            outFile << "YES";
            return 0;
        }
        matrix[ai-1][aj-1] = true;
    }
    inFile.close();
    outFile << "NO";
    outFile.close();
    return 0;
}