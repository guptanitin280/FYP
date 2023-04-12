//
// Created by risha on 27-02-2023.
//
#include <bits/stdc++.h>
#include "../include/Genome.h"

using namespace genetic;

Genome::Genome(uint32_t _n_caches,uint32_t _n_videos):n_caches(_n_caches),n_videos(_n_videos){

    bits.assign(n_caches, std::vector<bool>(n_videos, false));
    func_ptr= nullptr;
    fitness = 0;
}

Genome::Genome(uint32_t _n_caches,uint32_t _n_videos,std::vector<std::vector<bool>> _bits):n_caches(_n_caches),n_videos(_n_videos){
    bits=_bits;
    func_ptr= nullptr;
    fitness = calc_fitness();
}


Genome::Genome(uint32_t _n_caches,uint32_t _n_videos,uint32_t (* _f)(Genome&)):n_caches(_n_caches),n_videos(_n_videos){

    bits.assign(n_caches, std::vector<bool>(n_videos, false));
    func_ptr= _f;
    fitness = 0;
}

Genome::Genome(uint32_t _n_caches,uint32_t _n_videos,std::vector<std::vector<bool>> _bits,uint32_t (* _f)(Genome&)):n_caches(_n_caches),n_videos(_n_videos){

    bits=_bits;
    func_ptr= _f;
    fitness = 0;
}


void Genome::modify_gene(std::vector<std::vector<bool>> new_gene){
    bits=new_gene;
}

uint32_t Genome::calc_fitness() {
    fitness=(*func_ptr)(*this);
    return fitness;
}



