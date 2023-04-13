//
// Created by Asus-2021 on 4/12/2023.
//

#include "Graph.h"
Graph::Graph(Input &input) {
    requests = input.requests;
    server = input.cacheServer + 1;
    pheromoneUp.resize(requests, vector<long double>(server, 0));
    pheromoneDown.resize(server, vector<long double>(requests, 0));

    edgesUp.resize(requests);
    videoSize.resize(requests);
    for (int i = 0; i < requests; i++) {
        int video = input.requestsDescription[i][0];
        int endPoint = input.requestsDescription[i][1];
        int cnt = input.requestsDescription[i][2];
        videoSize[i] = input.videoSizes[video];
        for (int j = 0; j < server; j++) {
            if (input.latency[endPoint][j] != -1) {
                edgesUp[i].push_back({j, (input.latency[endPoint][0] - input.latency[endPoint][j]) * cnt});
            }
        }
    }
}