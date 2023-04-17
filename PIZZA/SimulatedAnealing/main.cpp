#include "algorithms/BruteForce.h"
#include "algorithms/SimulatedAnealing/SA_HyperParameters.h"
#include "algorithms/SimulatedAnealing/SimulatedAnealing.h"
#include "algorithms/aco/aco.h"
#include "heuristics/Greedy.h"
#include "heuristics/RandomInit.h"
#include "shared/Graph.h"
#include "shared/Score.h"
#include <bits/stdc++.h>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

Graph solve(const string& filePath) {
    ifstream file;
    file.open(filePath);
    Graph graph;
    file >> graph.numberOfClients;
    int edges;
    file >> edges;
    graph.G.resize(graph.numberOfClients);
    for (int i = 0; i < edges; i++) {
        uint32_t u, v;
        file >> u >> v;
        --u;
        --v;
        graph.addEdge(u, v);
    }
    return graph;
}

int main() {

    // string filePath = "../DIMAC_graphs/brock200-2.txt";
    cout << "File name : ";
    string name;
    cin >> name;
    string file = "test_data/" + name + ".txt";
    Input input;
    cout << file << endl;
    //Graph g = (solve(filePath));
     Graph g(file);
    //     dbg_out(o.features);
    //     dbg_out(Score::calculate(input,o));


    SA_HyperParams param;
    param.cool_down_rate = 0.96;
    param.cost_eval = {-1.0, 3.0};
    param.init_temp = 60;
    param.no_change_threshhold_per_it = 400;
    param.end_temp = 0.06;
    param.num_iter = 400;

    //    dbg_out(o.features);
    //    dbg_out(Score::calculate(input,o));

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
    SimulatedAnealing sm(g, RandomInit, param);
    auto sol = sm.solve();
    cout << name << endl;
    dbg_out(Score::calculate(g.input, sol));
    return 0;
}
