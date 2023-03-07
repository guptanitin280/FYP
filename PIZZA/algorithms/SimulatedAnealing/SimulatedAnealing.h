
#ifndef FYP_SIMULATED_ANEALING_H
#define FYP_SIMULATED_ANEALING_H

#include "../../shared/Graph.h"
#include "../../shared/Output.h"
#include "AcceptanceEvaluator.h"
#include "SA_HyperParameters.h"
#include <cstdint>
#include <vector>
using namespace std;
using init_solver_ptr = vector<bool> (*)(const Graph &);

class SimulatedAnealing {
  double init_temp;
  double end_temp;
  double cool_down_rate;
  int32_t num_iter;
  Graph g;
  init_solver_ptr init_solver;
  double update_temp(double cur_temp);
  vector<bool> generate_next_solution(const vector<bool> &cur_sol);
  AcceptanceEvaluator acceptable;

public:
  SimulatedAnealing(Graph &_g, init_solver_ptr init_solver,
                    SA_HyperParams &params);
  Output solve();
};

#endif
