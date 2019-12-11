#include <iostream>
#include <fstream>
#include "Graph.h"
#include "data.h"
#include "utils.h"
#include "mthread.h"
#include "context.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <time.h>
#include "Graph_analysis.cpp"

using namespace std;


void thread_mod(data_t * data) {
    std::cout << "Thread mod start" << std::endl;
    int nthreads = std::thread::hardware_concurrency();
    if(nthreads == 0)
        nthreads = 2;
    // nthreads = 4;
    std::cout << "Count of threads: " << nthreads << std::endl;
    std::vector<std::thread> threads;
    for(int i = 0; i < nthreads; i++) {
        std::thread thr(consumer, data, i);
        threads.emplace_back(std::move(thr));
    }
    producer(data);
    data->queue.stop_push = 1;

    for(auto& thr : threads) {
        thr.join();
    }

    std::cout << "Done!" << std::endl;
}


void single_mod(data_t * data) {
    ifstream infile(data->infilename);
    if (!infile) {
        cout << "NO" << endl;
        exit(EXIT_FAILURE);
    }
    std::string s;
    for (infile >> s; !infile.eof(); infile >> s) {
//        cout << s << endl;
        Graph g(s);

        int m = g.m;
        int max_d = g.max_d();
//        int chnum = g.chromatic_num();
//        int chind = g.chromatic_ind();
//        int komp_sv = g.komp_sv();
//        int treo = g.treo();
//        pair<int,int> rd = g.rad_diam();
//        int duo = g.duo();
//        int exponent = g.exponent();
//        int clique = g.clique();
//        int indep = g.indep();
//        int local_sv = g.local_sv();
//        int k_e_con = g.k_edge_connected();
//        int k_v_con = g.k_vertex_connected();
//        vector<int> g_and_c = g.girth_and_circle();
//        int girth = g_and_c[0];
//        int circle = g_and_c[1];
//        int even_girth = g_and_c[2];
//        int odd_girth = g_and_c[3];



//        cout << k_e_con << endl;

//        data->result_chnum[s] = chnum;
//        data->result_chind[s] = chind;
////
//
//        data->result_komp_sv[s] = komp_sv;
//        if (komp_sv == 1)
//            data->result_sv[s] = 1;
//        else
//            data->result_sv[s] = 0;
//        data->result_treo[s] = treo;
//        data->result_rad[s] = rd.first;
//        data->result_diam[s] = rd.second;
//        data->result_duo[s] = duo;
//        data->result_exponent[s] = exponent;
//        if (exponent == 0)
//            data->result_primitive[s] = 0;
//        else
//            data->result_primitive[s] = 1;

//        data->result_clique[s] = clique;
//        data->result_indep[s] = indep;
        data->result_m[s] = m;
        data->result_max_d[s] = max_d;

//        data->result_local_sv[s] = local_sv;
//        data->result_k_edge_connected[s] = k_e_con;
//        data->result_k_vertex_connected[s] = k_v_con;
//        data->result_girth[s] = girth;
//        data->result_circle[s] = circle;
//        data->result_even_girth[s] = even_girth;
//        data->result_odd_girth[s] = odd_girth;


    }
}



void run(data_t * data) {
    switch (data->multithread_mode) {

        case TM_SINGLE:
            single_mod(data);
            break;
        case TM_MULTI:
            thread_mod(data);
            break;
    }

//

//    save_map(data->result_chnum, data->outdir + "chromatic_num" + data->vertex_count + ".txt");
//    save_map(data->result_chind, data->outdir + "chromatic_ind" + data->vertex_count + ".txt");
//    save_map(data->result_sv, data->outdir + "component" + data->vertex_count + ".txt");
//    save_map(data->result_komp_sv, data->outdir + "amount_component" + data->vertex_count + ".txt");
//    save_map(data->result_treo, data->outdir + "treo" + data->vertex_count + ".txt");
//    save_map(data->result_rad, data->outdir + "radius" + data->vertex_count + ".txt");
//    save_map(data->result_diam, data->outdir + "diameter" + data->vertex_count + ".txt");
//    save_map(data->result_duo, data->outdir + "bipartite" + data->vertex_count + ".txt");
//    save_map(data->result_exponent, data->outdir + "exponent" + data->vertex_count + ".txt");
//    save_map(data->result_primitive, data->outdir + "primitive" + data->vertex_count + ".txt");
//    save_map(data->result_clique, data->outdir + "clique" + data->vertex_count + ".txt");
//    save_map(data->result_indep, data->outdir + "independent_num" + data->vertex_count + ".txt");
    save_map(data->result_m, data->outdir + "m" + data->vertex_count + ".txt");
    save_map(data->result_max_d, data->outdir + "max_d" + data->vertex_count + ".txt");
//    save_map(data->result_local_sv, data->outdir + "local_sv" + data->vertex_count + ".txt");
//    save_map(data->result_k_edge_connected, data->outdir + "k_edge_connected" + data->vertex_count + ".txt");
//    save_map(data->result_k_vertex_connected, data->outdir + "k_vertex_connected" + data->vertex_count + ".txt");


//    save_map(data->result_girth, data->outdir + "girth" + data->vertex_count + ".txt");
//    save_map(data->result_circle, data->outdir + "circle" + data->vertex_count + ".txt");
//    save_map(data->result_even_girth, data->outdir + "even_girth" + data->vertex_count + ".txt");
//    save_map(data->result_odd_girth, data->outdir + "odd_girth" + data->vertex_count + ".txt");
}


int main(int argc, char *argv[]) {

    clock_t start_time = clock();
    data_t data;

    data_init(&data, argc, argv);

    run(&data);


    std::cout << "\ntime: " << ((float)(clock() - start_time)) / CLOCKS_PER_SEC << std::endl;
    return 0;
}