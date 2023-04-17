#ifndef FYP_SA_HYPERPARAMETER_H
#define FYP_SA_HYPERPARAMETER_H

#include <utility>
struct SA_HyperParams {
  std::pair<double, double> cost_eval;
  double init_temp;
  double end_temp;
  double num_iter;
  double cool_down_rate;
  int no_change_threshhold_per_it;
};

#endif
