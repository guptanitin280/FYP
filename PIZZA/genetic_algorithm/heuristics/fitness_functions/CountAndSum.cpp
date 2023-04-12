    //
// Created by risha on 07-03-2023.
//

#include "CountAndSum.h"


uint32_t CountAndSum(genetic::Genome &gene){
    uint32_t numOfOnes= count(gene.bits.begin(),gene.bits.end(), true);
    uint32_t ans=numOfOnes*(gene.n);
    for(int i=0;i<gene.n;i++){
        if(gene.bits[i]){
            ans-=((gene.g.G[i])).size();
        }
    }
    return ans;
}