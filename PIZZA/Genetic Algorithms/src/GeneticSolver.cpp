//
// Created by risha on 27-02-2023.
//
#include <bits/stdc++.h>
#include "../include/GeneticSolver.h"
#include "../../shared/utils.h"

using namespace genetic;

GeneticSolver::GeneticSolver(uint32_t _n, Graph &_g,uint32_t _popSize, Picker &_picker, Evolver &_evolver, Breeder &_breeder,uint32_t (* _f)(Genome&),Genome (* _baseMis)(Graph&))
:n(_n),pop_size(_popSize),g(_g),picker(_picker),evolver(_evolver),breeder(_breeder),fitness_fun(_f),simple_mis(_baseMis)
{
    while(population.size()<pop_size){
        insertRandom();
    }
}

Genome GeneticSolver::Solve(uint32_t iterations) {
    for(uint32_t i=1;i<iterations;i++)iterate(i);
    return iterate(iterations);
}

Genome GeneticSolver::iterate(uint32_t generation_number) {
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

    // The member to be replaced
    auto &member = population[worst];
    while(true) {
        auto a = picker.pick(population);
        auto b = picker.pick(population);
        if(a==b)continue;



        member.modify_gene(breeder.breed(population[a],population[b]));
        evolver.evolve(member.bits);

        auto [_, ok] = duplicates_.emplace(member.genome());
        if (!ok) {
            continue;
        }

        member.recompute_fitness(g_);
        total_fitness_ += member.fitness();
        break;
    }

}
bool GeneticSolver::insertRandom() {
    Genome mem=(*simple_mis)(g);
    auto [_, ok] = duplicates.emplace(mem.bits);
    if (!ok) {
        return false;
    }
    population.emplace_back(mem);
    return true;
}
