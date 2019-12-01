//
// Created by user on 13.04.2019.
//

#ifndef NIR_GRAPH_H
#define NIR_GRAPH_H

#include <string>
#include <vector>
#include <set>

using namespace std;


class Graph {
public:
    explicit Graph(string g6);
    virtual ~Graph();
    Graph(vector<vector<int>> graph);

    vector<vector<int>> graph;
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


private:

};


#endif //NIR_GRAPH_H
