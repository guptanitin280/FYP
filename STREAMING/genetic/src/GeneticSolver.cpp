//
// Created by risha on 27-02-2023.
//
#include <bits/stdc++.h>
#include "../include/GeneticSolver.h"
#include "../../shared/utils.h"

using namespace genetic;

GeneticSolver::GeneticSolver(uint32_t _n,uint32_t _nV,Input &_g,uint32_t _popSize, Picker &_picker, Evolver &_evolver, Breeder &_breeder,uint32_t (* _f)(Genome&),std::vector<std::vector<bool>> (* _baseSol)(Input&))
        :n(_n),nV(_nV),pop_size(_popSize),g(_g),picker(_picker),evolver(_evolver),breeder(_breeder),fitness_fun(_f),simpleSol(_baseSol),maxFitness(0),bestGenome(n,nV,g,_f)
{

    uint32_t to_try=2*pop_size;
    while(population.size()<pop_size){
        if(to_try<=0)break;
        to_try--;
        insertRandom();
    }
}

Genome GeneticSolver::Solve(uint32_t iterations) {
    for(uint32_t i=1;i<iterations;i++)iterate(i);
    return iterate(iterations);
}

Genome GeneticSolver::iterate(uint32_t generation_number) {
    cout<<"iterating..."<<generation_number<<endl;
    const uint32_t EVOLVE_PERIOD=64;
    if(generation_number%EVOLVE_PERIOD  ==0){
        evolver.update_rate(generation_number);
    }
    uint32_t min_fitness = INT_MAX;
    ssize_t worst = -1;
    for (int i = 0; i < 10; ++i) {
        auto idx = rand(0,((int)population.size()) -1);
        auto fitness = population[idx].calc_fitness();
        if (fitness <= min_fitness) {
            min_fitness = fitness;
            worst = idx;
        }
    }

    assert(worst!=-1);
    // The member to be replaced
    auto &member = population[worst];
    uint32_t prevFitness=member.calc_fitness();
    uint32_t to_try=pop_size;
    while(true) {
        if(to_try<=0)break;
        to_try--;
        auto a = picker.pick(population);
        auto b = picker.pick(population);
//        cout<<"prev: "<<member.calc_fitness()<<endl;
        member.modify_gene(breeder.breed(population[a],population[b]));
//        cout<<"breed: "<<member.calc_fitness()<<endl;
        evolver.evolve(member.bits);
//        cout<<"evolve: "<<member.calc_fitness()<<endl;
        greedy_local_search(member.bits,g);
//        cout<<"greedy: "<<member.calc_fitness()<<endl;
        if(member.calc_fitness()>population[a].calc_fitness())
            cout<<population[a].calc_fitness()<<" "<<population[b].calc_fitness()<<" "<<member.calc_fitness()<<endl;

        auto [_, ok] = duplicates.emplace(member.bits);
        if (!ok) {
            continue;
        }
        uint32_t curFitness=member.calc_fitness();
        if(curFitness > maxFitness){
            cout<<"==============================================================================="<<endl;
            maxFitness=curFitness;
            bestGenome.modify_gene(member.bits);
            bestGenome.fitness=curFitness;
        }
        break;
    }
    return bestGenome;


}
bool GeneticSolver::insertRandom() {
    auto bits=(*simpleSol)(g);
    Genome mem(n,nV,g,bits,fitness_fun);
    auto [_, ok] = duplicates.emplace(mem.bits);
    if (!ok) {
        return false;
    }
    population.emplace_back(mem);

    uint32_t curFitness=mem.calc_fitness();
    if(curFitness > maxFitness){
        maxFitness=curFitness;
        bestGenome.modify_gene(mem.bits);
        bestGenome.fitness=curFitness;
    }
    cout<<"initial maxFitness"<<maxFitness<<endl;
    return true;
}

void greedy_local_search(std::vector<std::vector<bool>>& bv, const Input& input) {
    //!!IMPLEMENT

}

