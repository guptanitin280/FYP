#include "SAState.h"
#include "../shared/Output.h"
#include "../shared/Score.h"
#include "../shared/utils.h"
SAState::SAState(const Graph &input, const vector<bool> &clientSatisfied,
                 bool enableHeuristic)
    : graph(input), clientsSatistied(clientSatisfied),
      enableHeuristic(enableHeuristic) {}

SAState::SAState(const SAState &otherState)
    : graph(otherState.graph), clientsSatistied(otherState.clientsSatistied),
      enableHeuristic(otherState.enableHeuristic) {}

bool SAState::isValid() const {
  bool valid = true;
  for (auto e : this->graph.edges) {
    if (this->clientsSatistied[e.first] && this->clientsSatistied[e.second]) {
      valid = false;
    }
  }
  return valid;
}

int SAState::score() const {
  int numClients = 0;
  for (auto isClientSatisfied : clientsSatistied) {
    numClients += isClientSatisfied;
  }
  return numClients;
}

int SAState::getNumClients() const {
  int numClients = 0;
  for (auto isClientSatisfied : clientsSatistied) {
    numClients += isClientSatisfied;
  }
  return numClients;
}
int SAState::getInvalidClientsPenalty() const {
  int invalidEdges = 0;
  int n = this->graph.numberOfClients;
  for (int node = 0; node < n; node++) {
    for (int neighbour : graph.G[node]) {
      if (this->clientsSatistied[node] && this->clientsSatistied[neighbour])
        invalidEdges++;
    }
  }
  return invalidEdges / 2;
}
void SAState::operator=(const SAState &otherState) {
  this->clientsSatistied = otherState.clientsSatistied;
}

int get_random_client1(unordered_set<int> &clients) {
  int idx = rng() % clients.size();
  auto it = clients.begin();
  advance(it, idx);
  return *it;
}

SAState nextStateWithRandomHeuristic(const SAState &cur_sol) {
  SAState output(cur_sol);
  const Graph &graph = cur_sol.graph;
  vector<int> rand_vec;
  for (int i = 0; i < graph.numberOfClients; i++) {
    rand_vec.push_back(i);
  }
  shuffle(rand_vec.begin(), rand_vec.end(), rng);
  for (int i = 0; i < rand_vec.size() / 2; i++) {
    output.clientsSatistied[rand_vec[i]] = 0;
  }
  unordered_set<int> clients;
  for (int id = 0; id < graph.numberOfClients; id++) {
    clients.insert(id);
  }
  for (int id = 0; id < graph.numberOfClients; id++) {
    if (output.clientsSatistied[id]) {
      clients.erase(id);
      for (int neighbour : graph.G[id]) {
        clients.erase(neighbour);
      }
    }
  }
  while (clients.size() > 0) {
    int id = get_random_client1(clients);
    clients.erase(id);
    for (int neighbour : graph.G[id]) {
      clients.erase(neighbour);
    }
    output.clientsSatistied[id] = true;
  }
  return output;
}

