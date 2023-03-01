//
// Created by Asus-2021 on 2/14/2023.
//

#ifndef FYP_INPUT_H
#define FYP_INPUT_H
#include<bits/stdc++.h>
using namespace std;

class Input {
public:
    string filePath;
    uint32_t numberOfClients;
    vector<vector<string>>featureLiked;
    vector<vector<string>>featureDisLiked;

    Input(string _filePath);
    Input();
};


#endif //FYP_INPUT_H
