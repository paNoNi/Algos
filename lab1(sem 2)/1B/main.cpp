#include <iostream>
#include <fstream>

bool check(bool matrix[100][100], int& n) {
    for (int i = 0; i < n ; ++i) {
        for (int j = i; j < n ; ++j) {
            if( matrix[i][j] != matrix[j][i] || (i == j && matrix[i][j] == 1))
                return false;
        }
    }
    return true;
}

int main() {
    bool matrix[100][100] = {false};
    std::ifstream inFile("input.txt");
    int n;
    inFile >> n;
    for (int i = 0; i < n ; ++i) {
        for (int j = 0; j < n ; ++j) {
            inFile >> matrix[i][j];
        }
    }
    std::ofstream outFile("output.txt");
    if (check(matrix, n)) {
        outFile << "YES";
    } else {
        outFile << "NO";
    }
    outFile.close();
    return 0;
}