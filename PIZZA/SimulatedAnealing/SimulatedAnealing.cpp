#include "SimulatedAnealing.h"
#include "../shared/utils.h"
#include "SAState.h"
#include "SA_HyperParameters.h"
#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

SimulatedAnealing::SimulatedAnealing(Graph &_g, init_solver_ptr init_solver,
                                     SA_HyperParams &params,
                                     bool enableHeuristic)
    : g(_g), acceptable(params, g), init_solver(init_solver),
      enableHeuristic(enableHeuristic) {
  init_temp = params.init_temp;
  end_temp = params.end_temp;
  cool_down_rate = params.cool_down_rate;
  num_iter = params.num_iter;
  if (enableHeuristic) {
    fout.open("heuristic.txt");
  } else {
    fout.open("non-heuristic.txt");
  }
};

SimulatedAnealing::~SimulatedAnealing() { fout.close(); }

double SimulatedAnealing::update_temp(double cur_temp) {
  return cool_down_rate * cur_temp;
}
SAState SimulatedAnealing::generate_next_solution(const SAState &curState) {
  return curState.getNeighbouringState();
}

void log(ofstream &fout, SAState &curState, int iteration, double temperature) {
  bool valid = curState.isValid();
  cout << "At temp " << fixed << setprecision(8) << temperature
       << " value : " << curState.getNumClients() << " with valid : " << valid
       << endl;
  fout << iteration << " " << curState.score() << " " << valid << endl;
}

Output generate_output(const SAState &state) {
  Output output;
  const Graph &g = state.graph;
  for (int id = 0; id < g.numberOfClients; id++) {
    for (auto feature : g.input.featureLiked[id]) {
      output.features.insert(feature);
    }
    for (auto feature : g.input.featureDisLiked[id]) {
      output.features.insert(feature);
    }
  }
  for (int id = 0; id < g.numberOfClients; id++) {
    if (state.clientsSatistied[id]) {
      for (auto feature : g.input.featureDisLiked[id]) {
        output.features.erase(feature);
      }
    }
  }
  return output;
}
Output SimulatedAnealing::solve() {
  vector<bool> cur_sol = this->init_solver(g);
  SAState curState(this->g, cur_sol, this->enableHeuristic);
  SA_soln_status status;
  double cur_temp = init_temp;
  int it = 0;
  log(this->fout, curState, it, cur_temp);

  while (cur_temp > end_temp) {
    it++;
    for (int i = 0; i < num_iter; i++) {
      SAState posState = this->generate_next_solution(curState);
      status = this->acceptable(curState, posState, cur_temp);

      if (status == SA_soln_status::CHANGE) {
        curState = posState;
      } else if (status == SA_soln_status::GOOD_TO_BREAK) {
        curState = posState;
        break;
      }
    }
    cur_temp = this->update_temp(cur_temp);
    log(this->fout, curState, it, cur_temp);
  }
  return generate_output(curState);
}
