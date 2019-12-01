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

void save_map(std::map<string, int> &m, std::string filename) {
    std::ofstream fout(filename);
    for (auto item: m)
        fout << item.first << " : " << item.second << std::endl;
}

#endif //NIR_UTILS_H

