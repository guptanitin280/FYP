//
// Created by Asus-2021 on 4/12/2023.
//

#include "aco.h"

aco::aco(Input _input):input(_input),g(_input) {
}

Output aco::run(int _max_cycles) {
    max_cycle = _max_cycles;
    vector<int> path;
    int saved = 0;
    for (int j = 0; j < max_cycle; j++) {
        //make a path for each ants
        auto min_path = findPath();
        evaporatePheromone();
        long double u = min_path.second;
        long double v = saved;
        if (min_path.second > saved) {
            saved = min_path.second;
            path = min_path.first;
        }
        replenishPheromone(u, v, path);
    }

    output.numServers = input.cacheServer;
    for (int i = 2; i < path.size(); i++) {
        output.videosServed[path[i]].push_back(path[i - 1]);
    }
    return output;
}