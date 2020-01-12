#ifndef NIR_GRAPH_H
#define NIR_GRAPH_H

#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;


class Graph {
public:
    explicit Graph(string g6);
    virtual ~Graph();
    Graph(vector<vector<int>> graph);

    vector<vector<int>> graph;
    map<int, vector<vector<int>>> *color_cache;
    int n, m;



    set<int> girth();
    int komp_sv();
    int treo();
    pair<int, int> rad_diam();
    int duo();
    int exponent();
    int clique();
    int indep();
    int max_d();
    int chromatic_num();
    int chromatic_ind();
    int local_sv();
    int k_edge_connected();
    int k_vertex_connected();
    vector <int> girth_and_circle();

    void update_color_cache(map<int, vector<vector<int>>> *cache);
private:

};


#endif //NIR_GRAPH_H
