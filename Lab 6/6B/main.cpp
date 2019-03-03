#include <iostream>
#include <fstream>

struct Node {
    Node* right = nullptr;
    Node* left = nullptr;
    int value = 0;
};

bool isBSTCorrect(Node *tree, int min, int max) {

    if(tree == nullptr){
        return true;
    }

    if(tree->value <= min || tree->value >= max)
        return false;

    return isBSTCorrect(tree->left, min, tree->value) && isBSTCorrect(tree->right, tree->value, max);

}



int main() {

    int count;

    std::ifstream inFile("check.in");
    inFile >> count;
    Node *tree = new Node[count];
    if (count == 0)
        tree = nullptr;
    for (int i = 0; i < count; ++i) {
        int temp_left = 0, temp_right = 0;
        inFile >> tree[i].value >> temp_left >> temp_right;

        temp_left != 0 ? tree[i].left = tree + temp_left - 1 : tree[i].left = nullptr;
        temp_right != 0 ? tree[i].right = tree + temp_right - 1 : tree[i].right = nullptr;

    }
    inFile.close();
    std::ofstream outFile("check.out");
    if (isBSTCorrect(tree, INT_MIN, INT_MAX)) {
        outFile << "YES";
    } else {
        outFile << "NO";
    }
    outFile.close();
}