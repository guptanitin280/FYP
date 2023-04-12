//
// Created by Asus-2021 on 4/12/2023.
//

#include "aco.h"

#include "aco.h"

void aco::evaporatePheromone() {
    for (int i = 0; i < g.requests; i++) {
        for (int j = 0; j < g.server; j++) {
            g.pheromoneUp[i][j] = max(minPheromone, g.pheromoneUp[i][j] * evaporation);
            g.pheromoneDown[j][i] = max(minPheromone, g.pheromoneDown[i][j] * evaporation);
        }
    }
}