//
// Created by Asus-2021 on 2/10/2023.
//
//
#ifndef FYP_BRUTEFORCE_H
#define FYP_BRUTEFORCE_H

#include "../shared/Input.h"
#include "../shared/Output.h"

const int MAX_SIZE = 25;

class BruteForce {
public:
    Input input;
    Output output;

    BruteForce(Input _input);
    Output solve();
};


#endif //FYP_BRUTEFORCE_H
