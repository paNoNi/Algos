#include <fstream>
#include <vector>


class AVLTree
{
private:
    struct Node
    {
        int key;
        int child[2]{};
        int height;

        Node(int key, int left, int right)
        {
            this->key = key;
            this->height = 0;
            child[0] = left;
            child[1] = right;
        }
    };
    std::vector<Node *> tree;

public:

    int getSize(){
        return tree.size();
    }

    void push(int key, int left, int right) {
        tree.push_back(new Node(key, left-1, right-1));
    }

    int balance(int it)
    {
        return (tree[it]->child[1] != -1 ? tree[tree[it]->child[1]]->height : 0) -
                (tree[it]->child[0] != -1 ? tree[tree[it]->child[0]]->height : 0);
    }

    void counterHeight()
    {
        if (tree.empty())
        {
            return ;
        }

        dfs(tree[0]);
    }

    int heightRight(Node *node)
    {
        return node->child[1] == -1 ? 0 : tree[node->child[1]] -> height;
    }

    int heightLeft(Node *node)
    {
        return node->child[0] == -1 ? 0 : tree[node->child[0]] -> height;
    }

    void dfs(Node * node)
    {
        for (int child : node->child)
        {
            if (child != -1)
            {
                dfs(tree[child]);
            }
        }
        node->height = std::max(heightLeft(node), heightRight(node)) + 1;
    }
};

int main()
{
    std::ifstream inFile("balance.in");
    std::ofstream outFile("balance.out");
    AVLTree tree;

    int n;
    inFile >> n;

    for (int i = 0; i < n; i++)
    {
        int key;
        int left, right;
        inFile >> key >> left >> right;
        tree.push(key, left, right);
    }

    tree.counterHeight();

    for (int i = 0; i < tree.getSize(); i++)
    {
        outFile << tree.balance(i) << std::endl;
    }
}
