//
// Created by risha on 14-02-2023.
//

#ifndef FYP_GRAPH_H
#define FYP_GRAPH_H

#include<bits/stdc++.h>
#include "Input.h"
#include "utils.h"

using namespace std;

class Graph {
public:
    using client_id = uint32_t;
    uint32_t numberOfClients;
    Input input;
    vector<vector<client_id>>G;
    vector<pair<client_id ,client_id >> edges;

    explicit Graph(Input _input,bool invert=false);

    void addEdge(client_id client1,client_id client2);

    bool areCompatible(client_id client1,client_id client2);
};

#endif //FYP_GRAPH_H
