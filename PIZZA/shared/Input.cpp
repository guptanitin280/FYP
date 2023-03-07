//
// Created by Asus-2021 on 2/14/2023.
//

#include "Input.h"

Input::Input() {

}

Input::Input(string _filePath) {
    ifstream file;
    file.open("../"+_filePath);
    file >> numberOfClients;
    for (int i = 0; i < numberOfClients; i++) {
        int num;
        vector<string> liked, disliked;
        file >> num;
        for (int j = 0; j < num; j++) {
            string feature;
            file >> feature;
            liked.push_back(feature);
        }
        file >> num;
        for (int j = 0; j < num; j++) {
            string feature;
            file >> feature;
            disliked.push_back(feature);
        }
        featureLiked.push_back(liked);
        featureDisLiked.push_back(disliked);
    }
}
