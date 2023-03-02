#include<bits/stdc++.h>
#include "shared/Graph.h"
#include "genetic_algorithm/include/Breeder.h"
#include "genetic_algorithm/include/Evolver.h"
#include "genetic_algorithm/include/GeneticSolver.h"
#include "genetic_algorithm/include/Genome.h"
#include "genetic_algorithm/include/Picker.h"
#include "genetic_algorithm/heuristics/fitness_functions/NumberOfOnes.h"
#include "heuristics/RandomGreedy.h"


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
    string filePath = "test_data/d.txt";

    Graph gp(filePath);
    cout<<"Graph Made"<<endl;
    RandomBestPicker picker(100);
    SimpleEvolver evolver(0.03);
    RandomBreeder breeder;
    GeneticSolver solver(gp.numberOfClients,gp,200,picker,evolver,breeder,numberOfOnes,RandomGreedy);
    Genome result=solver.Solve(750);
    cout<<result.is_independent_set()<<endl;
    cout<<result.countOnes()<<endl;
    cout<<"final ans"<<result.bits<<endl;
//    cout<<gp.numberOfClients<<endl;
//    dbg_out(gp.G);


    return 0;
}