//
// Created by OKB on 13.05.2019.
//

#ifndef NIR_MTHREAD_H
#define NIR_MTHREAD_H


#include "data.h"
#include "context.h"
#include "task_queue.h"

void consumer(data_t * data, int num) {
    for (;;) {
        task_t task;
        if (!queue_pop(&data->queue, &task)) {
            break;
        }
        Graph graph(task.task);
        set<int> cycles = graph.girth();

        int elem_gir, elem_circle, elem_even_gir, elem_odd_gir;
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
        {
            std::lock_guard<std::mutex> lock(data->queue.cnt_elem_lock);
//            set_statistic(data, task.task,  elem_gir, elem_circle, elem_even_gir, elem_odd_gir);
        }
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
    int cnt = 1;
    for (infile >> s; !infile.eof(); infile >> s, cnt++) {
        if (cnt % 10000000 == 0) {
            std::cout << cnt << " graphs has been processed." << std::endl;
            cnt = 0;
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
