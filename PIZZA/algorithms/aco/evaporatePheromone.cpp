//
// Created by Asus-2021 on 3/2/2023.
//
#include "aco.h"

void aco::evaporatePheromone() {
    for (int i = 0; i < graph.numberOfClients; i++) {
        for (auto &c: pheromone[i]) {
            c.second = max(c.second * evaporation, min_pheromone);
        }
    }
}