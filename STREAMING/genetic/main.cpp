#include<bits/stdc++.h>
#include "shared/Input.h"
#include "shared/Output.h"
#include "shared/Score.h"

#include "genetic/include/Breeder.h"
#include "genetic/include/Evolver.h"
#include "genetic/include/GeneticSolver.h"
#include "genetic/include/GeneticConstants.h"
#include "genetic/include/Genome.h"
#include "genetic/include/Picker.h"
#include "genetic/heuristics/fitness_functions/TimeSaved.h"
#include "heuristics/RandomGreedy.h"


using namespace std;
using namespace genetic;

using namespace std;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }



int main() {
    string filePath = "test_data/G.txt";

    Input gp(filePath);
    RandomBestPicker picker(params::PICKER_SAMPLES);
    SimpleEvolver evolver(params::EVOLUTION_RATE);
    RandomBreeder breeder;
    GeneticSolver solver(gp.cacheServer,gp.videos,gp,params::POP_SIZE,picker,evolver,breeder, TimeSaved,RandomGreedy);
    Genome result=solver.Solve(50);
    cout<<result.isValid()<<endl;
    cout<<result.calc_fitness()<<endl;
    Output op;
    op.numServers=gp.cacheServer;
    op.numVideos=gp.videos;
    op.videosServed=result.bits;
    cout<<Score::calculate(gp,op)<<endl;


    return 0;
}