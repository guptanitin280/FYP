//
// Created by risha on 07-03-2023.
//

#include "SumOfDegrees.h"


uint32_t sumOfDegrees(genetic::Genome &gene){
    uint32_t ans=0;
    for(int i=0;i<gene.n;i++){
        if(gene.bits[i]){
            ans+=((gene.g.G[i])).size();
        }
    }
    return ans;
}