//
// Created by risha on 12-04-2023.
//

#include "Score.h"

long long Score::calculate(const Input &input, const Output &output) {
    long long val=0;
    long long totRequest=0;
    for(int req=0;req<input.requests;req++){
        auto video=(input.requestsDescription[req])[0];
        auto endPoint=(input.requestsDescription[req])[1];
        auto numRequest=(input.requestsDescription[req])[2];
        totRequest+=numRequest;

        int minLatency=input.latency[endPoint][0];// time from dataserver
        for(int cache=1;cache<=input.cacheServer;cache++){
            if(output.videosServed[cache][video] && input.latency[endPoint][cache]!=-1){
                minLatency=min(minLatency,input.latency[endPoint][cache]);
            }
        }
        val+=(numRequest*(input.latency[endPoint][0] - minLatency));
    }

    return (val*1000LL)/(totRequest);
}