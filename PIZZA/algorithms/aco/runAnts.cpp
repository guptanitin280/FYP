//
// Created by Asus-2021 on 3/2/2023.
//
#include "aco.h"
#include "../../shared/utils.h"

set<uint32_t> aco::findMaxClique() {
    set<uint32_t>max_clique;
    for (int i = 0; i < num_ants; i++) {
        set<uint32_t> currentClique, potentialClients;
        uint32_t startingClient = rand((uint32_t) 0, (uint32_t) graph.numberOfClients - 1);
        currentClique.insert(startingClient);
        for (auto &c: graph.G[startingClient]) potentialClients.insert(c);
        vector<long double>pheromoneFactor;
        pheromoneFactor.resize(graph.numberOfClients,0);
        for(auto &c:potentialClients){
            for(auto &d:currentClique){
                pheromoneFactor[c]+=pow(pheromone[c][d],alpha);
            }
        }
        while (!potentialClients.empty()) {
            vector<long double> prob;
            long double totProb = 0;
            for (auto &d: potentialClients) {
                long double tot = pheromoneFactor[d];
                totProb += tot;
                prob.push_back(tot);
            }
            for (auto &c: prob) c /= totProb;
            uint32_t whichOne = rand(prob);
            auto it = potentialClients.begin();
            while (whichOne > 0) {
                it = next(it);
                whichOne--;
            }
            uint32_t vert = *it;
            currentClique.insert(*it);
            potentialClients.erase(*it);

            vector<uint32_t> toRem;
            for (auto &e: potentialClients) {
                if (!pheromone[vert].count(e)) {
                    toRem.push_back(e);
                }
            }
            for (auto &c: toRem) potentialClients.erase(c);
            for(auto &c:potentialClients){
                pheromoneFactor[c]+=pow(pheromone[c][vert],alpha);
            }
        }
        if (max_clique.size() < currentClique.size()) {
            max_clique = currentClique;
        }
    }
    return max_clique;
}