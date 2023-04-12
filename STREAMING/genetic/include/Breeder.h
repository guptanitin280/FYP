//
// Created by risha on 27-02-2023.
//

#ifndef STREAMING_BREEDER_H
#define STREAMING_BREEDER_H
#include<bits/stdc++.h>
#include "Genome.h"
#include "../../shared/utils.h"

namespace genetic{

    class Breeder{
    public:
        virtual ~Breeder()=default;

        virtual std::vector<std::vector<bool>> breed(genetic::Genome &gene1, genetic::Genome &gene2)=0;
    };




    class RandomBreeder:public virtual Breeder{
    public:

        RandomBreeder(){};
        virtual std::vector<std::vector<bool>> breed(genetic::Genome &gene1, genetic::Genome &gene2) override{
            //!!IMPLEMENT
            assert(gene1.n_caches == gene2.n_caches);
            assert(gene1.n_videos == gene2.n_videos);
            double gene1_fitness=gene1.calc_fitness(),gene2_fitness=gene2.calc_fitness();
            genetic::Genome child=gene1;
            double flip_to_gene2= std::sqrt(gene2_fitness/2)/(gene1_fitness + gene2_fitness);
            for(uint32_t i=0;i<gene1.n_caches;i++){
                for(uint32_t j=0;i<gene1.n_videos;j++)
                if(get_probability()<flip_to_gene2){
                    child.bits[i][j]=gene2.bits[i][j];
                }
            }
            return child.bits;
        };
        ~RandomBreeder()=default;
    };




}

#endif //STREAMING_BREEDER_H
