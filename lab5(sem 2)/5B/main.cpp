#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#define INPUT_FILE "matching.in"
#define OUTPUT_FILE "matching.out"

class Graph {
private:
    std::vector< std::vector<char> > graph;
    std::vector<int> max_matching;

public:

    void pushEdge(int v_start,int v_end) {
        graph[v_start][v_end] = 1;
    }

    Graph(unsigned int f_share, unsigned int s_share) {
        max_matching.resize(s_share, -1);
        graph.resize(f_share);
        for (auto &c : graph)
        {
            c.resize(s_share, 0);
        }
    }

    bool dfs(int idx_n, std::vector<char> & busy, int s_share)
    {
        for (int i = 0; i < s_share; ++i)
        {
            if (graph[idx_n][i] && !busy[i])
            {
                busy[i] = 1;

                if (max_matching[i] == -1 ||
                    dfs(max_matching[i], busy, s_share))
                {
                    max_matching[i] = idx_n;
                    return true;
                }
            }
        }
        return false;
    }

    int maxMatching(int f_share, int s_share)
    {
        std::vector<char> use_matching(s_share, 0);

        for (int i = 0; i < f_share; ++i)
        {
            use_matching.assign(s_share, 0);
            dfs(i, use_matching, s_share);
        }

        return s_share - std::count(max_matching.begin(), max_matching.end(), -1);
    }

};






int main()
{
    std::ifstream infile(INPUT_FILE);

    unsigned int f_share, s_share, strings;
    infile >> f_share >> s_share >> strings;

    Graph graph(f_share,s_share);

    for (int i = 0; i < strings; ++i)
    {
        int v_start, v_end;
        infile >> v_start >> v_end;
        graph.pushEdge(--v_start, --v_end);
    }

    infile.close();

    std::ofstream outfile(OUTPUT_FILE);

    outfile << graph.maxMatching(f_share, s_share);
    outfile.close();
    return 0;
}