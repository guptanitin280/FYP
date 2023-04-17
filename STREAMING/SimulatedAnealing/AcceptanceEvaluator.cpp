#include "AcceptanceEvaluator.h"
#include "../shared/utils.h"
#include "CostEvaluator.h"
#include "SA_HyperParameters.h"
#include <iomanip>
AcceptanceEvaluator::AcceptanceEvaluator(SA_HyperParams &params)
    : cost_evalute(params) {
  this->not_changed_until = 0;
  this->good_to_break_threshhold = not_changed_until;
}

SA_soln_status AcceptanceEvaluator::operator()(const SAState &cur_sol,
                                               const SAState &pos_sol,
                                               double temperature) {

  SA_soln_status status;
  double cur_cost = cost_evalute(cur_sol);
  double pos_cost = cost_evalute(pos_sol);

  if (pos_cost <= cur_cost) {
    status = SA_soln_status::CHANGE;
    this->not_changed_until = 0;
    return status;
  }

  double rand_prob = get_probability();

  double prob = (cur_cost - pos_cost) / temperature;
  prob = exp(prob);
  if (rand_prob < prob) {
    // cout << "probabilty explore" << fixed << setprecision(10) << prob <<
    // endl;
    this->not_changed_until = 0;
    return SA_soln_status::CHANGE;
  }
  this->not_changed_until++;
  if (this->not_changed_until < this->good_to_break_threshhold) {
    this->not_changed_until = 0;
    return SA_soln_status::GOOD_TO_BREAK;
  }
  return SA_soln_status::NO_CHANGE;
}
