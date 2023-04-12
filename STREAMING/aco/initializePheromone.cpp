//
// Created by Asus-2021 on 4/12/2023.
//

#include "aco.h"

void aco::initialisePheromone() {
    for (int i = 0; i < g.server; i++) {
        for (int j = 0; j < g.requests; j++) {
            g.pheromoneDown[i][j] = minPheromone;
            g.pheromoneUp[j][i] = maxPheromone;
        }
    }
}