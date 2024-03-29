//
// Created by risha on 27-02-2023.
//

#ifndef STREAMING_EVOLVER_H
#define STREAMING_EVOLVER_H
#include<bits/stdc++.h>
#include "Genome.h"
#include "../../shared/utils.h"

namespace genetic{

    class Evolver{
    public:
        virtual ~Evolver()=default;
        virtual void evolve(std::vector<std::vector<bool>>& gene)=0;
        virtual void update_rate(uint32_t iter)=0;
    };


    class SimpleEvolver:public virtual Evolver{
    public:
        double changes_per_genome;

        SimpleEvolver(double _rate):changes_per_genome(_rate){};
        virtual void evolve(std::vector<std::vector<bool>>& gene) override{
            //!!IMPLEMENT
            double flip_probability= (changes_per_genome)/(gene[0]).size();
            for(uint32_t i=0;i<gene.size();i++){
                for(uint32_t j=0;j<gene[0].size();j++){
                    if(get_probability()< flip_probability)gene[i][j]=(!gene[i][j]);
                }
            }
        };

        void update_rate(uint32_t iter) override{
        }
        ~SimpleEvolver()=default;
    };

}

#endif //STREAMING_EVOLVER_H
