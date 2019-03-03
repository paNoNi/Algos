#include <iostream>
#include <fstream>
#include <string>

class BST {
private:

    class Node {
    public:
        Node* left = nullptr;
        Node* right = nullptr;
        int value = 0;
    };
    Node* head = nullptr;

    Node* minimum_all(BST::Node*);

public:

    Node* insert(Node*, const int&);

    Node* search(Node*, const int&);

    Node* remove(Node*, const int&);

    Node* getHead();

    Node* minimum(Node*, const int&, BST::Node*);

    Node* maximum(Node*, const int&, BST::Node*);

};



BST::Node* BST::maximum(BST::Node* node, const int &value,BST::Node* prev) {
    if (node == nullptr)
        return prev;
    if (node->value < value) {
        if (prev != nullptr) {
            if (node->value > prev->value) {
                prev = node;
            }
        } else {
            prev = node;
        }
    }
    if (value <= node->value) {
        return maximum(node->left, value, prev);
    }
    else {

        return maximum(node->right, value, prev);
    }
}

BST::Node*  BST::minimum(BST::Node* node, const int &value, BST::Node* next) {
    if (node == nullptr)
        return next;
    if (node->value > value) {
        if (next != nullptr) {
            if (node->value < next->value)
                next = node;
        } else {
            next = node;
        }
    }
    if (value < node->value) {
        return minimum(node->left, value, next);
    }
    else {

        return minimum(node->right, value, next);
    }
}

BST::Node*  BST::minimum_all(BST::Node* node){
    if (node->left == nullptr)
        return node;
    return minimum_all(node->left);
}

BST::Node* BST::getHead() {
    return head;
};

BST::Node* BST::remove(Node* node, const int& value) {
    if (node == nullptr)
        return node;
    if (value < node->value) {
        node->left = remove(node->left, value);
    }
    else if (value > node->value) {
        node->right = remove(node->right, value);
    }
    else if (node->left != nullptr && node->right != nullptr) {
        if(node == head) {
            head->value = minimum_all(head->right)->value;
            head->right = remove(head->right, head->value);
        } else {
            node->value = minimum_all(node->right)->value;
            node->right = remove(node->right, node->value);
        }

    }
    else
    if (node->left != nullptr) {
        if(node == head) {
            head = head->left;
        } else {
            node = node->left;
        }
    }
    else {
        if(node == head) {
            head = head->right;
        } else {
            node = node->right;
        }
    }
    return node;
}

BST::Node* BST::search(Node* node, const int& value) {
    if (node == nullptr || value == node->value)
    return node;
    if (value < node->value) {
        return search(node->left, value);
    }
    else {
        return search(node->right, value);
    }
}

BST::Node* BST::insert(Node* node,const int& value){
    if (node == nullptr) {
        if(head == nullptr) {
            Node* temp = new Node;
            temp->value = value;
            head = temp;
        }
        return node;
    }else if (value < node->value) {
        node->left = insert(node->left, value);
        if(node->left == nullptr) {
            Node* temp = new Node;
            temp->value = value;
            node->left = temp;
        }
    }
    else if (value > node->value) {
        node->right = insert(node->right, value);
        if (node->right == nullptr) {
            Node *temp = new Node;
            temp->value = value;
            node->right = temp;
        }
    }

    return node;
}

int main(){
    std::ifstream inFile("bstsimple.in");
    std::ofstream outFile("bstsimple.out");
    std::string line;
    BST tree;
    while (inFile >> line) {
        if(line == "insert") {
            int value = 0;
            inFile >> value;
            tree.insert(tree.getHead(),value);
        } else if (line == "delete"){
            int value = 0;
            inFile >> value;
            tree.remove(tree.getHead(), value);
        } else if (line == "exists") {
            int value = 0;
            inFile >> value;
            tree.search(tree.getHead(), value) != nullptr ? outFile << "true\n" : outFile << "false\n";
        } else if (line == "next") {
            int value = 0;
            inFile >> value;
            if (tree.minimum(tree.getHead(), value, nullptr) != nullptr) {
                outFile << tree.minimum(tree.getHead(), value, nullptr)->value << "\n";
            } else {
                outFile << "none\n";
            }
        } else if (line == "prev") {
            int value = 0;
            inFile >> value;
            if (tree.maximum(tree.getHead(), value, nullptr) != nullptr) {
                outFile << tree.maximum(tree.getHead(), value, nullptr)->value << "\n";
            } else {
                outFile << "none\n";
            }
        }
    }
    inFile.close();
    return 0;
}