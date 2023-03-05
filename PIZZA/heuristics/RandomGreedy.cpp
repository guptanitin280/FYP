//
// Created by risha on 01-03-2023.
//

#include "RandomGreedy.h"

//take the element with the minimum degree
//but among the multiple node take one randomly
//return different clique every time

vector<bool> RandomGreedy(Graph& input) {
    vector<bool> output;
    output.resize(input.numberOfClients, false);
    const int LIM = 1e9;
    using client_id = int;
    int numberOfClients = input.numberOfClients;

    vector<int> degrees(numberOfClients, 0);
    vector<bool> done(numberOfClients, false);
    set<vector<int>> minSet;
    map<int, int> randomValueAssigned;
    for (client_id id = 0; id < numberOfClients; id++) {
        degrees[id] = input.G[id].size();
        randomValueAssigned[id] = (int) rand(1, LIM);
        minSet.insert({degrees[id], randomValueAssigned[id], id});
    }
    while (!minSet.empty()) {
        auto it = minSet.begin();
        client_id minDegreeNode = (*it)[2];
        output[minDegreeNode] = true;
        map<client_id, uint32_t> toDecrease;
        done[minDegreeNode] = true;

        for (auto neighbour: input.G[minDegreeNode]) {
            if (!done[neighbour]) {
                minSet.erase({degrees[neighbour], randomValueAssigned[neighbour], (int) neighbour});
                done[neighbour] = true;
                for (auto nextNeighbours: input.G[neighbour]) {
                    if (!done[nextNeighbours])toDecrease[nextNeighbours]++;
                }
            }
        }
        for (auto[client, decrement]: toDecrease) {
            minSet.erase({degrees[client],randomValueAssigned[client],client});
            degrees[client] -= decrement;
            if (!done[client]) {
                randomValueAssigned[client] = (int) rand(1, LIM);
                minSet.insert({degrees[client], randomValueAssigned[client], client});
            }
        }
        minSet.erase(it);

    }
//    for(auto x:output){
//        cout<<x<<" ";
//    }
//    cout<<endl;
    return output;

}
