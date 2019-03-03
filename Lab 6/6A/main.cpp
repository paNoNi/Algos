#include <iostream>
#include <fstream>

struct Node {
    int right;
    int left;
    int value;
};

int heightCalculate(Node* tree, int count, int it){

    int left_height = 0;
    int right_height = 0;
    int  height = 0;

    if ( count == 0 )
        return height;

    if(tree[it].left != 0){
        left_height += heightCalculate(tree, count, tree[it].left - 1);
    }

    if(tree[it].right != 0){
        right_height += heightCalculate(tree, count, tree[it].right - 1);
    }

    if( left_height > right_height) {
        height = left_height;
    } else {
        height = right_height;
    }

    ++height;

    return height;
}


int main() {
    int count;
    std::ifstream inFile("height.in");
    inFile >> count;
    Node *tree = new Node[count];
    for (int i = 0; i < count ; ++i) {
        inFile >> tree[i].value;
        inFile >> tree[i].left;
        inFile >> tree[i].right;
    }
    inFile.close();
    std::ofstream outFile("height.out");
    outFile << heightCalculate(tree, count, 0);
    outFile.close();
}