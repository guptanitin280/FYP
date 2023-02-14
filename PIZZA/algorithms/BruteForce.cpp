//
// Created by Asus-2021 on 2/10/2023.
//

#include "BruteForce.h"

BruteForce::BruteForce(Input _input) : input(_input) {

}

bool intersection(vector<string>&a,vector<string>&b) {
    unordered_set<string> temp;
    for (auto &c: a) temp.insert(c);
    for (auto &c: b) {
        if (temp.count(c)) {
            return true;
        }
    }
    return false;
}

Output BruteForce::solve() {

    if (input.numberOfClients > MAX_SIZE) {
        return output;
    }
    bool can[input.numberOfClients][input.numberOfClients];
    memset(can, false, sizeof can);
    for (int i = 0; i < input.numberOfClients; i++) {
        for (int j = i + 1; j < input.numberOfClients; j++) {
            can[i][j] = !(intersection(input.featureLiked[i], input.featureDisLiked[j]) ||
                          intersection(input.featureDisLiked[i], input.featureLiked[j]));
        }
    }
    int ans = 1;
    uint64_t mask = 1;
    for (uint64_t i = 0; i < (1ull << input.numberOfClients); i++) {
        bool flag = false;
        for (uint64_t j = 0; j < input.numberOfClients; j++) {
            for (uint64_t k = j + 1; k < input.numberOfClients; k++) {
                if ((i & (1ull << j)) && (i & (1ull << k)) && !can[j][k]) {
                    flag = true;
                }
            }
        }
        if (!flag) {
            int cnt = __builtin_popcountll(i);
            if (ans < cnt) {
                ans = cnt;
                mask = i;
            }
        }
    }

    unordered_set<string> included;
    for (uint64_t k = 0; k < input.numberOfClients; k++) {
        if (mask & (1ull << k)) {
            for (auto &c: input.featureLiked[k]) {
                included.insert(c);
            }
        }
    }
    for (auto &c: included) {
        output.features.push_back(c);
    }
    return output;




//    uint32_t numberOfFeatures;
//    unordered_map<string,int> features;
//    for (auto &c: input.featureDisLiked) {
//        for (auto &d: c) {
//            features[d] = 1;
//        }
//    }
//    for (auto &c: input.featureLiked) {
//        for (auto &d: c) {
//            features[d] = 1;
//        }
//    }
//    numberOfFeatures = features.size();
//    if (max(numberOfFeatures, input.numberOfClients) > MAX_SIZE) {
//        return output;
//    }
//    if (numberOfFeatures < input.numberOfClients) {
//        vector<string>allFeatures;
//        int index=0;
//        for(auto &c:features) {
//            c.second = index++;
//            allFeatures.push_back(c.first);
//        }
//        for(int i=0;i<(1ull<<numberOfFeatures);i++){
//            int cnt=0;
//
//        }
//
//    } else {
//
//    }
    return output;
}