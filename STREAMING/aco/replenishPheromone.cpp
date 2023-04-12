//
// Created by Asus-2021 on 4/12/2023.
//

#include "aco.h"

void aco::replenishPheromone(long double u,long double v,vector<int>&path) {

    for (int i = 2; i < path.size(); i += 2) {
        g.pheromoneUp[path[i - 1]][path[i]] += 1 / (1 + u + v);
        g.pheromoneUp[path[i - 1]][path[i]] = min(maxPheromone, g.pheromoneUp[path[i - 1]][path[i]]);
    }

    for (int i = 1; i < path.size(); i += 2) {
        g.pheromoneDown[path[i - 1]][path[i]] += (1 / (1 + u + v));
        g.pheromoneDown[path[i - 1]][path[i]] = min(maxPheromone, g.pheromoneDown[path[i - 1]][path[i]]);
    }

}