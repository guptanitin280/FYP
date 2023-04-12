//
// Created by risha on 12-04-2023.
//

#include "Score.h"

int Score::calculate(const Input &input, const Output &output) {
    int val=0;
    for(int req=0;req<input.requests;req++){
        auto video=(input.requestsDescription[req])[0];
        auto endPoint=(input.requestsDescription[req])[1];
        auto numRequest=(input.requestsDescription[req])[2];

        int minLatency=input.latency[endPoint][0];// time from dataserver
        for(int cache=1;cache<=input.cacheServer;cache++){
            if(output.videosServed[cache][video]){
                minLatency=min(minLatency,input.latency[endPoint][cache+1]);
            }
        }
        val+=(numRequest*(input.latency[endPoint][0] - minLatency));
    }
    return val;
}