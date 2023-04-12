//
// Created by Asus-2021 on 4/12/2023.
//

#include "aco.h"
#include "../shared/utils.h"

pair<vector<int>,int> aco::findPath() {

    vector<int> minLatencypath;
    int saved = -1;
    bool vis[g.requests];
    int rem[g.server];
    rem[0] = LLONG_MAX;
    for (int j = 1; j < g.server; j++) {
        rem[j] = input.cacheServerCapacity;
    }

    for (int i = 0; i < numberOfAnts; i++) {

        vector<int> path;
        path.push_back(0);
        memset(vis, false, sizeof vis);
        int currentSaved = 0;
        int times = g.requests;
        while (times--) {

            vector<long double> prob;
            vector<int> whichOne;


            int whichServer = path.back();
            long double tot = 0;
            for (int t = 0; t < g.requests; t++) {
                if (!vis[t]) {
                    prob.push_back(g.pheromoneDown[whichServer][t]);
                    tot += prob.back();
                    whichOne.push_back(t);
                }
            }
            for (auto &c: prob) c /= tot;
            int whichRequest = whichOne[rand(prob)];

            path.push_back(whichRequest);

            prob.clear();
            whichOne.clear();
            vector<int> lat;
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
            int id = rand(prob);
            whichServer = whichOne[id];
            currentSaved += lat[id];
            path.push_back(whichServer);
        }

        if(currentSaved>saved){
            saved=currentSaved;
            minLatencypath=path;
        }
    }

    return {minLatencypath,saved};
}