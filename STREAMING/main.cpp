#include<bits/stdc++.h>
#include "shared/Input.h"
#include "shared/Output.h"
#include "shared/Score.h"
#include "genetic/include/Breeder.h"
#include "genetic/include/Evolver.h"
#include "genetic/include/GeneticSolver.h"
#include "genetic/include/Genome.h"
#include "genetic/include/Picker.h"
#include "genetic/heuristics/fitness_functions/TimeSaved.h"
#include "genetic/heuristics/fitness_functions/CacheUtilisation.h"

#include "heuristics/RandomGreedy.h"



using namespace std;
using namespace genetic;

using namespace std;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }



int main() {
    string filePath = "test_data/me_at_the_zoo.in";

    Input gp(filePath);
    cout<<"Graph Made"<<endl;
    RandomBestPicker picker(150);
    SimpleEvolver evolver(0.03);
    RandomBreeder breeder;
    GeneticSolver solver(gp.cacheServer,gp.videos,gp,250,picker,evolver,breeder, TimeSaved,RandomGreedy);
    Genome result=solver.Solve(150);
    cout<<result.isValid()<<endl;
    cout<<result.calc_fitness()<<endl;
    Output output;
    output.numVideos=gp.videos;
    output.numServers=gp.cacheServer;
    output.videosServed=result.bits;
    cout<<"final ans"<<result.bits<<endl;
    cout<<"score"<<Score::calculate(gp,output);
//    cout<<gp.numberOfClients<<endl;
//    dbg_out(gp.G);


    return 0;
}