#ifndef FYP_SA_COST_EVALUATOR_H
#define FYP_SA_COST_EVALUATOR_H
#include "../shared/Graph.h"
#include "SAState.h"
#include "SA_HyperParameters.h"
#include <vector>

using namespace std;

class CostEvaluator {
  int A, B;
  Graph &g;

public:
  CostEvaluator(SA_HyperParams &params, Graph &g);
  double operator()(const SAState &sol);
};

#endif
