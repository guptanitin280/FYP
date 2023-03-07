#include<bits/stdc++.h>
#include "algorithms/BruteForce.h"
#include "heuristics/Greedy.h"
#include "shared/Graph.h"
#include "shared/Score.h"
#include "algorithms/aco/aco.h"

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
//    string filePath = "../DIMAC_graphs/gen400-p0-9-75.txt";
//
//    Input input;
//    Graph g=(solve(filePath));
//
//    aco solver=aco(g);
//    Output o=solver.run(3001);
    string filePath = "test_data/C500-9.txt";
    aco solver = aco(Input(filePath));
    solver.initializePheromoneClassicalWay=false;
    Output o = solver.run(3001);
//    dbg_out(o.features);
    dbg_out(Score::calculate(Input(filePath),o));
}