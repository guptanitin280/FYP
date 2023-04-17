//
// Created by risha on 27-02-2023.
//
#include <bits/stdc++.h>
#include "../include/GeneticSolver.h"
#include "../../shared/utils.h"

using namespace genetic;

GeneticSolver::GeneticSolver(uint32_t _n, Graph &_g,uint32_t _popSize, Picker &_picker, Evolver &_evolver, Breeder &_breeder,uint32_t (* _f)(Genome&),vector<bool> (* _baseMis)(Graph&))
:n(_n),pop_size(_popSize),g(_g),picker(_picker),evolver(_evolver),breeder(_breeder),fitness_fun(_f),simple_mis(_baseMis),maxFitness(0),bestGenome(n,g,_f)
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
    const uint32_t EVOLVE_PERIOD=25;
    if(generation_number%EVOLVE_PERIOD  ==0){
        evolver.update_rate(generation_number);
    }
    uint32_t min_fitness = INT_MAX;
    ssize_t worst = -1;
    for (int i = 0; i < 20; ++i) {
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
        member.modify_gene(breeder.breed(population[a],population[b]));
        evolver.evolve(member.bits);
        greedy_local_search(member.bits,g);
        auto [_, ok] = duplicates.emplace(member.bits);
        if (!ok) {
            continue;
        }
        uint32_t curFitness=member.calc_fitness();
        if(curFitness > population[a].calc_fitness() || curFitness > population[b].calc_fitness()){
            cout<<"SOLUTION IMPROVED"<<endl;
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
    std::unordered_set<int> excluded_vertices;
    vector<int> iter(graph.numberOfClients);
    std::iota(iter.begin(),iter.end(),0);
    std::sort(iter.begin(),iter.end(),[&](int a,int b){
        return graph.G[a].size() < graph.G[b].size();
    });

    for (int v:iter) {
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

