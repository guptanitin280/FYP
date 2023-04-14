//
// Created by Asus-2021 on 4/12/2023.
//

#include "Input.h"

Input::Input(){

}

Input::Input(std::string _filePath) {
    ifstream file;
    file.open("../" + _filePath);

    file >> videos;
    file >> endpoints;
    file >> requests;
    file >> cacheServer;
    file >> cacheServerCapacity;
    videoSizes.resize(videos);
    for (int i = 0; i < videos; i++) {
        file >> videoSizes[i];
    }

    latency.resize(endpoints);
    for (int i = 0; i < endpoints; i++) {
        latency[i].resize(cacheServer + 1, -1);
        file >> latency[i][0];
        int k;
        file >> k;

        for (int j = 1; j <= k; j++) {
            int whichOne;
            file >> whichOne;
            file >> latency[i][whichOne + 1];
        }
    }
    requestsDescription.resize(requests);


    for (int i = 0; i < requests; i++) {
        int video;
        int endpoint;
        int numOfRequests;
        file >> video >> endpoint >> numOfRequests;
        requestsDescription[i] = {video, endpoint, numOfRequests};
    }
    file.close();
}