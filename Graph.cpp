//
// Created by user on 13.04.2019.
//

#include <iostream>
#include <set>
#include <queue>
#include <cassert>
#include <algorithm>
//#include <wingdi.h>
#include "Graph.h"

const int INF = 1000000000;
Graph::~Graph() = default;

void print_graph(Graph *g){
    for (int i = 0; i < g->graph.size(); i++) {
        cout << endl;
        for (int j = 0; j < g->graph.size(); j++)
            cout << g->graph[i][j] << ' ';
    }
    cout << endl;
}

Graph::Graph(string g6) {
    int n = (int(g6[0]) - 63);
    this->n = n;
    this->m = 0;
    vector<vector<int>> result(n, vector<int>(n, 0));

    int row = 0;
    int col = 1;
    for (int i = 1; i < g6.size(); i++) {
        int ch = g6[i] - 63;
        int bit = 0;
        for (int ibit = 5; ibit >= 0; --ibit) {
            bit = (ch >> ibit) & 1;
            result[row][col] = bit;
            result[col][row] = bit;
            row++;
            if (row == col) {
                row = 0;
                col++;
            }

            if (col == n) {

                this->graph = result;
//                print_graph(this);
                for (int ii = 0; ii < result.size(); ii++) {
                    for (int j = 0; j < result.size(); j++)
                        if (result[ii][j] == 1)
                            m++;
                }

//                cout << m << endl;

                m /= 2;
//                cout << m << endl;

                return;
            }
        }
    }

    this->graph = vector<vector<int> >();

}

Graph::Graph(vector<vector<int>> graph) {
    this->graph = graph;

}


void dfs(Graph *g, int v, vector<int> &used, vector<int> &p, set<int> &cycle) { //поиск в глубину
    used[v] = 1;
    for (int i = 0; i < g->graph[v].size(); i++) {
        if (g->graph[v][i] == 1) {
            int k = 0;
            int to = i;
            if (used[to] == 0) {
                p[to] = v;
                dfs(g, to, used, p, cycle);
            }
            else if (used[to] == 1 && to != p[v]) {
                int star = to;
                int fin = v;
                k = 0;
                for (int j = fin; j != star; j = p[j])
                    k++;
                cycle.insert(k + 1);
            }
        }
    }
    used[v] = 0;
}


set<int> Graph::girth() {
    vector<int> used;
    vector<int> p;
    int n = int(this->graph.size());
    set<int> cycle;
    for (int i = 0; i < n; i++) {
        p.push_back(-1);
        used.push_back(0);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            p[j] = -1;
            used[j] = 0;
        }
        dfs(this, i, used, p, cycle);
    }
    return cycle;

}

void dfs_1(vector<vector<int>> &g, int v, vector<int> &used) {
    used[v] = 1;
    for (int i = 0; i < g.size(); i++) {
        if (g[v][i] == 1) {
            int to = i;
            if (used[to] == 0)
                dfs_1(g, to, used);
        }
    }
}

int Graph::komp_sv() { // количество компонент связности
    int n = int(this->graph.size());
    vector<int> used(n, 0);

    int komp = 0;
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            dfs_1(this->graph, i, used);
            komp++;
        }
    }
    return komp;
}

int Graph::treo() { // количество треугольников
    int n = int(this->graph.size());
    int cnt = 0;
    for (int a = 0; a < n; a++)
        for (int b = a + 1; b < n; b++)
            for (int c = b + 1; c < n; c++)
                if (this->graph[a][b] != 0 && this->graph[b][c] != 0 && this->graph[a][c] != 0)
                    cnt++;
    return cnt;
}

pair<int, int> Graph::rad_diam() { // радиус и диаметр
    int n = this->n;
    vector<vector<int>> d(this->graph);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (d[i][j] == 0) {
                if (i != j)
                    d[i][j] = INF;
            }
        }
    }

    vector <int> e(n);
    int rad = INF, diam = 0;
    for (int t = 0; t < n; t++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                d[u][v] = min(d[u][v], d[u][t] + d[t][v]);

    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++)
            if (d[u][v] == INF)
                d[u][v] = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            e[i] = max(e[i], d[i][j]);

    for (int i = 0; i < n; i++) {
        rad = min(rad, e[i]);
        diam = max(diam, e[i]);
    }

    return make_pair(rad, diam);
}

