//
// Created by Asus-2021 on 4/12/2023.
//

#ifndef STREAMING_GRAPH_H
#define STREAMING_GRAPH_H
#include<bits/stdc++.h>
#include "../shared/Input.h"
using namespace std;

class Graph {
public:

    int requests;
    int server;
    vector<vector<long double>>pheromoneUp;
    vector<vector<long double>>pheromoneDown;
    vector<vector<pair<int,int>>>edgesUp;
    vector<int>videoSize;

    Graph(Input &input);
};


#endif //STREAMING_GRAPH_H
