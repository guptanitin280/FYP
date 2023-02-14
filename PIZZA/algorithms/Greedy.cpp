//
// Created by risha on 14-02-2023.
//

#include "Greedy.h"

Greedy::Greedy(Input _input) : input(_input) {

}

Output Greedy::solve() {
    using client_id = uint32_t;
    uint32_t numberOfClients=input.numberOfClients;
    Graph clientGraph(input);
    vector<int> degrees(numberOfClients,0);
    vector<bool> done(numberOfClients, false);
    set<pair<uint32_t ,client_id >> minSet;
    for(client_id id=0;id<numberOfClients;id++){
        degrees[id]=clientGraph.G[id].size();
        minSet.insert({degrees[id],id});
    }
    while(! minSet.empty()){
        auto it=minSet.begin();
        client_id minDegreeNode=it->second;
        map<client_id,uint32_t> toDecrease;
        for(auto feature:input.featureLiked[minDegreeNode])output.features.insert(feature);
        done[minDegreeNode]=true;
        for(auto neighbour:clientGraph.G[minDegreeNode]){
            if(!done[neighbour]){
                minSet.erase({degrees[neighbour],neighbour});
                done[neighbour]=true;
                for(auto nextNeighbours:clientGraph.G[neighbour]){
                    if(!done[nextNeighbours])toDecrease[nextNeighbours]++;
                }
            }
        }
        for(auto [client,decrement]:toDecrease){
            minSet.erase({degrees[client],client});
            degrees[client]-=decrement;
            minSet.insert({degrees[client],client});
        }
        minSet.erase(it);
    }

    return output;
}
