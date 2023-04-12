//
// Created by risha on 12-04-2023.
//

#include "CacheUtilisation.h"

uint32_t Cacheutilisation(genetic::Genome &gene){

    auto input= gene.g;
    auto output=gene.bits;
    double filled_cap = 0, excess_cap_perc = 0;
    for (int cacheServer_id = 1; cacheServer_id <= input.cacheServer;
         cacheServer_id++) {
        int filled_cap_cur = 0;
        for (int video_id = 0; video_id < input.videos; video_id++) {
            if (output[cacheServer_id][video_id]) {
                filled_cap_cur += input.videoSizes[video_id];
            }
        }
        filled_cap += filled_cap_cur;
    }
    return filled_cap;


}