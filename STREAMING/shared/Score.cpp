//
// Created by risha on 12-04-2023.
//

#include "Score.h"

int Score::calculate(const Input &input, const Output &output) {
    int val = 0;
    for (int i = 0; i < input.numberOfClients; i++) {
        bool acceptable = true;
        for (string s : input.featureLiked[i]) {
            if (!output.features.count(s)) {
                acceptable = false;
                break;
            }
        }
        if (!acceptable)
            continue;
        for (string s : input.featureDisLiked[i]) {
            if (output.features.count(s)) {
                acceptable = false;
                break;
            }
        }
        if (acceptable)
            val++;
    }
    return val;
}