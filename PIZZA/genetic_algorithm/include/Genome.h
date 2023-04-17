//
// Created by risha on 27-02-2023.
//

#ifndef FYP_GENOME_H
#define FYP_GENOME_H

#include <bits/stdc++.h>
#include "../../shared/Graph.h"
#include "../../shared/utils.h"

namespace genetic{

    class Genome{
    public:
        uint32_t n;
        vector<bool> bits;
        Graph& g;
        uint32_t (* func_ptr)(Genome&) ;
        uint32_t fitness;

        Genome();
        Genome(uint32_t _n,Graph& _g);
        Genome(uint32_t _n,Graph& _g,vector<bool> _bits);
        Genome(uint32_t _n,Graph& _g,uint32_t (* _f)(Genome&));
        Genome(uint32_t _n,Graph& _g,vector<bool> _bits,uint32_t (* _f)(Genome&));

        void modify_gene(vector<bool> new_gene);

        bool is_independent_set();

        uint32_t calc_fitness();

        uint32_t countOnes();

    };
}




#endif //FYP_GENOME_H
