//
// Created by Asus-2021 on 2/28/2023.
//

#include "aco.h"

#include <utility>

//aco::aco(const Graph& graph) : graph(graph), input() {
//    num_ants = 10;
//    min_pheromone = 0.5;
//    max_pheromone = 20;
//    alpha = 2;
//    max_cycles = 1000;
//    evaporation = 0.995;
//    initialCliqueCnt = 5;
//    pheromone.resize(graph.numberOfClients);
//}

aco::aco(const Input& _input) :input(_input),graph(_input,true),graphInv(_input) {
    num_ants = 10;
    min_pheromone = 0.5;
    max_pheromone = 20;
    alpha = 2;
    max_cycles = 1000;
    evaporation = 0.995;
    initialCliqueCnt = 100;
    pheromone.resize(graph.numberOfClients);
    initializePheromoneClassicalWay = true;
}

Output aco::run(int _max_cycles) {
    max_cycles = _max_cycles;
    if(initializePheromoneClassicalWay){
        aco::initialisePheromoneClassicWay();
    }else{
        aco::initialisePheromoneHeuristicWay();
    }
    set<uint32_t> finalClique;
    ofstream file;
    file.open("ip.txt");
    for (int j = 0; j < max_cycles; j++) {
        file<<j+1<<" ";
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
        file<<finalClique.size()<<endl;
    }
    file.close();

    for (auto &c: finalClique) {
        for (auto &d: input.featureLiked[c]) {
            output.features.insert(d);
        }
    }
    return output;
}