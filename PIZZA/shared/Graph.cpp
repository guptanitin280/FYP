//
// Created by risha on 14-02-2023.
//

#include "Graph.h"
#include "Input.h"

Graph::Graph() {

}

Graph::Graph(const Input& _input,bool invert): input(_input) {
    numberOfClients = _input.numberOfClients;
    G.resize(numberOfClients);

    fillAdjacencyList(invert);

}

void Graph::addEdge(client_id client1, client_id client2) {
    G[client1].push_back(client2);
    G[client2].push_back(client1);
    edges.emplace_back(client1,client2);
    edges.emplace_back(client2,client1);
}

bool Graph::areCompatible(client_id client1, client_id client2) {
    return (intersection(input.featureLiked[client1],input.featureDisLiked[client2]).empty() &&
            intersection(input.featureLiked[client2],input.featureDisLiked[client1]).empty()
    )  ;
}

void Graph::fillAdjacencyList(bool invert) {
    vector<vector<bool>> g;
    g.resize(numberOfClients, vector<bool>(numberOfClients, false));
    unordered_map<string, vector<client_id>> likes;
    unordered_map<string, vector<client_id>> dislikes;

    for (int i = 0; i < numberOfClients; i++) {
        for (auto &x: input.featureLiked[i])likes[x].push_back(i);
        for (auto &x: input.featureDisLiked[i])dislikes[x].push_back(i);
    }

    for (auto &[feature, _]: likes) {
        for (auto x: likes[feature]) {
            for (auto y: dislikes[feature]) {
                g[x][y] = true;
                g[y][x]=true;
            }
        }
    }

//    for (auto &[feature, _]: likes) {
//        for (auto x: likes[feature]) {
//            for (auto y: dislikes[feature]) {
//                g[x][y] = g[y][x] = true;
//            }
//        }
//    }
//
    for (int i = 0; i < numberOfClients; i++) {
        for (int j = i + 1; j < numberOfClients; j++) {
            if (g[i][j] != invert) addEdge(i, j);
        }
    }

}