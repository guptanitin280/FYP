//
// Created by risha on 12-04-2023.
//

#ifndef STREAMING_GENETICSOLVER_H
#define STREAMING_GENETICSOLVER_H

#include<bits/stdc++.h>
#include "Genome.h"
#include "../../shared/utils.h"
#include "Genome.h"
#include "Breeder.h"
#include "Picker.h"
#include "Evolver.h"
#include "../../shared/Input.h"
#include "../../shared/utils.h"

void greedy_local_search(std::vector<std::vector<bool>>& bv, const Input& input);

namespace genetic{

    class GeneticSolver{
    public:
        using HashTable =std::set<std::vector<std::vector<bool>>>;

        uint32_t n,nV,pop_size;
        Input& g;
        Picker& picker;
        Evolver& evolver;
        Breeder& breeder;
        uint32_t (* fitness_fun)(Genome&) ;
        std::vector<std::vector<bool>> (* simpleSol)(Input&);
        vector<Genome> population;
        HashTable duplicates;

        uint32_t maxFitness;
        Genome bestGenome;

        GeneticSolver(uint32_t _n,uint32_t _nV,Input& _g,uint32_t _popSize,Picker& _picker,Evolver& _evolver,Breeder& _breeder,uint32_t (* _f)(Genome&),std::vector<std::vector<bool>> (* _baseSol)(Input&));

        Genome Solve(uint32_t iterations);

        Genome iterate(uint32_t generation_number);

        bool insertRandom();


    };





}

#endif //STREAMING_GENETICSOLVER_H
