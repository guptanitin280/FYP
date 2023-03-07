//
// Created by Asus-2021 on 2/28/2023.
//

#include "aco.h"

#include <utility>



ofstream aco::ff;

aco::aco(const Input& _input,const initializingAlgo &_algo=initializingAlgo::CLASSICAL_WAY) :input(_input),graph(_input,true),graphInv(_input) {
    num_ants = 30;
    min_pheromone = 0.01;
    max_pheromone = 4;
    alpha = 2;
    max_cycles = 1000;
    evaporation = 0.995;
    initialCliqueCnt = 5000;
    algo=_algo;
    pheromone.resize(graph.numberOfClients);
}

Output aco::run(int _max_cycles) {
    max_cycles = _max_cycles;
    if(algo==initializingAlgo::CLASSICAL_WAY){
        aco::initialisePheromoneClassicWay();
    }else {
        aco::initialisePheromoneHeuristicWay();
    }
    set<uint32_t> finalClique;
    for (int j = 0; j < max_cycles; j++) {
        ff<<j+1<<" ";
        cout<<j+1<<" ";
        //make a clique for each ants
        auto max_clique = findMaxClique();
        evaporatePheromone();
        long double u = finalClique.size();
        long double v = max_clique.size();
        if (finalClique.size() < max_clique.size()) {
            finalClique = max_clique;
        }
        replenishPheromone(u, v, finalClique);
        ff<<finalClique.size()<<endl;
    }

    for (auto &c: finalClique) {
        for (auto &d: input.featureLiked[c]) {
            output.features.insert(d);
        }
    }
    return output;
}