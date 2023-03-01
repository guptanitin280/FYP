#include<bits/stdc++.h>
#include "shared/Graph.h"
#include "genetic_algorithm/include/Breeder.h"
#include "genetic_algorithm/include/Evolver.h"
#include "genetic_algorithm/include/GeneticSolver.h"
#include "genetic_algorithm/include/Genome.h"
#include "genetic_algorithm/include/Picker.h"
#include "genetic_algorithm/heuristics/fitness_functions/NumberOfOnes.h"


vector<bool> timepass(Graph& g){
    vector<bool> temp(g.numberOfClients, false);
    return temp;
}

using namespace std;
using namespace genetic;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

int main() {
    string filePath = "test_data/a.txt";

    dbg_out("hi");
    Graph gp(filePath);
    dbg_out(1);
    RandomBestPicker picker(10);
    dbg_out(2);
    SimpleEvolver evolver(0.05);
    dbg_out(3);
    RandomBreeder breeder;
    dbg_out(4);
    GeneticSolver solver(gp.numberOfClients,gp,20,picker,evolver,breeder,numberOfOnes,timepass);
    dbg_out("bye");
    Genome result=solver.Solve(10);
    dbg_out("chai");
    dbg_out(result.bits);
//    cout<<gp.numberOfClients<<endl;
//    dbg_out(gp.G);


    return 0;
}