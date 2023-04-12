#include "RandomInit.h"
#include <unordered_set>
#include <vector>

int get_random_client(unordered_set<int> &clients) {
  int idx = rng() % clients.size();
  auto it = clients.begin();
  advance(it, idx);
  return *it;
}

vector<bool> RandomInit(Graph &input) {
  unordered_set<int> clients;
  for (int id = 0; id < input.numberOfClients; id++) {
    clients.insert(id);
  }
  vector<bool> output(input.numberOfClients, false);
  while (clients.size() > 0) {
    int id = get_random_client(clients);
    clients.erase(id);
    for (int neighbour : input.G[id]) {
      clients.erase(neighbour);
    }
    output[id] = true;
  }
  return output;
}
