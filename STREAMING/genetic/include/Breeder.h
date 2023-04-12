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
        };
        ~RandomBreeder()=default;
    };




}

#endif //STREAMING_BREEDER_H