void bfs(Graph *g, vector <int> &dolya, vector <int> &used, int s, bool &ok) { // поиск в ширину
    queue<int> q;
    q.push(s);
    used[s] = 1;
    dolya[s] = 1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < g->n; i++) {
            if (g->graph[v][i] == 1) {
                int to = i;
                if (used[to] == 0) {
                    used[to] = 1;
                    if (dolya[v] == 1)
                        dolya[to] = 2;
                    else
                        dolya[to] = 1;
                    q.push(to);
                }
                else if (dolya[v] == dolya[to]) {
                    ok = false;
                    return;
                }
            }
        }
    }
}

int Graph::duo() {
    int n = this->n;
    bool ok = true;
    vector <int> dolya(n, 0);
    vector <int> used(n, 0);

    for (int i = 0; i < n; i++) {
        if (!ok)
            return -1;
        else if (used[i] == 0)
            bfs(this, dolya, used, i, ok);
    }
    if (ok)
        return 1;

    else
        return -1;
}

int Graph::exponent() {
    int n = this->n;
    int e = 1;
    assert(n > 2);
    int emax = 2*(n-1);
    vector<vector<int> > gg(graph);
    vector<vector<int> > c(n, vector<int>(n));

    bool b = true;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 0) {
                b = false;
                break;
            }
        }
    }
    if (b)
        return e;


    bool bb;
    for (int i = 2; i <= emax; i++) {
        for (int j = 1; j < i; j++) {
            for (int ii = 0; ii < n; ii++) {
                for (int jj = 0; jj < n; jj++) {
                    c[ii][jj] = 0;
                    for (int k = 0; k < n; k++) {
                        c[ii][jj] += graph[ii][k] * gg[k][jj];
                    }
                }
            }
        }
        gg = c;
        bb = true;
        for (int ii = 0; ii < n && bb; ii++) {
            for (int jj = 0; jj < n; jj++) {
                if (c[ii][jj] == 0) {
                    bb = false;
                    break;
                }
            }
        }
        if (bb)
            return i;

    }
    return 0;
}

void extend(set<int> comsub, set<int> &max_comsub, set <int> candidates, set<int> nety, vector<vector<int> > &gg) {
    // алгоритм брона-кербоша

    while (!candidates.empty()) {
        set <int> new_candidates;
        set <int> new_not;
        bool b = false;
        int cnt = 0;
        for (int i = 0; i < nety.size(); i++) {
            cnt = 0;
            for (int item: candidates)
                if (gg[i][item] == 1)
                    cnt++;
            if (cnt == candidates.size())
                b = true;
        }
        if (b)
            return;

        int v = *candidates.begin();
        comsub.insert(v);
        for (int item : candidates) {
            if (gg[v][item] == 1)
                new_candidates.insert(item);
        }

        for (int item: nety) {
            if (gg[v][item] == 1)
                new_not.insert(item);
        }
        if (new_candidates.empty() && new_not.empty()) { // получается comsub - клика
            if (comsub.size() > max_comsub.size())
                max_comsub = comsub;
        }
        else
            extend(comsub, max_comsub, new_candidates, new_not, gg);

        set <int> tmp_candidates;
        set <int> tmp_comsub;
        nety.insert(v);
        for (int item: comsub){
            if (item != v)
                tmp_comsub.insert(item);
        }
        comsub = tmp_comsub;

        for (int item : candidates) {
            if (item != v)
                tmp_candidates.insert(item);
        }
        candidates = tmp_candidates;
    }

}

int Graph::clique() { //максимальная клика
    int n = this->n;
    set <int> nety, comsub, max_comsub, candidates;
    for (int i = 0; i < n; i++)
        candidates.insert(i);
    extend(comsub, max_comsub, candidates, nety, graph);
    int ans = int(max_comsub.size());
    return ans;
}

