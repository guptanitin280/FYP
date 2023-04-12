
#ifndef FYP_SIMULATED_ANEALING_H
#define FYP_SIMULATED_ANEALING_H

#include "../shared/Output.h"
#include "AcceptanceEvaluator.h"
#include "SAState.h"
#include "SA_HyperParameters.h"
#include <cstdint>
#include <vector>
using namespace std;
using init_solver_ptr = vector<vector<bool>> (*)(const Input &);

class SimulatedAnealing {
  double init_temp;
  double end_temp;
  double cool_down_rate;
  int32_t num_iter;
  Input input;
  init_solver_ptr init_solver;
  double update_temp(double cur_temp);
  SAState generate_next_solution(const SAState &cur_sol);
  AcceptanceEvaluator acceptable;

public:
  SimulatedAnealing(Input &_input, init_solver_ptr init_solver,
                    SA_HyperParams &params);
  Output solve();
};

#endif
