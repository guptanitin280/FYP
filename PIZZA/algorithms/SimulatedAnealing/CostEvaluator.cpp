#include "CostEvaluator.h"
#include "SA_HyperParameters.h"
#include <vector>

CostEvaluator::CostEvaluator(SA_HyperParams &params, Graph &g) : g(g) {
  this->A = params.cost_eval.first;
  this->B = params.cost_eval.second;
}

double CostEvaluator::operator()(const vector<bool> &sol) {
  int e1 = 0;
  for (auto x : sol)
    e1 += x;
  int e2 = 0;
  int n = this->g.numberOfClients;
  for (int node = 0; node < n; node++) {
    for (int neighbour : g.G[node]) {
      if (sol[node] && sol[neighbour])
        e2++;
    }
  }
  e2 /= 2;
  return this->A * e1 + this->B * e2;
}
