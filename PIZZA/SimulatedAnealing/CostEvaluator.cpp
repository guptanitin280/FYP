#include "CostEvaluator.h"
#include "SA_HyperParameters.h"
#include <vector>

CostEvaluator::CostEvaluator(SA_HyperParams &params, Graph &g) : g(g) {
  this->A = params.cost_eval.first;
  this->B = params.cost_eval.second;
}

double CostEvaluator::operator()(const SAState &sol) {
  return this->A * sol.getNumClients() +
         this->B * sol.getInvalidClientsPenalty();
}
