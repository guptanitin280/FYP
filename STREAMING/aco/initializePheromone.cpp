//
// Created by Asus-2021 on 4/12/2023.
//

#include "aco.h"
#include "../heuristics/RandomGreedy.h"
#include "../shared/Score.h"

void aco::initialisePheromone() {
    if (algo == initializingAlgo::CLASSICAL_WAY) {
        for (int i = 0; i < g.server; i++) {
            for (int j = 0; j < g.requests; j++) {
                g.pheromoneDown[i][j] = minPheromone;
                g.pheromoneUp[j][i] = minPheromone;
            }
        }
    } else {
        for (int i = 0; i < g.server; i++) {
            for (int j = 0; j < g.requests; j++) {
                g.pheromoneDown[i][j] = maxPheromone * 0.9;
                g.pheromoneUp[j][i] = maxPheromone * 0.9;
            }
        }

        vector<pair<long double, vector<vector<bool>>>> values;
        long double tot = 0;
        for (int j = 0; j < initialSol; j++) {
            auto sol = RandomGreedy(input);
            output.videosServed = sol;
            output.numServers = input.cacheServer;
            output.numVideos = input.videos;
            values.emplace_back(Score::calculate(input, output), sol);
            tot += values.back().first;
        }

        sort(values.begin(), values.end());
        for (auto &c: values) {
            c.first /= tot;
        }
        for (auto &[x, sol]: values) {
            for (int k = 0; k < input.requests; k++) {
                int idx = 0;
                int endPoint = input.requestsDescription[k][1];

                for (int i = 1; i < g.server; i++) {
                    if (sol[i][input.requestsDescription[k][0]] &&
                        input.latency[endPoint][i] != -1 && input.latency[endPoint][i] < input.latency[endPoint][idx]) {
//                        g.pheromoneUp[k][i] = maxPheromone;
//                        g.pheromoneUp[k][i] = min(g.pheromoneUp[k][i], maxPheromone);

                        idx = i;
                    }
                }

                g.pheromoneUp[k][idx] += x;
                g.pheromoneUp[k][idx] = min(g.pheromoneUp[k][idx], maxPheromone);

            }
        }
    }
}