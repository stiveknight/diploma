//
// Created by OKB on 13.05.2019.
//

#ifndef NIR_MTHREAD_H
#define NIR_MTHREAD_H


#include "data.h"
#include "context.h"
#include "task_queue.h"

void kek(vector<vector<int>> &colors, vector<int> &current, int max_color, int pos, int deep) {
    if (pos == deep) {
        colors.push_back(current);
        return;
    }
    for (int c = 0; c < max_color; c++) {
        int m = 0;
        for (int x = 0; x < pos; x++) {
            if (current[x] > m)
                m = current[x];
        }
        if (c > m + 1)
            continue;
        current[pos] = c;
        kek(colors, current, max_color, pos+1, deep);
    }
}

vector<vector<int>> get_colors(int deep, int max_color) {
    vector<vector<int>> colors;
    vector<int> current(deep);
    kek(colors, current, max_color, 0, deep);
    return colors;
}

map<int, vector<vector<int>>> cache_color_permutation(int n, int max_color) {
    map<int, vector<vector<int>>> result;
    for (int i = 1; i < max_color; i++) {
        result[i] = get_colors(n, i);
    }
    return result;
}

void consumer(data_t * data, int num) {
    map<string, int> result_chnum;
    // map<string, int> result_chind;
//    map<string, int> result_girth;
//    map<string, int> result_circle;
//    map<string, int> result_even_girth;
//    map<string, int> result_odd_girth;
    string filename1 = data->outdir + "chromatic_num" + data->vertex_count + "_3.txt";
//    string filename2 = data->outdir + "chromatic_ind" + data->vertex_count + "_3.txt";
//    string filename3 = data->outdir + "girth" + data->vertex_count + "_3.txt";
//    string filename4 = data->outdir + "circle" + data->vertex_count + "_3.txt";
//    string filename5 = data->outdir + "even_girth" + data->vertex_count + "_3.txt";
//    string filename6 = data->outdir + "odd_girth" + data->vertex_count + "_3.txt";
    map<int, vector<vector<int>>> cache = cache_color_permutation(stoi(data->vertex_count), stoi(data->vertex_count));
    for (int i = 1;; i++) {
        task_t task;
        if (!queue_pop(&data->queue, &task)) {
            break;
        }
        string &s = task.task;
        Graph graph(s);
        graph.update_color_cache(&cache);
        int chnum = graph.chromatic_num();
//        int chind = graph.chromatic_ind();
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
//                vector<int> g_and_c = graph.girth_and_circle();
//                int girth = g_and_c[0];
//                int circle = g_and_c[1];
//                int even_girth = g_and_c[2];
//                int odd_girth = g_and_c[3];



        //        cout << k_e_con << endl;

        result_chnum[s] = chnum;
//        result_chind[s] = chind;
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
//                result_girth[s] = girth;
//                result_circle[s] = circle;
//                result_even_girth[s] = even_girth;
//                result_odd_girth[s] = odd_girth;
        if (i % 10000 == 0) {
            // Here we dump a peace of result and drop maps for next calculations.
            std::lock_guard<std::mutex> lock(data->queue.cnt_elem_lock);
            save_map(result_chnum, filename1);
            result_chnum = map<string, int>();
//            save_map(result_girth, filename3);
//            save_map(result_circle, filename4);
//            save_map(result_even_girth, filename5);
//            save_map(result_odd_girth, filename6);
//            result_girth = map<string, int>();
//            result_circle = map<string, int>();
//            result_even_girth = map<string, int>();
//            result_odd_girth = map<string, int>();
        }
    }
    {
        std::lock_guard<std::mutex> lock(data->queue.cnt_elem_lock);
        save_map(result_chnum, filename1);
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
        if (cnt % 100000 == 0) {
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
        for (int i = 0; i < 6; i++)
        data->queue.sem_full.notify();
    }
}

#endif //NIR_MTHREAD_H
