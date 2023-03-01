#include "algorithms/SimulatedAnealing/SA_HyperParameters.h"
#include "algorithms/SimulatedAnealing/SimulatedAnealing.h"
#include "genetic_algorithm/heuristics/fitness_functions/NumberOfOnes.h"
#include "genetic_algorithm/include/Breeder.h"
#include "genetic_algorithm/include/Evolver.h"
#include "genetic_algorithm/include/GeneticSolver.h"
#include "genetic_algorithm/include/Genome.h"
#include "genetic_algorithm/include/Picker.h"
#include "heuristics/Greedy.h"
#include "shared/Graph.h"
#include <bits/stdc++.h>

vector<bool> timepass(Graph& g){
    vector<bool> temp(g.numberOfClients, false);
    return temp;
}

using namespace std;
using namespace genetic;

using namespace std;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }



int main() {
    string filePath = "test_data/e.txt";

    Graph gp(filePath);
    cout<<"Graph Made"<<endl;
    //   RandomBestPicker picker(5);
    // SimpleEvolver evolver(0.05);
    // RandomBreeder breeder;
    // GeneticSolver
    // solver(gp.numberOfClients,gp,10,picker,evolver,breeder,numberOfOnes,Greedy);
    // Genome result=solver.Solve(5);
    // cout<<result.is_independent_set()<<endl;
    // cout<<"final ans"<<result.bits<<endl;
    //    cout<<gp.numberOfClients<<endl;
    //    dbg_out(gp.G);

    SA_HyperParams param;
    param.cool_down_rate = 0.96;
    param.cost_eval = {-1.0, 1.0};
    param.init_temp = 60;
    param.no_change_threshhold_per_it = 70;
    param.end_temp = 0.06;
    param.num_iter = 100;

    SimulatedAnealing sm(gp, Greedy, param);
    auto sol = sm.solve();
    int ans = 0;
    for (auto x : sol) {
      if (x)
        ans++;
    }
    cout << ans << endl;
    return 0;
}
