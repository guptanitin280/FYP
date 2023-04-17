//
// Created by risha on 17-04-2023.
//

#include "VideosStored.h"

uint32_t VideosStored(genetic::Genome &gene){
    auto input= gene.g;
    auto output=gene.bits;
    set<int> videosCached;

    for(int cache=1;cache<=input.cacheServer;cache++){
        for(int vid=0;vid<input.videos;vid++){
            if(output[cache][vid])videosCached.insert(vid);
        }
    }

    return videosCached.size();
    }
