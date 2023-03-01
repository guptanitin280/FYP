#include<bits/stdc++.h>
#include "algorithms/BruteForce.h"
#include "algorithms/Greedy.h"
#include "shared/Graph.h"
#include "shared/Score.h"
#include "algorithms/aco/aco.h"

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

int main() {
    string filePath = "test_data/e.txt";

    Input input(filePath);
    aco solver=aco(input);
    Output o=solver.run(1);
    dbg_out(o.features);
    dbg_out(Score::calculate(input,o));

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


    return 0;
}

