//
// Created by risha on 14-02-2023.
//

#include "Graph.h"
#include "Input.h"

Graph::Graph() {

}

Graph::Graph(Input _input,bool invert): input(_input) {
    numberOfClients = _input.numberOfClients;
    G.resize(numberOfClients);

    fillAdjacencyList();

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

void Graph::fillAdjacencyList(){
    unordered_map<string,vector<client_id>>likes;
    unordered_map<string,vector<client_id>>dislikes;

    for (int i = 0; i < numberOfClients; i++){
        for(auto &x:input.featureLiked[i])likes[x].push_back(i);
        for(auto &x:input.featureDisLiked[i])dislikes[x].push_back(i);
    }

    for(auto &[feature,_]:likes){
        for(auto x:likes[feature]){
            for(auto y:dislikes[feature]){
                addEdge(x,y);
            }
        }
    }

}