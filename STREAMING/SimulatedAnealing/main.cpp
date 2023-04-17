#include "../heuristics/Greedy.h"
#include "../heuristics/RandomGreedy.h"
#include "../shared/Input.h"
#include "../shared/Score.h"
#include "SA_HyperParameters.h"
#include "SimulatedAnealing.h"
#include <bits/stdc++.h>

void solve() {
  Input I("test_data/me_at_the_zoo.in");
  SA_HyperParams param;
  param.cool_down_rate = 0.96;
  param.cost_eval = {-5, 0, 100};
  param.init_temp = 60;
  param.no_change_threshhold_per_it = 200;
  param.end_temp = 0.06;
  param.num_iter = 1000;
  cout << "====== With heuristics =======" << endl;
  bool enableHeuristic = true;
  SimulatedAnealing sm1(I, RandomGreedyConst, param, enableHeuristic);
  auto sol = sm1.solve();
  cout << "Final score is :" << Score::calculate(I, sol) << endl;

  cout << "\n\n====== Without heuristics =======" << endl;
  enableHeuristic = false;
  SimulatedAnealing sm2(I, RandomGreedyConst, param, enableHeuristic);
  auto sol2 = sm2.solve();

  cout << "Final score is :" << Score::calculate(I, sol2) << endl;
}

int32_t main() { solve(); }
