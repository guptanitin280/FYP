//
// Created by risha on 27-02-2023.
//
#include <bits/stdc++.h>

#include <utility>
#include "../include/Genome.h"

using namespace genetic;

Genome::Genome(uint32_t _n_caches,uint32_t _n_videos,Input& _g):n_caches(_n_caches),n_videos(_n_videos),g(_g){

    bits.assign(n_caches, std::vector<bool>(n_videos, false));
    func_ptr= nullptr;
    fitness = 0;
}

Genome::Genome(uint32_t _n_caches,uint32_t _n_videos,Input& _g,std::vector<std::vector<bool>> _bits):n_caches(_n_caches),n_videos(_n_videos),g(_g){
    bits=std::move(_bits);
    func_ptr= nullptr;
    fitness = calc_fitness();
}


Genome::Genome(uint32_t _n_caches,uint32_t _n_videos,Input& _g,uint32_t (* _f)(Genome&)):n_caches(_n_caches),n_videos(_n_videos),g(_g){

    bits.assign(n_caches, std::vector<bool>(n_videos, false));
    func_ptr= _f;
    fitness = 0;
}

Genome::Genome(uint32_t _n_caches,uint32_t _n_videos,Input& _g,std::vector<std::vector<bool>> _bits,uint32_t (* _f)(Genome&)):n_caches(_n_caches),n_videos(_n_videos),g(_g){

    bits=std::move(_bits);
    func_ptr= _f;
    fitness = 0;
}


void Genome::modify_gene(std::vector<std::vector<bool>> new_gene){
    bits=std::move(new_gene);
}

uint32_t Genome::calc_fitness() {
    fitness=(*func_ptr)(*this);
    return fitness;
}

bool Genome::isValid(){
    for (int cacheServer_id = 1; cacheServer_id <= g.cacheServer;
         cacheServer_id++) {
        int filled_cap = 0;
        for (int video_id = 0; video_id < g.videos; video_id++) {
            if (bits[cacheServer_id][video_id]) {
                filled_cap += g.videoSizes[video_id];
            }
        }
        if (filled_cap > g.cacheServerCapacity)
            return false;
    }
    return true;
}



