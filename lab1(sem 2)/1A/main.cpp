#include <iostream>
#include <fstream>

int main() {
    std::ifstream inFile("input.txt");
    int n, m;
    inFile >> n >> m;
    bool matrix[100][100] = {false};
    for (int i = 0; i < m ; ++i) {
            int ai, aj;
            inFile >> ai >> aj;
            if ((ai <= n && aj <= n) && (ai > 0 && aj > 0))
            matrix[ai-1][aj-1] = true;
    }
    inFile.close();
    std::ofstream outFile("output.txt");
    for (int k = 0; k < n ; ++k) {
        for (int i = 0; i < n ; ++i) {
            outFile << matrix[k][i] << " " ;
        }
        outFile << "\n" ;
    }
    outFile.close();
    return 0;
}