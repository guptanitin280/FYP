#include "SimulatedAnealing.h"
#include "../../shared/utils.h"
#include "SA_HyperParameters.h"
#include <vector>

SimulatedAnealing::SimulatedAnealing(Graph &_g, init_solver_ptr init_solver,
                                     SA_HyperParams &params)
    : g(_g), acceptable(params, g), init_solver(init_solver) {
  init_temp = params.init_temp;
  end_temp = params.end_temp;
  cool_down_rate = params.cool_down_rate;
  num_iter = params.num_iter;
};

double SimulatedAnealing::update_temp(double cur_temp) {
  return cool_down_rate * cur_temp;
}

vector<bool>
SimulatedAnealing::generate_next_solution(const vector<bool> &cur_sol) {
  int s = cur_sol.size();
  int v = rng() % s;
  vector<bool> pos_sol = cur_sol;
  pos_sol[v] = !pos_sol[v];
  return pos_sol;
}

vector<bool> SimulatedAnealing::solve() {
  vector<bool> cur_sol = this->init_solver(g);
  SA_soln_status status;
  double cur_temp = init_temp;
  int p = 0;
  for (auto x : cur_sol) {
    p += x;
  }
  cout << "initial val : " << p << endl;
  while (cur_temp > end_temp) {
    for (int i = 0; i < num_iter; i++) {
      vector<bool> pos_sol = this->generate_next_solution(cur_sol);
      status = this->acceptable(cur_sol, pos_sol, cur_temp);

      if (status == SA_soln_status::CHANGE) {
        cur_sol = pos_sol;
      } else if (status == SA_soln_status::GOOD_TO_BREAK) {
        cur_sol = pos_sol;
        break;
      }
    }
    int p = 0;
    for (auto x : cur_sol) {
      p += x;
    }
    bool valid = true;
    for (auto e : this->g.edges) {
      if (cur_sol[e.first] && cur_sol[e.second]) {
        valid = false;
      }
    }
    cur_temp = this->update_temp(cur_temp);
    cout << "At temp " << cur_temp << " val : " << p
         << " with valid : " << valid << endl;
  }
  return cur_sol;
}
