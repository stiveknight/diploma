//
// Created by user on 12.05.2019.
//

#ifndef NIR_UTILS_H
#define NIR_UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <map>

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

void save_map(std::map<string, int> &m, const std::string& filename) {
    std::ofstream fout(filename, std::ofstream::out | std::ofstream::app);
    for (const auto& item: m) {
        fout << item.first << " : " << item.second << endl;
    }
    fout.close();
}

void save_map_and_clear(std::map<string, int> &m, const std::string& filename) {
    save_map(m, filename);
    m = map<string, int>();
}

void dump_state(data_t * data) {
    save_map(data->result_chnum, data->outdir + "chromatic_num" + data->vertex_count + "_1.txt");
    save_map(data->result_chind, data->outdir + "chromatic_ind" + data->vertex_count + "_1.txt");
//    save_map(data->result_sv, data->outdir + "component" + data->vertex_count + ".txt");
//    save_map(data->result_komp_sv, data->outdir + "amount_component" + data->vertex_count + ".txt");
//    save_map(data->result_treo, data->outdir + "treo" + data->vertex_count + ".txt");
//    save_map(data->result_rad, data->outdir + "radius" + data->vertex_count + ".txt");
//    save_map(data->result_diam, data->outdir + "diameter" + data->vertex_count + ".txt");
//    save_map(data->result_duo, data->outdir + "bipartite" + data->vertex_count + ".txt");
//    save_map(data->result_exponent, data->outdir + "exponent" + data->vertex_count + ".txt");
//    save_map(data->result_clique, data->outdir + "clique" + data->vertex_count + ".txt");
//    save_map(data->result_indep, data->outdir + "independent_num" + data->vertex_count + ".txt");
//    save_map(data->result_m, data->outdir + "m" + data->vertex_count + ".txt");
//    save_map(data->result_local_sv, data->outdir + "local_sv" + data->vertex_count + ".txt");
//    save_map(data->result_k_edge_connected, data->outdir + "k_edge_connected" + data->vertex_count + ".txt");
//    save_map(data->result_k_vertex_connected, data->outdir + "k_vertex_connected" + data->vertex_count + ".txt");
//    save_map(data->result_m, data->outdir + "m" + data->vertex_count + ".txt");
//    save_map(data->result_max_d, data->outdir + "max_d" + data->vertex_count + ".txt");

//    save_map(data->result_girth, data->outdir + "girth" + data->vertex_count + ".txt");
//    save_map(data->result_circle, data->outdir + "circle" + data->vertex_count + ".txt");
//    save_map(data->result_even_girth, data->outdir + "even_girth" + data->vertex_count + ".txt");
//    save_map(data->result_odd_girth, data->outdir + "odd_girth" + data->vertex_count + ".txt");

    // Clear data
    data->gir = vector<int>();
    data->circle = vector<int>();
    data->even_gir = vector<int>();
    data->odd_gir = vector<int>();

//    map<int, int> map_gir;
//    map<int, int> map_circle;
//    map<int, int> map_even_gir;
//    map<int, int> map_odd_gir;
    data->result_chnum = map<string, int>();
    data->result_chind = map<string, int>();
    data->result_sv = map<string, int>();
    data->result_komp_sv = map<string, int>();
    data->result_treo = map<string, int>();
    data->result_rad = map<string, int>();
    data->result_diam = map<string, int>();
    data->result_duo = map<string, int>();
    data->result_exponent = map<string, int>();
    data->result_clique = map<string, int>();
    data->result_indep = map<string, int>();
    data->result_m = map<string, int>();
    data->result_local_sv = map<string, int>();
    data->result_k_edge_connected = map<string, int>();
    data->result_k_vertex_connected = map<string, int>();
    data->result_girth = map<string, int>();
    data->result_circle = map<string, int>();
    data->result_even_girth = map<string, int>();
    data->result_odd_girth = map<string, int>();
}

#endif //NIR_UTILS_H

