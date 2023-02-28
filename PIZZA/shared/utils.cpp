//
// Created by risha on 14-02-2023.
//

#include "utils.h"

uint32_t rand(uint32_t x,uint32_t y){
return std::uniform_int_distribution<uint32_t>(x,y)(rng);
}

double get_probability(){
    return std::uniform_real_distribution<>(0.0, 1.0)(rng);
}



std::vector<std::string> intersection(std::vector<std::string> v1,
                                      std::vector<std::string> v2){
    std::vector<std::string> v3;
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    std::set_intersection(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3));
    return v3;
}


size_t custom_hash::operator()(std::vector<bool> x) const {
    static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
    uint64_t v=(x).size();
    for(int i=0;i<(x).size();i++){
        v^=(splitmix64(i+FIXED_RANDOM)>>(i%4));
    }
    return v;
}


