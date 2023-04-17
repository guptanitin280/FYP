#include "SimulatedAnealing.h"
#include "../shared/Score.h"
#include "../shared/utils.h"
#include "SAState.h"
#include "SA_HyperParameters.h"
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <vector>

SimulatedAnealing::SimulatedAnealing(Input &_input, init_solver_ptr init_solver,
                                     SA_HyperParams &params,
                                     bool enableHeuristic)
    : input(_input), acceptable(params), init_solver(init_solver),
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

double SimulatedAnealing::update_temp(double cur_temp) {
  return cool_down_rate * cur_temp;
}
SAState SimulatedAnealing::generate_next_solution(const SAState &cur_sol) {
  return cur_sol.getNeighbouringState();
}

void log(ofstream &fout, SAState &curState, int iteration, double temperature) {
  bool valid = curState.isValid();
  cout << "At temp " << fixed << setprecision(8) << temperature
       << " latency : " << curState.getAvgLatencyContri()
       << " with valid : " << valid << endl;
  fout << iteration << " " << curState.score() << " " << valid << endl;
}
Output SimulatedAnealing::solve() {
  vector<vector<bool>> cur_sol_mat =
      this->enableHeuristic
          ? vector<vector<bool>>(input.cacheServer + 1,
                                 vector<bool>(input.videos, true))
          : this->init_solver(input);
  SAState curState(this->input, cur_sol_mat, this->enableHeuristic);
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
    bool valid = curState.isValid();
    cur_temp = this->update_temp(cur_temp);
    log(this->fout, curState, it, cur_temp);
  }
  Output output;
  output.numVideos = this->input.videos;
  output.numServers = this->input.cacheServer;
  output.videosServed = curState.videoServed;
  return output;
}

SimulatedAnealing::~SimulatedAnealing() { this->fout.close(); }
