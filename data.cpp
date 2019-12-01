//
// Created by user on 12.05.2019.
//

#include <iostream>
#include <getopt.h>
#include <string.h>
#include "data.h"


int data_init(data_t * data, int argc, char *argv[]) {
    data->outdir = "../result/";
    queue_init(&data->queue);
    if (argc > 1){
        data->multithread_mode = TM_SINGLE;
        int correct = 0;
        const char *opt_string = "n:msf:";
        for (;;) {
            int opt = getopt(argc, argv, opt_string);
            if (-1 == opt)
                break;
            switch (opt) {
                case 'n':
                    data->vertex_count = optarg;
                case 'm':
                    data->multithread_mode = TM_MULTI;
                    break;
                case 's':
                    data->multithread_mode = TM_SINGLE;
                    break;
                case 'f':
                    data->infilename = optarg;
                    correct = 1;
                    break;
                default:
                    printf("Incorrect arguments.\n! -f <filename> = filename with graphs\n  -m = multithread mod\n  -s = single mod\n");
                    return (EXIT_FAILURE);
            }
        }
        if (correct == 0) {
            printf("Incorrect arguments.\n! -f <filename> = filename with graphs\n  -m = multithread mod\n  -s = single mod\n");
            exit(EXIT_FAILURE);
        }

        return (EXIT_SUCCESS);
    } else {
        printf("Enter count of vertex: ");
        std::cin >> data->vertex_count;
        string dir = "../files/";
        string name = "graphs" + data->vertex_count + ".txt";
        data->infilename = dir + name;
        string s;
        printf("Enter thread mod [s/m]: ");
        cin >> s;
        if (s == "m") {
            data->multithread_mode = TM_MULTI;
        } else {
            data->multithread_mode = TM_SINGLE;
        }
    }

    return (EXIT_SUCCESS);
}