int Graph::indep() { // число независимости
    int n = this->n;
    set <int>  candidates, comsub, max_comsub, nety;
    vector <vector<int> > dop_g(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (graph[i][j] == 0)
                    dop_g[i][j] = 1;
                else
                    dop_g[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < n; i++)
        candidates.insert(i);
    extend(comsub, max_comsub, candidates, nety, dop_g);
    int ans = int(max_comsub.size());
    return ans;
}

int Graph::max_d(){ // максимальная степень вершины
    int n = this->n;
    int ans = 0, k = 0;

    for (int i = 0; i < n; i++){
        k = 0;
        for (int j = 0; j < n; j++){
            if (graph[i][j] == 1)
                k += 1;
        }
        if (k > ans)
            ans = k;
    }
    return ans;
}


bool dfs_chrom(Graph *g, int v, vector<int> &colors, int value) {
    for (int c = 0; c < value; c++) {
        bool tmp = true;
        for (int i = 0; i < g->graph[v].size(); i++) {
            if (g->graph[v][i] == 1)
                if (colors[i] == c) {
                    tmp = false;
                    break;
                }
        }
        if (!tmp)
            continue;

        colors[v] = c;

        for (int item: colors)
            if (item == -1)
                return true;

        for (int i = 0; i < g->graph[v].size(); i++) {
            if (g->graph[v][i] == 1)
                if (colors[i] == -1) {
                    if (dfs_chrom(g, i, colors, value))
                        return true;
                }
        }
        colors[v] = -1;
    }
    return false;
}



int Graph::chromatic_num(){
    int n = this->n;
    int m = this->m;

    if (m == n*(n-1)/2)
        return n;

    if (this->duo() == 1)
        return 2;


    set<int> cycles = this->girth();
    bool tmp = true;
    for (int item: cycles){
        if (item % 2 == 1)
            tmp = false;
    }
    if (tmp){
        return 2;
    }

    int inf = this->clique();

    int sup = 1 + this->max_d();



    for (int value = inf; value <= sup; value++) {
        vector<int> colors(n, -1);
        bool res;
        for (int i = 0; i < n; i++) {
            res = dfs_chrom(this, i, colors, value);
            if (res)
                break;

        }

        if (res)
            return value;
    }
    return -1;
}



int get_available_color(vector<vector<int> > &used, int u, int v, int max_color) {
    int n = int(used.size());
    for (int c = 1; c < max_color+1; c++) {
        bool bad_color = false;
        for (int i = 0; i < n; i++) {
            // Если цвет с уже поюзан, то переходим к следующему
            if (used[u][i] == c) {
                bad_color = true;
                break;
            }
        }

        if (bad_color)
            continue;

        // Тоже самое, только для другоо конца ребра
        for (int i = 0; i < n; i++) {
            // Если цвет с уже поюзан, то переходим к следующему
            if (used[v][i] == c) {
                bad_color = true;
                break;
            }
        }

        if (bad_color)
            continue;

        return c;
    }
    return -1;
}


bool dfs(int u, vector<vector<int> > &used, int max_color) {
    int n = int(used.size());
    // Проверяем, что в used нет нулей -> значит граф покрасился, выходим из рекурсии
    bool cool = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (used[i][j] == 0) {
                cool = false;
                // goto используется для выхода из двойного цикла
                goto x;
            }
        }
    }
    x:

    if (cool)
        return true;

    for (int v = 0; v < n; v++) {
        if (used[u][v] == 0) {
            int color = get_available_color(used, u, v, max_color);
            if (color == -1)
                return false;

            used[u][v] = color;
            used[v][u] = color;
            if (dfs(v, used, max_color))
                return true;
            // Обнуляем, чтобы попробовать другие цвета для этого ребра
//            used[u][v] = 0;
//            used[v][u] = 0;
        }
    }
    return false;
}



int Graph::chromatic_ind(){
    int ans = this->max_d();
//    cout << ans;
    if (this->duo() == 1)
        return ans;


    vector<vector<int>> used(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (this->graph[i][j] == 1) {
                used[i][j] = 0;
            }
        }
    }

    if (dfs(0, used, ans)) {
        return ans;
    }
    return ans+1;
}

bool is_sv(vector<vector<int>> g) { // связный?
    int n = int(g.size());
    vector<int> used(n, 0);

    int komp = 0;
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            dfs_1(g, i, used);
            komp++;
        }
    }
    return komp == 1;

}

