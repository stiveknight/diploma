//
// Created by OKB on 13.05.2019.
//

#ifndef NIR_MTHREAD_H
#define NIR_MTHREAD_H


#include "data.h"
#include "context.h"
#include "task_queue.h"

void consumer(data_t * data, int num) {
    map<string, int> result_chnum;
    map<string, int> result_chind;
    string filename1 = data->outdir + "chromatic_num" + data->vertex_count + "_1.txt";
    string filename2 = data->outdir + "chromatic_ind" + data->vertex_count + "_2.txt";
    for (int i = 1;; i++) {
        task_t task;
        if (!queue_pop(&data->queue, &task)) {
            break;
        }
        string &s = task.task;
        Graph graph(s);
        int chnum = graph.chromatic_num();
        int chind = graph.chromatic_ind();
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

        result_chnum[s] = chnum;
        result_chind[s] = chind;
        //
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
        //        data->result_clique[s] = clique;
        //        data->result_indep[s] = indep;
        //        data->result_m[s] = m;
        //        data->result_local_sv[s] = local_sv;
        //        data->result_k_edge_connected[s] = k_e_con;
        //        data->result_k_vertex_connected[s] = k_v_con;
        //        data->result_girth[s] = girth;
        //        data->result_circle[s] = circle;
        //        data->result_even_girth[s] = even_girth;
        //        data->result_odd_girth[s] = odd_girth;
        if (i % 10000 == 0) {
            // Here we dump a peace of result and drop maps for next calculations.
            std::lock_guard<std::mutex> lock(data->queue.cnt_elem_lock);
            save_map(result_chnum, filename1);
            save_map(result_chind, filename2);
            result_chnum = map<string, int>();
            result_chind = map<string, int>();
        }
    }
    {
        std::lock_guard<std::mutex> lock(data->queue.cnt_elem_lock);
        save_map(result_chnum, filename1);
        save_map(result_chind, filename2);
    }
    queue_cancel(&data->queue);
    std::cout << "thread " << num << " ended" << std::endl;
}

void producer(data_t * data) {
    std::ifstream infile(data->infilename);
    if (!infile) {
        std::cout << "param -f: filename is not correct" << std::endl;
        raise(-1);
    }
    std::string s;
    long long cnt = 1;
    for (infile >> s; !infile.eof(); infile >> s, cnt++) {
        if (cnt % 10000 == 0) {
            std::cout << "Line: " << cnt << " Current graph: " << s << std::endl;
        }
        task_t task = {
                .task = s,
        };
        queue_push(&data->queue, &task);
    }
    data->queue.stop_push = 1;

    {
        while (!data->queue.q.empty()) {
            // TODO(menc): look at this shit. maybe rewrite this later..
        }
        //for (int i = 0; i < 4; i++)
        data->queue.sem_full.notify();
    }
}

#endif //NIR_MTHREAD_H
