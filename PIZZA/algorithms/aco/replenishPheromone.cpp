//
// Created by Asus-2021 on 3/2/2023.
//

#include "aco.h"
void aco::replenishPheromone(long double u,long double v,set<uint32_t>&finalClique) {
    for (auto &c: finalClique) {
        for (auto &d: finalClique) {
            if (c != d) {
                pheromone[c][d] += 1 / (1 + u + v);
                pheromone[c][d] = min(max_pheromone, pheromone[c][d]);
            }
        }
    }
}