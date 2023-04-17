#ifndef FYP_SA_ACCAPTANCEEVALUATOR_H
#define FYP_SA_ACCAPTANCEEVALUATOR_H

#include "CostEvaluator.h"
#include "SAState.h"
#include "SA_HyperParameters.h"
#include <vector>
using namespace std;

enum SA_soln_status { NO_CHANGE, CHANGE, GOOD_TO_BREAK };

class AcceptanceEvaluator {
  CostEvaluator cost_evalute;
  Graph &g;
  int not_changed_until;

  // It will break after some number of consicutive comparison give no change
  int good_to_break_threshhold;

public:
  AcceptanceEvaluator(SA_HyperParams &params, Graph &g);
  SA_soln_status operator()(const SAState &cur_sol, const SAState &pos_sol,
                            double temperature);
};

#endif
