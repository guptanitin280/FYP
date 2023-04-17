#include "../algorithms/BruteForce.h"
#include "../heuristics/Greedy.h"
#include "../heuristics/RandomInit.h"
#include "../shared/Graph.h"
#include "../shared/Score.h"
#include "SA_HyperParameters.h"
#include "SimulatedAnealing.h"
#include <bits/stdc++.h>

using namespace std;


int main() {
  string filename = "test_data/gen400-p0-9-75.txt";
  Graph g(filename);
  SA_HyperParams param;
  param.cool_down_rate = 0.96;
  param.cost_eval = {-1.0, 3.0};
  param.init_temp = 60;
  param.no_change_threshhold_per_it = 400;
  param.end_temp = 0.06;
  param.num_iter = 400;

  cout << "====== With heuristics =======" << endl;
  bool enableHeuristic = true;
  SimulatedAnealing sm1(g, RandomInitConst, param, enableHeuristic);
  auto sol = sm1.solve();
  cout << "Final score is :" << Score::calculate(g.input, sol) << endl;

  cout << "\n\n====== Without heuristics =======" << endl;
  enableHeuristic = false;
  SimulatedAnealing sm2(g, RandomInitConst, param, enableHeuristic);
  auto sol2 = sm2.solve();
  cout << "Final score is :" << Score::calculate(g.input, sol2) << endl;

  return 0;
}
