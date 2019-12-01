//
// Created by user on 07.10.2019.
//
#include <set>
#include <algorithm>
#include "data.h"

//void anal_girth(data_t * data, std::set<int> cycles){
//    int elem_gir, elem_circle, elem_even_gir, elem_odd_gir;
//    if (cycles.empty()) {
//        elem_gir = -1;
//        elem_circle = -1;
//        elem_even_gir = -1;
//        elem_odd_gir = -1;
//    } else {
//        elem_gir = *(cycles.begin());
//        elem_circle = *(max_element(cycles.begin(), cycles.end()));
//
//        int elem = -1;
//        for (int item: cycles) {
//            if (item % 2 == 0) {
//                elem = item;
//                break;
//            }
//        }
//        elem_even_gir = elem;
//
//        elem = -1;
//        for (int item: cycles) {
//            if (item % 2 == 1) {
//                elem = item;
//                break;
//            }
//        }
//        elem_odd_gir = elem;
//    }
//
//    if (elem_gir == elem_circle && elem_gir != -1) {
//        data->vec_same.push_back(g6 + " " + to_string(elem_circle));
//        data->map_same[elem_circle]++;
//    }
//}

