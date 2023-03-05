//
// Created by Asus-2021 on 2/28/2023.
//

#ifndef FYP_ACO_H
#define FYP_ACO_H

#include <cstdint>
#include<bitset>
#include "../../shared/Graph.h"
#include "../../shared/Output.h"

class aco{
    uint32_t num_ants;
    long double min_pheromone;
    long double max_pheromone;
    long double alpha;
    long double evaporation;
    long double initialCliqueCnt;
    uint32_t max_cycles;
    Graph graph;
    Input input;
    vector<unordered_map<uint32_t ,long double>>pheromone;
    Output output;

public:
    aco(const Input& _input);
    aco(const Graph& graph);
    set<uint32_t> findMaxClique();
    Output run(int _max_cycles);
    void evaporatePheromone();
    void replenishPheromone(long double u,long double v,set<uint32_t>&finalClique);
    void initialisePheromoneClassicWay();
    void initialisePheromoneHeuristicWay();
};

#endif //FYP_ACO_H
