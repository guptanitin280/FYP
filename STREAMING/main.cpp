#include "SimulatedAnealing/SA_HyperParameters.h"
#include "SimulatedAnealing/SimulatedAnealing.h"
#include "heuristics/Greedy.h"
#include "heuristics/RandomGreedy.h"
#include "shared/Input.h"
#include "shared/Score.h"
#include <bits/stdc++.h>

#define int long long

#define nitin                                                                  \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(nullptr)
using namespace std;
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.f << ", " << p.second << ')';
}
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef FYP
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

void solve() {
  Input I("test_data/me_at_the_zoo.in");

  SA_HyperParams param;
  param.cool_down_rate = 0.96;
  param.cost_eval = {-5, 0, 100};
  param.init_temp = 60;
  param.no_change_threshhold_per_it = 200;
  param.end_temp = 0.06;
  param.num_iter = 1000;

  SimulatedAnealing sm(I, RandomGreedyConst, param, true);
  auto sol = sm.solve();
  dbg_out(Score::calculate(I, sol));
}

int32_t main() {
  nitin;
  solve();
}
