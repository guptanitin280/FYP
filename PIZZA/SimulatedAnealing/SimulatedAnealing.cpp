#include "SimulatedAnealing.h"
#include "../../shared/utils.h"
#include "SA_HyperParameters.h"
#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

SimulatedAnealing::SimulatedAnealing(Graph &_g, init_solver_ptr init_solver,
                                     SA_HyperParams &params)
    : g(_g), acceptable(params, g), init_solver(init_solver) {
  init_temp = params.init_temp;
  end_temp = params.end_temp;
  cool_down_rate = params.cool_down_rate;
  num_iter = params.num_iter;
};

double SimulatedAnealing::update_temp(double cur_temp) {
  return cool_down_rate * cur_temp;
}
int get_random_client1(unordered_set<int> &clients) {
  int idx = rng() % clients.size();
  auto it = clients.begin();
  advance(it, idx);
  return *it;
}
vector<bool> RandomGreedy(const Graph &graph, const vector<bool> &cur_sol) {
  vector<bool> output = cur_sol;
  vector<int> rand_vec;
  for (int i = 0; i < graph.numberOfClients; i++) {
    rand_vec.push_back(i);
  }
  shuffle(rand_vec.begin(), rand_vec.end(), rng);
  for (int i = 0; i < rand_vec.size() / 2; i++) {
    output[rand_vec[i]] = 0;
  }
  unordered_set<int> clients;
  for (int id = 0; id < graph.numberOfClients; id++) {
    clients.insert(id);
  }
  for (int id = 0; id < graph.numberOfClients; id++) {
    if (output[id]) {
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
    output[id] = true;
  }
  return output;
}

vector<bool> RandomGreedy1(const Graph &graph, const vector<bool> &cur_sol) {

  vector<bool> output = cur_sol;
  vector<int> rand_vec;
  for (int i = 0; i < graph.numberOfClients; i++) {
    rand_vec.push_back(i);
  }
  shuffle(rand_vec.begin(), rand_vec.end(), rng);
  for (int i = 0; i < rand_vec.size() / 2; i++) {
    output[rand_vec[i]] = 0;
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
    if (output[id]) {
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
    output[minDegreeNode] = true;
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
  //    for(auto x:output){
  //        cout<<x<<" ";
  //    }
  //    cout<<endl;
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
  // if (included.size() == 0) {
  {
    int t = rng() % others.size();
    auto tit = others.begin();
    advance(tit, t);
    included.insert(*tit);
    others.erase(tit);
    return;
  }
  int s = rng() % included.size();
  int t = rng() % others.size();
  auto sit = included.begin();
  auto tit = others.begin();
  advance(sit, s);
  advance(tit, t);
  auto f1 = *sit, f2 = *tit;
  included.erase(sit);
  others.erase(tit);
  included.insert(f2);
  others.insert(f1);
}

vector<bool> random_feature_swap(const Graph &g, const vector<bool> &sol) {
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
    if (sol[i]) {
      for (auto feature : g.input.featureDisLiked[i]) {
        includedFeatures.erase(feature);
        otherFeatures.insert(feature);
      }
    }
  }
  vector<bool> output(g.numberOfClients, false);
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
      output[id] = true;
    }
  }
  return output;
}

vector<bool>
SimulatedAnealing::generate_next_solution(const vector<bool> &cur_sol) {
  // if (get_probability() < 0.10)
  //   return random_feature_swap(this->g, cur_sol);
  // if (get_probability() < 0.33)
  //   return RandomGreedy(this->g, cur_sol);
  int s = cur_sol.size();
  int v = rng() % s;
  vector<bool> pos_sol = cur_sol;
  pos_sol[v] = !pos_sol[v];
  return pos_sol;
}

Output SimulatedAnealing::solve() {
  vector<bool> cur_sol = this->init_solver(g);
  SA_soln_status status;
  double cur_temp = init_temp;
  int p = 0;
  for (auto x : cur_sol) {
    p += x;
  }
  int it = 0;
  ofstream fout;
  fout.open("ip4.txt");
  cout << "initial val : " << p << endl;
  fout << 1 << " " << p << " " << 1 << endl;
  while (cur_temp > end_temp) {
    it++;
    for (int i = 0; i < num_iter; i++) {
      vector<bool> pos_sol = this->generate_next_solution(cur_sol);
      status = this->acceptable(cur_sol, pos_sol, cur_temp);

      if (status == SA_soln_status::CHANGE) {
        cur_sol = pos_sol;
      } else if (status == SA_soln_status::GOOD_TO_BREAK) {
        cur_sol = pos_sol;
        break;
      }
    }
    int p = 0;
    for (auto x : cur_sol) {
      p += x;
    }
    bool valid = true;
    for (auto e : this->g.edges) {
      if (cur_sol[e.first] && cur_sol[e.second]) {
        valid = false;
      }
    }
    cur_temp = this->update_temp(cur_temp);
    cout << "At temp " << cur_temp << " val : " << p
         << " with valid : " << valid << endl;
    fout << it << " " << p << " " << valid << endl;
  }
  Output output;
  for (int id = 0; id < this->g.numberOfClients; id++) {
    for (auto feature : g.input.featureLiked[id]) {
      output.features.insert(feature);
    }
    for (auto feature : g.input.featureDisLiked[id]) {
      output.features.insert(feature);
    }
  }
  for (int id = 0; id < this->g.numberOfClients; id++) {
    if (cur_sol[id]) {
      for (auto feature : g.input.featureDisLiked[id]) {
        output.features.erase(feature);
      }
    }
  }
  fout.close();
  return output;
}
