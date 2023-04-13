//
// Created by Asus-2021 on 4/12/2023.
//

#include "aco.h"


void aco::evaporatePheromone() {
    for (long long i = 0; i < g.requests; i++) {
        for (long long j = 0; j < g.server; j++) {
            g.pheromoneUp[i][j] = max(minPheromone, g.pheromoneUp[i][j] * evaporation);
            g.pheromoneDown[j][i] = max(minPheromone, g.pheromoneDown[j][i] * evaporation);
        }
    }
}