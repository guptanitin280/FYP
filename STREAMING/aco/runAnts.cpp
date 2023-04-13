//
// Created by Asus-2021 on 4/12/2023.
//

#include "aco.h"
#include "../shared/utils.h"




pair<vector<long long>,long long> aco::findPath() {

    vector<long long> minLatencypath;
    long long maxScore = -1;
    bool vis[g.requests];
    long long rem[g.server];


    for (long long i = 0; i < numberOfAnts; i++) {

        vector<long long> path;
        path.push_back(0);
        memset(vis, false, sizeof vis);

        rem[0] = LLONG_MAX;
        for (long long j = 1; j < g.server; j++) {
            rem[j] = input.cacheServerCapacity;
        }


        long long times = g.requests;
        while (times--) {

            vector<long double> prob;
            vector<long long> whichOne;


            long long whichServer = path.back();
            long double tot = 0;
            for (long long t = 0; t < g.requests; t++) {
                if (!vis[t]) {
                    prob.push_back(g.pheromoneDown[whichServer][t]);
                    tot += prob.back();
                    whichOne.push_back(t);
                }
            }
            for (auto &c: prob) c /= tot;
            long long whichRequest = whichOne[rand(prob)];
            vis[whichRequest]=true;

            path.push_back(whichRequest);

            prob.clear();
            whichOne.clear();
            vector<long long> lat;
            tot = 0;

            for (auto &c: g.edgesUp[whichRequest]) {
                if (rem[c.first] >= g.videoSize[whichRequest]) {
                    prob.push_back(c.second + g.pheromoneUp[whichRequest][c.first]);
                    tot += prob.back();
                    lat.push_back(c.second);
                    whichOne.push_back(c.first);
                }
            }

            for (auto &c: prob) c /= tot;
            long long id = rand(prob);

            whichServer = whichOne[id];
            rem[whichServer] -= g.videoSize[whichRequest];
            path.push_back(whichServer);
        }

        long long currentScore= calculateScore(path);
        if(currentScore>maxScore){
            maxScore=currentScore;
            minLatencypath=path;
        }
    }

    return {minLatencypath,maxScore};
}