SAState nextStateWithGreedyHeuristic(const SAState &cur_sol) {
  const Graph &graph = cur_sol.graph;
  SAState output(cur_sol);
  vector<int> rand_vec;
  for (int i = 0; i < graph.numberOfClients; i++) {
    rand_vec.push_back(i);
  }
  shuffle(rand_vec.begin(), rand_vec.end(), rng);
  for (int i = 0; i < rand_vec.size() / 2; i++) {
    output.clientsSatistied[rand_vec[i]] = 0;
  }
  const int LIM = 1e9;
  using client_id = int;
  int numberOfClients = graph.numberOfClients;

  vector<int> degrees(numberOfClients, 0);
  vector<bool> done(numberOfClients, false);
  set<vector<int>> minSet;
  map<int, int> randomValueAssigned;
  for (client_id id = 0; id < numberOfClients; id++) {
    degrees[id] = graph.G[id].size();
    randomValueAssigned[id] = (int)rand(1, LIM);
    minSet.insert({degrees[id], randomValueAssigned[id], id});
  }
  for (client_id id = 0; id < numberOfClients; id++) {
    if (output.clientsSatistied[id]) {
      done[id] = 1;
      minSet.erase({degrees[id], randomValueAssigned[id], (int)id});
      for (auto neighbour : graph.G[id]) {
        done[neighbour] = true;
        degrees[neighbour] -= 1;
        minSet.erase({degrees[neighbour], randomValueAssigned[neighbour],
                      (int)neighbour});
      }
    }
  }
  while (!minSet.empty()) {
    auto it = minSet.begin();
    client_id minDegreeNode = (*it)[2];
    output.clientsSatistied[minDegreeNode] = true;
    map<client_id, uint32_t> toDecrease;
    done[minDegreeNode] = true;

    for (auto neighbour : graph.G[minDegreeNode]) {
      if (!done[neighbour]) {
        minSet.erase({degrees[neighbour], randomValueAssigned[neighbour],
                      (int)neighbour});
        done[neighbour] = true;
        for (auto nextNeighbours : graph.G[neighbour]) {
          if (!done[nextNeighbours])
            toDecrease[nextNeighbours]++;
        }
      }
    }
    for (auto [client, decrement] : toDecrease) {
      minSet.erase({degrees[client], randomValueAssigned[client], client});
      degrees[client] -= decrement;
      if (!done[client]) {
        randomValueAssigned[client] = (int)rand(1, LIM);
        minSet.insert({degrees[client], randomValueAssigned[client], client});
      }
    }
    minSet.erase(it);
  }
  return output;
}
void swap_some_feature(set<string> &included, set<string> &others) {
  auto p = get_probability();
  if (others.size() == 0 || (p < 0.5 && included.size() != 0)) {
    int s = rng() % included.size();
    auto sit = included.begin();
    advance(sit, s);
    others.insert(*sit);
    included.erase(sit);
    return;
  }

  int t = rng() % others.size();
  auto tit = others.begin();
  advance(tit, t);
  included.insert(*tit);
  others.erase(tit);
  return;
}

SAState random_feature_swap(const SAState &sol) {
  const Graph &g = sol.graph;
  set<string> all_features;
  using client_id = int;

  for (int i = 0; i < g.numberOfClients; i++) {
    for (auto feature : g.input.featureLiked[i]) {
      all_features.insert(feature);
    }
    for (auto feature : g.input.featureDisLiked[i]) {
      all_features.insert(feature);
    }
  }
  set<string> includedFeatures = all_features;
  set<string> otherFeatures;
  for (int i = 0; i < g.numberOfClients; i++) {
    if (sol.clientsSatistied[i]) {
      for (auto feature : g.input.featureDisLiked[i]) {
        includedFeatures.erase(feature);
        otherFeatures.insert(feature);
      }
    }
  }
  vector<bool> out(g.numberOfClients, false);
  swap_some_feature(includedFeatures, otherFeatures);
  for (client_id id = 0; id < g.numberOfClients; id++) {
    bool valid = true;
    for (auto feature : g.input.featureLiked[id]) {
      if (includedFeatures.count(feature) == 0) {
        valid = false;
        break;
      }
    }
    if (!valid)
      continue;
    for (auto feature : g.input.featureDisLiked[id]) {
      if (includedFeatures.count(feature) > 0) {
        valid = false;
        break;
      }
    }
    if (valid) {
      out[id] = true;
    }
  }
  SAState state(sol);
  state.clientsSatistied = out;
  return state;
}

SAState nextStateWithClientSwap(const SAState &otherState) {
  SAState state(otherState);
  int v = rng() % state.clientsSatistied.size();
  state.clientsSatistied[v] = !state.clientsSatistied[v];
  return state;
}

// Other heuristics :
//  1. Next state with greedy heuristics
//  2. Next state with one of random feature swap
SAState SAState::getNeighbouringState() const {
  double prob = get_probability();
  if (this->enableHeuristic) {
    if (get_probability() < 0.33)
      return nextStateWithRandomHeuristic(*this);
  }
  return nextStateWithClientSwap(*this);
}
