//
// Created by Asus-2021 on 4/12/2023.
//

#ifndef STREAMING_INPUT_H
#define STREAMING_INPUT_H
#include<bits/stdc++.h>
using namespace std;

class Input {
public:

    int videos;
    int endpoints;
    int requests;
    int cacheServer;
    int cacheServerCapacity;
    vector<int>videoSizes;
    vector<vector<int>>latency;
    vector<vector<int>>requestsDescription;


    Input();

    Input(std::string _filePath);
};


#endif //STREAMING_INPUT_H
