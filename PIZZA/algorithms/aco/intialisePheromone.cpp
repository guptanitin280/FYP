//
// Created by Asus-2021 on 3/2/2023.
//

#include "aco.h"
#include "../../heuristics/RandomGreedy.h"
#include "../../heuristics/RandomInit.h"
#include "../../shared/utils.h"


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
            pheromone[i][d] = max_pheromone*0.9;
        }
    }

    set<pair<vector<bool>,long double>> s;
    long double cnt=0;
    for (int j = 0; j < initialCliqueCnt; j++) {
        vector<bool> clique;

        int x=rand(0,5);
        if (x<=4) {
            clique = RandomInit(graphInv);
        } else {
            clique = RandomGreedy(graphInv);
        }
        int temp = 0;
        for (int i = 0; i < graph.numberOfClients; i++) {
            if (clique[j]) temp++;
        }
        cnt+=temp;
        s.insert({clique, temp});
    }

    for (auto clique: s) {
        clique.second=clique.second/cnt;
        vector<int> nodes;
        for (int i = 0; i < graph.numberOfClients; i++) {
            if (clique.first[i]) nodes.push_back(i);
        }
//        long double temp = (nodes.size()) * (nodes.size());
//        temp /= graph.edges.size();
        for (auto &c: nodes) {
            for (auto d: nodes) {
                if (c != d && pheromone[c].count(d)) {
                    pheromone[c][d] += clique.second;
                    pheromone[c][d]=min(max_pheromone,pheromone[c][d]);
                }
            }
        }
    }
}