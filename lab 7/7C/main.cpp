#include <fstream>
#include <vector>
#include <queue>
#include <iostream>

struct TempNode
{
    int key;
    int child[2];

    TempNode(int key, int left, int right)
    {
        this->key = key;
        child[0] = left;
        child[1] = right;
    }
};


class AVLTree
{
private:
    struct Node
    {
        int key;
        int height;
        int num;
        Node* child[2]{};

        Node(int key, Node * left, Node * right, int num)
        {
            this->key = key;
            this->height = 1;
            this->num = num;
            child[0] = left;
            child[1] = right;
        }

        Node(TempNode * node, int num)
        {
            this->height = 1;
            this->key = node->key;
            this->num = num;
            child[0] = child[1] = nullptr;
        }
    };


    std::vector<TempNode *> inTree;
    std::vector<TempNode *> outTree;
    Node * root = nullptr;

public:

    std::vector<TempNode *> getOutTree(){
        return outTree;
    }

    void setRoot(Node* node){
        this->root = node;
    }

    Node* getRoot(){
        return this->root;
    }

    void push(int key, int left,int right){
        inTree.push_back(new TempNode(key, left-1, right-1));
    }

    void makeTree()
    {
        root = new Node(inTree[0], 0);
        dfsMake(root);
    }

    void dfsMake(Node *node)
    {
        for (int i = 0; i < 2; i++)
        {
            if (inTree[node->num]->child[i] == -1)
            {
                node->child[i] = nullptr;
            }
            else
            {
                node->child[i] = new Node(inTree[inTree[node->num]->child[i]], inTree[node->num]->child[i]);
                dfsMake(node->child[i]);
            }
        }
    }

    int countBalance(Node *node)
    {
        return (node->child[1] != nullptr ? node->child[1]->height : 0) -
               (node->child[0] != nullptr ? node->child[0]->height : 0);
    }

    void countHeight()
    {
        if (inTree.empty())
        {
            return ;
        }

        dfs(root);
    }

    void calvHeight(Node *node)
    {
        node->height = std::max(heightLeft(node), heightRight(node)) + 1;
    }

    int heightRight(Node *node)
    {
        return node->child[1] == nullptr ? 0 : node->child[1]->height;
    }

    int heightLeft(Node *node)
    {
        return node->child[0] == nullptr ? 0 : node->child[0]->height;
    }

    void dfs(Node * node)
    {
        for (auto child : node->child)
        {
            if (child != nullptr)
            {
                dfs(child);
            }
        }
        calvHeight(node);
    }

    Node * rotate(Node * node, int side)
    {
        Node * temp = node->child[side == 0 ? 1 : 0];
        node->child[side == 0 ? 1 : 0] = temp->child[side == 0 ? 0 : 1];
        temp->child[side == 0 ? 0 : 1] = node;
        calvHeight(node);
        calvHeight(temp);
        return temp;
    }

    Node * balance(Node * node)
    {
        calvHeight(node);
        if (countBalance(node) > 1)
        {

            if (countBalance(node->child[1]) < 0)
            {
                node->child[1] = rotate(node->child[1], 1);
            }
            return rotate(node, 0);
        }
        if (countBalance(node) < -1)
        {
            if (countBalance(node->child[0]) > 0)
            {
                node->child[0] = rotate(node->child[0], 0);
            }
            return rotate(node, 1);
        }
        return node;
    }

    void makeOutTree()
    {
        std::queue<Node *> queue;
        queue.push(root);
        int num = 1;
        while (!queue.empty())
        {
            Node * temp = queue.front();
            queue.pop();
            int children_num[2] = {0, 0};
            for (int i = 0; i < 2; i++)
            {
                if (temp->child[i] != nullptr)
                {
                    queue.push(temp->child[i]);
                    children_num[i] = ++num;
                }
            }
            outTree.push_back(new TempNode(temp->key, children_num[0], children_num[1]));
        }
    }

    Node * insert(Node * root, int key)
    {
        if (root == nullptr)
        {
            return new Node(key, nullptr, nullptr, inTree.size()+1);
        }
        root->child[key < root->key ? 0 : 1] = insert(root->child[key < root->key ? 0 : 1], key);
        return balance(root);
    }
};

int main()
{
    std::ifstream in("addition.in");
    std::ofstream out("addition.out");

    int n;
    in >> n;
    AVLTree tree ;

    for (int i = 0; i < n; i++)
    {
        int key;
        int left, right;
        in >> key >> left >> right;
        tree.push(key, left, right);
    }

    int key;
    in >> key;

    if (n == 0)
    {
        out << 1 << "\n" << key << " " << 0 << " " << 0 << std::endl;
        return 0;
    }

    tree.makeTree();
    tree.countHeight();
    tree.setRoot(tree.insert(tree.getRoot(), key));
    tree.makeOutTree();

    out << n + 1 << std::endl;
    for (auto c : tree.getOutTree())
    {
        out << c->key << " " << c->child[0] << " " << c->child[1] << std::endl;
    }
}
