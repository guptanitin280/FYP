//
// Created by Asus-2021 on 4/12/2023.
//

#include "aco.h"
#include "../shared/Score.h"

ofstream aco::ff;
aco::aco(Input _input,initializingAlgo _algo):input(_input),g(_input),algo(_algo) {
    output.numServers = input.cacheServer;
    output.numVideos = input.videos;
    output.videosServed.resize(output.numServers + 1, vector<bool>(input.videos, false));
}

Output aco::run(long long _max_cycles) {
    initialisePheromone();
    max_cycle = _max_cycles;
    vector<long long> path;
    long long maxScore = 0;


    for (long long j = 0; j < max_cycle; j++) {
        //make a path for each ants
        auto min_path = findPath();
        evaporatePheromone();

        long double u = min_path.second;
        long double v = maxScore;
        if (min_path.second > maxScore) {
            maxScore = min_path.second;
            path = min_path.first;
        }
        replenishPheromone(u, v, path);
        ff << j + 1 << " " << calculateScore(path) << endl;
    }

    return output;
}


long long aco::calculateScore(vector<long long> &path) {
    for (long long i = 0; i <= output.numServers; i++) {
        for (long long j = 0; j < output.numVideos; j++) {
            output.videosServed[i][j] = false;
        }
    }
    for (long long i = 2; i < path.size(); i += 2) {
        output.videosServed[path[i]][input.requestsDescription[path[i - 1]][0]] = true;
    }
    return Score::calculate(input, output);
}

bool aco::isValid() {
    for (long long cacheServer_id = 1; cacheServer_id <= input.cacheServer; cacheServer_id++) {
        long long filled_cap = 0;
        for (long long video_id = 0; video_id < input.videos; video_id++) {
            if (output.videosServed[cacheServer_id][video_id]) {
                filled_cap += input.videoSizes[video_id];
            }
        }
        if (filled_cap > input.cacheServerCapacity)
            return false;
    }
    return true;
}