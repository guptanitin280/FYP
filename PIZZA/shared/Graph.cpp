//
// Created by risha on 14-02-2023.
//

#include "Graph.h"
#include "Input.h"

Graph::Graph(Input _input,bool invert): input(_input) {
    numberOfClients = _input.numberOfClients;
    G.resize(numberOfClients);

    for (int i = 0; i < numberOfClients; i++) {
        for (int j = i + 1; j < numberOfClients; j++) {
            if (areCompatible(i, j) == invert)
                addEdge(i, j);
        }
    }

}

void Graph::addEdge(client_id client1, client_id client2) {
    G[client1].push_back(client2);
    G[client2].push_back(client1);
}

bool Graph::areCompatible(client_id client1, client_id client2) {
    return (intersection(input.featureLiked[client1],input.featureDisLiked[client2]).empty() &&
            intersection(input.featureLiked[client2],input.featureDisLiked[client1]).empty()
    )  ;
}