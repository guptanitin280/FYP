#ifndef FYP_SA_COST_EVALUATOR_H
#define FYP_SA_COST_EVALUATOR_H
#include "SAState.h"
#include "SA_HyperParameters.h"

using namespace std;

class CostEvaluator {
  double LatencyFactor, ServerUtilizationFactor, ExcessCachePanelty;

public:
  CostEvaluator(SA_HyperParams &params);
  double operator()(const SAState &sol);
};

#endif