bool surroundings(Graph *g, int n){
    vector<int> sur;
    for (int i = 0; i < g->graph.size(); i++)
        if (g->graph[n][i] == 1)
            sur.push_back(i);
//    cout << sur.size() << endl;
    vector<int> mapping(g->n, 0);
    for (int i = 0; i < sur.size(); i++)
        mapping[sur[i]] = i;

    int new_x, new_y;
    vector<vector<int>> new_matrix(sur.size(), vector<int>(sur.size(), 0));
    for (int i = 0; i < g->graph.size(); i++)
        for (int j = 0; j < g->graph.size(); j++) {
            int tmp1 = count(sur.begin(), sur.end(), i);
            int tmp2 = count(sur.begin(), sur.end(), j);
//            cout << tmp1 << " " << tmp2 << endl;
            if (tmp1 != 0 && tmp2 != 0) {
                new_x = mapping[i];
                new_y = mapping[j];
                new_matrix[new_x][new_y] = 1;
                new_matrix[new_y][new_x] = 1;
            }
        }
    return is_sv(new_matrix);
}


int Graph::local_sv(){
    int n = this->n;

    for (int i = 0; i < n; i++)
         if (!surroundings(this, i))
             return 0;
    return 1;
}

bool bfs_flow(Graph *g, int s, int t, vector<int> &p){
    int n = int(g->graph.size());
    queue<int> q;
    q.push(s);
    vector<bool> used(n);
    vector<int> d(n);
    used[s] = true;
    p[s] = -1;
    while (!q.empty()){
        int v = q.front();
        q.pop();
        for (int to = 0; to < g->graph[v].size(); ++to){
            if (!used[to] && g->graph[v][to] == 1){
                used[to] = true;
                q.push(to);
                d[to] = d[v] + 1;
                p[to] = v;

                if (to == t)
                    return true;
            }

        }
    }
    return false;
}


int max_flow(Graph *g, int v1, int v2){
    int n = int(g->graph.size());
    int flow = 0;
    vector<int> p(n, -1);
    vector<int> used(n, 0);
    Graph new_g = Graph(g->graph);
    while (bfs_flow(&new_g, v1, v2, p)){
        vector<int> path;
        for (int v=v2; v != -1; v=p[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size()-1; i++){
            new_g.graph[path[i]][path[i+1]] = 0;
            new_g.graph[path[i+1]][path[i]] = 0;
        }
        flow += 1;
        fill(p.begin(), p.end(), -1);
    }
    return flow;
}



int Graph::k_vertex_connected() {
    int n = static_cast<int>(graph.size());
    if (is_sv(graph)) {
        vector<vector<int>> ng(2*n, vector<int>(2*n, 0));
//        int x[4] = {0, n, n, 0};
//        int y[4] = {0, n, 0, n};
        for (int i = 0; i < n; i++) {
            ng[i][i+n] = 1;
            for (int j = 0; j < n; j++){
                ng[n + i][j] = graph[i][j];
            }
        }
        for (int i = 0; i< n; i++) {
            ng[i][i + n] = 1;
            ng[i+n][i] = 1;
        }


        Graph new_g = Graph(ng);
//        print_graph(&new_g);

        int ans = INF;
        for (int i = n; i < new_g.graph.size(); i++)
            for (int j = 0; j < n; j++)
                if (i != j)
                    ans = min(ans, max_flow(&new_g, i, j));
        return ans;
    }
    else
        return 0;

}

int Graph::k_edge_connected() {
    if (is_sv(graph)) {
        int ans = INF;
        for (int i = 0; i < graph.size(); i++)
            for (int j = i + 1; j < graph.size(); j++)
                if (i != j)
                    ans = min(ans, max_flow(this, i, j));
        return ans;
    }
    else
        return 0;
}


vector<int> Graph::girth_and_circle(){
    int elem_gir, elem_circle, elem_even_gir, elem_odd_gir;
    set <int> cycles = this->girth();
    if (cycles.empty()) {
        elem_gir = -1;
        elem_circle = -1;
        elem_even_gir = -1;
        elem_odd_gir = -1;
    } else {
        elem_gir = *(cycles.begin());
        elem_circle = *(max_element(cycles.begin(), cycles.end()));

        int elem = -1;
        for (int item: cycles) {
            if (item % 2 == 0) {
                elem = item;
                break;
            }
        }
        elem_even_gir = elem;

        elem = -1;
        for (int item: cycles) {
            if (item % 2 == 1) {
                elem = item;
                break;
            }
        }
        elem_odd_gir = elem;
    }

    vector <int> ans;
    ans.push_back(elem_gir);
    ans.push_back(elem_circle);
    ans.push_back(elem_even_gir);
    ans.push_back(elem_odd_gir);

    return ans;
}