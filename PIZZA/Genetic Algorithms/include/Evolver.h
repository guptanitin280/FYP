//
// Created by risha on 27-02-2023.
//

#ifndef FYP_EVOLVER_H
#define FYP_EVOLVER_H
#include<bits/stdc++.h>
#include "Genome.h"
#include "../../shared/utils.h"

namespace genetic{

    class Evolver{
    public:
        virtual ~Evolver();
        virtual void evolve(vector<bool>& gene)=0;
        virtual void update_rate(uint32_t iter)=0;
    };

    class SimpleEvolver:public virtual Evolver{
    public:
        double changes_per_genome;

        SimpleEvolver(double _rate):changes_per_genome(_rate){};
        virtual void evolve(vector<bool>& gene) override{
            double flip_probability= (changes_per_genome)/gene.size();
            for(uint32_t i=0;i<gene.size();i++){
                if(get_probability()< flip_probability)gene[i]=(!gene[i]);
            }
        };

        void update_rate(uint32_t iter) override{
        }
    };

}

#endif //FYP_EVOLVER_H
