#include "CostEvaluator.h"

CostEvaluator::CostEvaluator(SA_HyperParams &params) {
  auto [a, b, c] = params.cost_eval;
  this->LatencyFactor = a;
  this->ServerUtilizationFactor = b;
  this->ExcessCachePanelty = c;
}

double CostEvaluator::operator()(const SAState &sol) {
  double avgLatency = sol.getAvgLatencyContri();
  auto [cache_use, cache_excess] = sol.cacheServerUtilisation();
  return this->LatencyFactor * avgLatency +
         this->ExcessCachePanelty * cache_excess +
         this->ServerUtilizationFactor * cache_use;
}
