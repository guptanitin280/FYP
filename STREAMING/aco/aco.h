//
// Created by Asus-2021 on 4/12/2023.
//

#ifndef STREAMING_ACO_H
#define STREAMING_ACO_H
#include "../shared/Input.h"
#include "../shared/Output.h"
#include "Graph.h"

class aco {
public:
    Input input;
    Output output;
    int numberOfAnts = 10;
    int max_cycle = 100;
    long double evaporation = 0.995;
    long double minPheromone = 0.01;
    long double maxPheromone = 4;
    Graph g;

    aco(Input _input);

    pair<vector<int>,int> findPath();

    Output run(int _max_cycles);

    void evaporatePheromone();

    void replenishPheromone(long double u, long double v, vector<int> &whichOne);

    void initialisePheromone();

};


#endif //STREAMING_ACO_H
