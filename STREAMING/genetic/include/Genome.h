//
// Created by risha on 27-02-2023.
//

#ifndef FYP_GENOME_H
#define FYP_GENOME_H

#include <bits/stdc++.h>

namespace genetic{

    class Genome{
    public:
        uint32_t n_caches;
        uint32_t n_videos;
        std::vector<std::vector<bool>> bits;
        uint32_t (* func_ptr)(Genome&) ;
        uint32_t fitness;

        Genome();
        Genome(uint32_t _n_caches,uint32_t _n_videos);
        Genome(uint32_t _n_caches,uint32_t _n_videos,std::vector<std::vector<bool>> _bits);
        Genome(uint32_t _n_caches,uint32_t _n_videos,uint32_t (* _f)(Genome&));
        Genome(uint32_t _n_caches,uint32_t _n_videos,std::vector<std::vector<bool>> _bits,uint32_t (* _f)(Genome&));

        void modify_gene(std::vector<std::vector<bool>> new_gene);

        uint32_t calc_fitness();

    };
}




#endif //FYP_GENOME_H
