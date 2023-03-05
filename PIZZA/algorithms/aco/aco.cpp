//
// Created by Asus-2021 on 2/28/2023.
//

#include "aco.h"

#include <utility>

aco::aco(const Graph& graph) : graph(graph), input() {
    num_ants = 10;
    min_pheromone = 0.5;
    max_pheromone = 20;
    alpha = 2;
    max_cycles = 1000;
    evaporation = 0.995;
    initialCliqueCnt = 5;
    pheromone.resize(graph.numberOfClients);
}

aco::aco(const Input& _input) :input(_input),graph(_input,true) {
    num_ants = 10;
    min_pheromone = 0.5;
    max_pheromone = 20;
    alpha = 2;
    max_cycles = 1000;
    evaporation = 0.995;
    initialCliqueCnt = 50;
    cout<<graph.edges.size()<<endl;
    pheromone.resize(graph.numberOfClients);
}

Output aco::run(int _max_cycles) {
    max_cycles = _max_cycles;
    aco::initialisePheromoneClassicWay();
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