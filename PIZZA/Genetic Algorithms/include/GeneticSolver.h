//
// Created by risha on 27-02-2023.
//

#ifndef FYP_GENETICSOLVER_H
#define FYP_GENETICSOLVER_H

#include<bits/stdc++.h>
#include "Genome.h"
#include "../../shared/utils.h"
#include "Genome.h"
#include "Breeder.h"
#include "Picker.h"
#include "Evolver.h"
#include "../../shared/Graph.h"
#include "../../shared/utils.h"

namespace genetic{

    class GeneticSolver{
    public:
        using HashTable =std::unordered_set<vector<bool>,custom_hash>;

        uint32_t n,pop_size;
        Graph& g;
        Picker& picker;
        Evolver& evolver;
        Breeder& breeder;
        uint32_t (* fitness_fun)(Genome&) ;
        Genome (* simple_mis)(Graph&);
        vector<Genome> population;
        HashTable duplicates;

        GeneticSolver(uint32_t _n,Graph& _g,uint32_t _popSize,Picker& _picker,Evolver& _evolver,Breeder& _breeder,uint32_t (* _f)(Genome&),Genome (* _baseMis)(Graph&));

        Genome Solve(uint32_t iterations);

        Genome iterate(uint32_t generation_number);

        bool insertSpecificGenome(Genome& gene);

        bool insertRandom();


    };





}

#endif //FYP_GENETICSOLVER_H


