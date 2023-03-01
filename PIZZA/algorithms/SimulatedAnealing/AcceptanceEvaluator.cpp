#include "AcceptanceEvaluator.h"
#include "../../shared/utils.h"
#include "CostEvaluator.h"
#include "SA_HyperParameters.h"
AcceptanceEvaluator::AcceptanceEvaluator(SA_HyperParams &params, Graph &g)
    : cost_evalute(params, g), g(g) {
  this->not_changed_until = 0;
  this->good_to_break_threshhold = not_changed_until;
}

SA_soln_status AcceptanceEvaluator::operator()(const vector<bool> &cur_sol,
                                               const vector<bool> &pos_sol,
                                               double temperature) {

  SA_soln_status status;
  double cur_cost = cost_evalute(cur_sol);
  double pos_cost = cost_evalute(pos_sol);

  if (pos_cost < cur_cost) {
    status = SA_soln_status::CHANGE;
    this->not_changed_until = 0;
    return status;
  }

  double rand_prob = get_probability();

  double prob = (cur_cost - pos_cost) / temperature;
  int s = cur_sol.size();
  for (int i = 0; i < s; i++) {
    if (cur_sol[i] != pos_sol[i]) {
      double deg_cont = (2 * g.G[i].size()) / (double)(g.edges.size());
      if (pos_sol[i]) {
        // node is being added :
        prob *= (1 + deg_cont);
      } else {
        prob *= (1 - deg_cont);
      }
    }
  }
  prob = exp(prob);
  if (rand_prob <= prob) {
    this->not_changed_until = 0;
    return SA_soln_status::CHANGE;
  }
  this->not_changed_until++;
  if (this->not_changed_until > this->good_to_break_threshhold) {
    this->not_changed_until = 0;
    return SA_soln_status::GOOD_TO_BREAK;
  }
  return SA_soln_status::NO_CHANGE;
}
