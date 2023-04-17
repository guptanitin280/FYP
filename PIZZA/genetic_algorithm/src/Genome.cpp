//
// Created by risha on 27-02-2023.
//
#include <bits/stdc++.h>
#include "../include/Genome.h"

using namespace genetic;

Genome::Genome(uint32_t _n,Graph& _g):n(_n),g(_g){

    bits.assign(n, false);
    func_ptr= nullptr;
    fitness = 0;
}

Genome::Genome(uint32_t _n,Graph& _g,vector<bool> _bits):n(_n),g(_g){
    bits=_bits;
    func_ptr= nullptr;
    fitness = calc_fitness();
}

Genome::Genome(uint32_t _n,Graph& _g,uint32_t (* _f)(Genome&)):n(_n),g(_g){
    bits.assign(n, false);
    func_ptr= _f;
    fitness = 0;
}

Genome::Genome(uint32_t _n,Graph& _g,vector<bool>_bits,uint32_t (* _f)(Genome&)):n(_n),g(_g){
    bits=_bits;
    func_ptr= _f;
    fitness = calc_fitness();
}

void Genome::modify_gene(vector<bool> new_gene){
    bits=new_gene;
    if(get_probability()< 0.002)cout<<"SOLUTION IMPROVED"<<endl;
}

uint32_t Genome::calc_fitness() {
    fitness=(*func_ptr)(*this);
    return fitness;
}


bool Genome::is_independent_set(){
    for(auto x:g.edges){
        if(bits[x.first] && bits[x.second])return false;
    }
    return true;
}

uint32_t Genome::countOnes() {
    return std::count(bits.begin(),bits.end(), true);
}



