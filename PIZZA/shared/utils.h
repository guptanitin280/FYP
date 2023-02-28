//
// Created by risha on 14-02-2023.
//

#ifndef FYP_UTILS_H
#define FYP_UTILS_H

#include <bits/stdc++.h>
#include <string> //std::string
#include <vector> //std::vector

std::mt19937  rng(std::chrono::steady_clock::now().time_since_epoch().count());
uint32_t rand(uint32_t x,uint32_t y);
double get_probability();

std::vector<std::string> intersection(std::vector<std::string> v1,
                                      std::vector<std::string> v2);

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(std::vector<bool> x) const;
};

#endif //FYP_UTILS_H
