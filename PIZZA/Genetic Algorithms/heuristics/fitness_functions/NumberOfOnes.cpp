//
// Created by risha on 27-02-2023.
//
#include <bits/stdc++.h>
#include "../../include/Genome.h"

uint32_t numberOfOnes(genetic::Genome &gene){
    uint32_t numOfOnes= count(gene.bits.begin(),gene.bits.end(), true);
    return numOfOnes;
}


