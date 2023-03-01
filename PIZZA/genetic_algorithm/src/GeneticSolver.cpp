//
// Created by risha on 27-02-2023.
//
#include <bits/stdc++.h>
#include "../include/GeneticSolver.h"
#include "../../shared/utils.h"

using namespace genetic;

GeneticSolver::GeneticSolver(uint32_t _n, Graph &_g,uint32_t _popSize, Picker &_picker, Evolver &_evolver, Breeder &_breeder,uint32_t (* _f)(Genome&),vector<bool> (* _baseMis)(Graph&))
:n(_n),pop_size(_popSize),g(_g),picker(_picker),evolver(_evolver),breeder(_breeder),fitness_fun(_f),simple_mis(_baseMis),maxFitness(0),bestGenome(n,g)
{
    while(population.size()<pop_size){
        insertRandom();
//        cout<<population.size()<<endl;
    }
}

Genome GeneticSolver::Solve(uint32_t iterations) {
    for(uint32_t i=1;i<iterations;i++)iterate(i);
    return iterate(iterations);
}

Genome GeneticSolver::iterate(uint32_t generation_number) {
    cout<<"iterating..."<<endl;
    const uint32_t EVOLVE_PERIOD=64;
    if(generation_number%EVOLVE_PERIOD  ==0){
        evolver.update_rate(generation_number);
    }
    uint32_t min_fitness = 0;
    ssize_t worst = -1;
    for (int i = 0; i < 10; ++i) {
        auto idx = rand(0,population.size());
        auto fitness = population[idx].fitness;
        if (fitness < min_fitness) {
            min_fitness = fitness;
            worst = idx;
        }
    }

    assert(worst!=-1);
    // The member to be replaced
    auto &member = population[worst];
    while(true) {
        auto a = picker.pick(population);
        auto b = picker.pick(population);

        member.modify_gene(breeder.breed(population[a],population[b]));
        evolver.evolve(member.bits);
        greedy_local_search(member.bits,g);

        auto [_, ok] = duplicates.emplace(member.bits);
        if (!ok) {
            continue;
        }
        uint32_t curFitness=member.calc_fitness();
        if(curFitness > maxFitness){
            maxFitness=curFitness;
            bestGenome.modify_gene(member.bits);
            bestGenome.fitness=curFitness;
        }
        break;
    }

    return bestGenome;


}
bool GeneticSolver::insertRandom() {
    auto bits=(*simple_mis)(g);
    Genome mem(n,g,bits,fitness_fun);
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
    return true;
}

void greedy_local_search(std::vector<bool>& bv, const Graph& graph) {
    std::set<int> excluded_vertices;

    for (int v = 0; v < bv.size(); ++v) {
        if (!bv[v]) {
            excluded_vertices.insert(v);
            continue;
        }

        for (int u : graph.G[v]) {
            if (excluded_vertices.count(u) > 0) {
                continue;
            }

            bv[u] = false;
            excluded_vertices.insert(u);
        }
    }

    for(auto v:excluded_vertices){
        bool hasNeighbours=false;
        for(auto u:graph.G[v]){
            if(bv[u]){
                hasNeighbours=true;
                break;
            }
        }
        if(!hasNeighbours)bv[v]=true;
    }

}

