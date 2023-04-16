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
                                     SA_HyperParams &params)
    : input(_input), acceptable(params), init_solver(init_solver) {
  init_temp = params.init_temp;
  end_temp = params.end_temp;
  cool_down_rate = params.cool_down_rate;
  num_iter = params.num_iter;
};

double SimulatedAnealing::update_temp(double cur_temp) {
  return cool_down_rate * cur_temp;
}
SAState SimulatedAnealing::generate_next_solution(const SAState &cur_sol) {
  return cur_sol.getNeighbouringState();
}
Output SimulatedAnealing::solve() {
  // vector<vector<bool>> cur_sol_mat = this->init_solver(input);
  vector<vector<bool>> cur_sol_mat = vector<vector<bool>>(
      input.cacheServer + 1, vector<bool>(input.videos, true));
  SAState curState(this->input, cur_sol_mat);
  Output curOut;
  curOut.numServers = this->input.cacheServer;
  curOut.numVideos = this->input.videos;
  curOut.videosServed = cur_sol_mat;
  cout << Score::calculate(this->input, curOut) << endl;
  SA_soln_status status;
  double cur_temp = init_temp;

  ofstream fout;
  cout << "enter out file " << endl;
  string s;
  cin >> s;
  fout.open(s + ".txt");
  int it = 0;
  fout << it << " " << curState.score() << " " << 1 << endl;
  cout << "initial latency percentage : " << fixed << setprecision(8)
       << curState.getAvgLatencyContri() << endl;
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
    cout << "At temp " << fixed << setprecision(8) << cur_temp
         << " latency : " << curState.getAvgLatencyContri()
         << " with valid : " << valid << endl;
    if (valid)
      fout << it << " " << curState.score() << " " << 1 << endl;
  }
  Output output;
  output.numVideos = this->input.videos;
  output.numServers = this->input.cacheServer;
  output.videosServed = curState.videoServed;
  return output;
}
