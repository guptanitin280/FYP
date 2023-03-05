#include "algorithms/BruteForce.h"
#include "algorithms/SimulatedAnealing/SA_HyperParameters.h"
#include "algorithms/SimulatedAnealing/SimulatedAnealing.h"
#include "algorithms/aco/aco.h"
#include "heuristics/Greedy.h"
#include "shared/Graph.h"
#include "shared/Score.h"
#include <bits/stdc++.h>
#include <vector>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

Graph solve(string filePath) {
    ifstream file;
    file.open(filePath);
    Graph graph;
    file >> graph.numberOfClients;
    int edges;
    int n = graph.numberOfClients;
    file >> edges;
    set<pair<int, int>> st;
    graph.G.resize(graph.numberOfClients);
    for (int i = 0; i < edges; i++) {
        uint32_t u, v;
        file >> u >> v;
        --u;
        --v;
        if (u > v)
          swap(u, v);
        st.insert({u, v});
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          if (st.count({i, j})) {
            continue;
          } else {
            graph.addEdge(i, j);
          }
        }
    }
    return graph;
}

int main() {
    string filePath = "../DIMAC_graphs/brock200-2.txt";
    string file = "test_data/e.txt";
    Input input;
    Graph g = (solve(filePath));
    // Graph g(file);
    //     dbg_out(o.features);
    //     dbg_out(Score::calculate(input,o));

    //    BruteForce bf(filePath);
    //    Output o = bf.solve();
    //    dbg_out(o.features);
    //
    //    Greedy gd(filePath);
    //    Output greedy_output = gd.solve();
    //    dbg_out(greedy_output.features);
    //
    //    dbg_out(Score::calculate(gd.input,greedy_output));

    //    Graph gp(filePath);
    //    cout<<gp.numberOfClients<<endl;
    //    dbg_out(gp.G);

    SA_HyperParams param;
    param.cool_down_rate = 0.96;
    param.cost_eval = {-1.0, 3.0};
    param.init_temp = 100;
    param.no_change_threshhold_per_it = 200;
    param.end_temp = 0.01;
    param.num_iter = 500;

    SimulatedAnealing sm(g, Greedy, param);
    auto sol = sm.solve();
    int ans = 0;
    for (auto x : sol) {
      if (x)
        ans++;
    }
    cout << ans << endl;
    return 0;
}
