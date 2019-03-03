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
        Node* child[2];

        Node(TempNode * node, int num)
        {
            this->height = 0;
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

    void buildTree()
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
        return (node->child[1] != nullptr ? node->child[1]->height : 0) - (node->child[0] != nullptr ? node->child[0]->height : 0);
    }

    void countHeight()
    {
        if (inTree.empty())
        {
            return ;
        }

        custHeight(root);
    }

    void calcHeight(Node *node)
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

    void custHeight(Node *node)
    {
        for (auto child : node->child)
        {
            if (child != nullptr)
            {
                custHeight(child);
            }
        }
        calcHeight(node);
    }

    Node * rotate(Node * node, int side)
    {
        Node * temp = node->child[side == 0 ? 1 : 0];
        node->child[side == 0 ? 1 : 0] = temp->child[side == 0 ? 0 : 1];
        temp->child[side == 0 ? 0 : 1] = node;
        calcHeight(node);
        calcHeight(temp);
        return temp;
    }

    Node* balance(Node * node)
    {
        if (countBalance(node->child[1]) < 0)
        {
            node->child[1] = rotate(node->child[1], 1);
        }
        return rotate(node, 0);
    }

    void buildOutputTree()
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
};

int main()
{
    std::ifstream in("rotation.in");
    std::ofstream out("rotation.out");

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

    tree.buildTree();

    tree.countHeight();

    tree.setRoot(tree.balance(tree.getRoot()));

    tree.buildOutputTree();

    out << n << std::endl;
    for (auto c : tree.getOutTree())
    {
        out << c->key << " " << c->child[0] << " " << c->child[1] << std::endl;
    }
}
