//
// Created by Asus-2021 on 3/2/2023.
//

#include "aco.h"
#include "../../heuristics/RandomGreedy.h"

void aco::intialisePheromone() {
    //initialize pheromone
    for (int i = 0; i < graph.numberOfClients; i++) {
        for (auto &d: graph.G[i]) {
            pheromone[i][d] = (min_pheromone+max_pheromone)/2;
        }
    }

    for(int j=0;j<initialCliqueCnt;j++) {
        vector<bool> clique = RandomGreedy(graph);
        vector<int>nodes;
        for(int i=0;i<graph.numberOfClients;i++){
            if(clique[i]) nodes.push_back(i);
        }
        long double temp=
        for(auto &c:nodes){
            for(auto d:nodes){
                if(c!=d){
                    pheromone[c][d]=min(max_pheromone,nodes.size())
                }
            }
        }
    }

}