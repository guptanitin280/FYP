//
// Created by Asus-2021 on 3/2/2023.
//

#include "aco.h"
#include "../../heuristics/RandomGreedy.h"
#include "../../heuristics/RandomInit.h"

void aco::initialisePheromoneClassicWay() {
    //initialize pheromone classic way
    for (int i = 0; i < graph.numberOfClients; i++) {
        for (auto &d: graph.G[i]) {
            pheromone[i][d] = max_pheromone;
        }
    }
}

void aco::initialisePheromoneHeuristicWay() {
    //initialize pheromone using heuristic way
    for (int i = 0; i < graph.numberOfClients; i++) {
        for (auto &d: graph.G[i]) {
            pheromone[i][d] = min_pheromone;
        }
    }
    for (int j = 0; j < initialCliqueCnt; j++) {
        vector<bool> clique = RandomInit(graphInv);
        vector<int> nodes;
        for (int i = 0; i < graph.numberOfClients; i++) {
            if (clique[i]) nodes.push_back(i);
        }
        long double temp = (nodes.size()) * (nodes.size());
        temp /= graph.edges.size();
        for (auto &c: nodes) {
            for (auto d: nodes) {
                if (c != d) {
                    pheromone[c][d] = min(max_pheromone, temp + pheromone[c][d]);
                }
            }
        }
    }
}