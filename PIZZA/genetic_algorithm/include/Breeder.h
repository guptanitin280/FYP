//
// Created by risha on 27-02-2023.
//

#ifndef FYP_BREEDER_H
#define FYP_BREEDER_H
#include<bits/stdc++.h>
#include "Genome.h"
#include "../../shared/utils.h"

namespace genetic{

    class Breeder{
    public:
        virtual ~Breeder()=default;

        virtual vector<bool> breed(genetic::Genome &gene1, genetic::Genome &gene2)=0;
    };




    class RandomBreeder:public virtual Breeder{
    public:

        RandomBreeder(){};
        virtual vector<bool> breed(genetic::Genome &gene1, genetic::Genome &gene2) override{
            assert(gene1.n == gene2.n);
            genetic::Genome child=gene1;
            double gene1_fitness=gene1.calc_fitness(),gene2_fitness=gene2.calc_fitness();
            double flip_to_gene2= gene2_fitness/(gene1_fitness + gene2_fitness);
            for(uint32_t i=0;i<gene1.n;i++){
                if(get_probability()<flip_to_gene2){
                    child.bits[i]=gene2.bits[i];
                }
            }
            return child.bits;
        };
        ~RandomBreeder()=default;
    };




}

#endif //FYP_BREEDER_H
