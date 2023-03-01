//
// Created by risha on 14-02-2023.
//

#include "Greedy.h"

vector<bool> Greedy(const Graph &input) {
  vector<bool> output;
  output.resize(input.numberOfClients, false);
  using client_id = uint32_t;
  uint32_t numberOfClients = input.numberOfClients;

  vector<int> degrees(numberOfClients, 0);
  vector<bool> done(numberOfClients, false);
  set<pair<uint32_t, client_id>> minSet;
  for (client_id id = 0; id < numberOfClients; id++) {
    degrees[id] = input.G[id].size();
    minSet.insert({degrees[id], id});
  }
  while (!minSet.empty()) {
    auto it = minSet.begin();
    client_id minDegreeNode = it->second;
    output[minDegreeNode] = true;
    map<client_id, uint32_t> toDecrease;
    done[minDegreeNode] = true;

    for (auto neighbour : input.G[minDegreeNode]) {
      if (!done[neighbour]) {
        minSet.erase({degrees[neighbour], neighbour});
        done[neighbour] = true;
        for (auto nextNeighbours : input.G[neighbour]) {
          if (!done[nextNeighbours])
            toDecrease[nextNeighbours]++;
        }
      }
    }
    for (auto [client, decrement] : toDecrease) {
      minSet.erase({degrees[client], client});
      degrees[client] -= decrement;
      if (!done[client])
        minSet.insert({degrees[client], client});
    }
    minSet.erase(it);
  }

  return output;
}
