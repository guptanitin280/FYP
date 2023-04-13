//
// Created by Asus-2021 on 4/12/2023.
//

#ifndef STREAMING_ACO_H
#define STREAMING_ACO_H
#include "../shared/Input.h"
#include "../shared/Output.h"
#include "Graph.h"
enum initializingAlgo { CLASSICAL_WAY, RANDOM_GREEDY_WAY};

class aco {
public:
    Input input;
    Output output;
    long long numberOfAnts = 20;
    long long max_cycle = 100;
    long double evaporation = 0.995;
    long double minPheromone = 0.01;
    long double maxPheromone = 4;
    Graph g;
    static ofstream ff;
    initializingAlgo algo;
    long long initialSol=100;

    aco(Input _input,initializingAlgo _algo);

    pair<vector<long long>,long long> findPath();

    Output run(long long _max_cycles);

    void evaporatePheromone();

    void replenishPheromone(long double u, long double v, vector<long long> &whichOne);

    void initialisePheromone();

    bool isValid();

    long long calculateScore(vector<long long>&path);
};


#endif //STREAMING_ACO_H
