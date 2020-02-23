#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

#define INPUT_FILE "spantree.in"
#define  OUTPUT_FILE "spantree.out"

class Graph
{
private:


    struct Point {

        int x;
        int y;

    };

    std::vector<Point> points;


public:


    void set_Point(int x, int y) {
        Point temp{x, y};
        points.push_back(temp);
    }

    double primFindMST() {
        double mst = 0;
        std::vector<double> dist(points.size(), std::numeric_limits<double>::max());
        std::vector<bool> used(points.size(), false);
        dist[0] = 0;

        for (int i = 0; i < points.size(); ++i) {
            int v = -1;
            for (int j = 0; j < points.size(); ++j) {
                if (!used[j] && (v == -1 || dist[j] < dist[v])) {
                    v = j;
                }
            }

            used[v] = true;

            for (unsigned int j = 0; j < points.size(); ++j) {
                double length = get_length( j, v );
                if (!used[j] && dist[j] > length) {
                    dist[j] = length;
                }
            }
        }

        for (auto x : dist) {
            mst += x;
        }
        return mst;
    }


    double get_length(unsigned int a, unsigned int b)
    {
        return sqrt( pow((points[b].x - points[a].x), 2) + pow((points[b].y - points[a].y), 2));
    }

};




int main()
{
    std::ifstream infile(INPUT_FILE);

    if (!infile.is_open()) {
        std::cerr << "Couldn't open the file";
    }

    unsigned int number_of_vertex;
    infile >> number_of_vertex;


    Graph graph;

    for (int i = 0; i < number_of_vertex; ++i)
    {
        int x, y;
        infile >> x >> y;
        graph.set_Point(x, y);
    }

    infile.close();

    std::ofstream outfile(OUTPUT_FILE);
    outfile << std::setprecision(15) << graph.primFindMST();
    outfile.close();

    return 0;
}