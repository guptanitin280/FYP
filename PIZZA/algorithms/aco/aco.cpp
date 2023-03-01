//
// Created by Asus-2021 on 2/28/2023.
//

#include "aco.h"

#include <utility>
#include "../../shared/utils.h"

aco::aco(const Graph& graph) : graph(graph), input(){
    num_ants = 10;
    min_pheromone = 0.5;
    max_pheromone = 10;
    alpha = 3;
    max_cycles = 1000;
    evaporation = 0.9;
    pheromone.resize(graph.numberOfClients);
}

aco::aco(const Input& _input) :input(_input),graph(_input,true) {
    num_ants = 10;
    min_pheromone = 0.5;
    max_pheromone = 10;
    alpha = 3;
    max_cycles = 1000;
    evaporation = 0.9;
    pheromone.resize(graph.numberOfClients);
}

set<uint32_t> aco::findMaxClique() {
    set<uint32_t>max_clique;
    for (int i = 0; i < num_ants; i++) {
        cout<<"ant "<<i<<endl;
        set<uint32_t> currentClique, potentialClients;
        uint32_t startingClient = rand((uint32_t) 0, (uint32_t) graph.numberOfClients - 1);
        currentClique.insert(startingClient);
        for (auto &c: graph.G[startingClient]) potentialClients.insert(c);
        while (!potentialClients.empty()) {
            vector<long double> prob;
            long double totProb = 0;
            for (auto &d: potentialClients) {
                long double tot = 0;
                for (auto &c: currentClique) {
                    tot += pow(pheromone[c][d], alpha);
                }
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
        }
        if (max_clique.size() < currentClique.size()) {
            max_clique = currentClique;
        }
    }
    return max_clique;
}

void aco::evaporatePheromone() {
    for (int i = 0; i < graph.numberOfClients; i++) {
        for (auto &c: pheromone[i]) {
            c.second = max(c.second * evaporation, min_pheromone);
        }
    }
}

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

Output aco::run(int _max_cycles) {
    max_cycles = _max_cycles;
    //initialize pheromone
    for (int i = 0; i < graph.numberOfClients; i++) {
        for (auto &d: graph.G[i]) {
            pheromone[i][d] = max_pheromone;
        }
    }

    set<uint32_t> finalClique;

    for (int j = 0; j < max_cycles; j++) {
        cout<<"cycle "<<j<<endl;
        //make a clique for each ants
        auto max_clique = findMaxClique();
        evaporatePheromone();
        long double u = finalClique.size();
        long double v = max_clique.size();
        if (finalClique.size() < max_clique.size()) {
            finalClique = max_clique;
        }
        replenishPheromone(u, v, finalClique);
        cout<<finalClique.size()<<endl;
    }

    for (auto &c: finalClique) {
        for (auto &d: input.featureLiked[c]) {
            output.features.insert(d);
        }
    }
    return output;
}