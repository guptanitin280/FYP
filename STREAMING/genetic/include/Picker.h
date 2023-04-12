//
// Created by risha on 12-04-2023.
//

#ifndef STREAMING_PICKER_H
#define STREAMING_PICKER_H
#include<bits/stdc++.h>
#include "Genome.h"
#include "../../shared/utils.h"

namespace genetic{

    class Picker{
    public:
        virtual ~Picker()=default;
        virtual uint32_t pick(vector<genetic::Genome>& generation)=0;
    };


    class RandomBestPicker:public virtual Picker{
    public:
        uint32_t sample_size;

        RandomBestPicker(uint32_t _n):sample_size(_n){};
        virtual uint32_t pick(vector<genetic::Genome>& generation) override{
            uint32_t max_fitness = 0;
            int best = -1;
            for (size_t i = 0; i < sample_size; ++i) {
                auto idx = static_cast<int>(rand(0,(int)generation.size() -1));
                auto fitness = generation[idx].calc_fitness();
                if (fitness > max_fitness) {
                    max_fitness = fitness;
                    best = idx;
                }
            }

            assert(best != -1);
            return best;
        };

        ~RandomBestPicker()=default;
    };




}

#endif //STREAMING_PICKER_H
