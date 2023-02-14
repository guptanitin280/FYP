//
// Created by risha on 14-02-2023.
//

#ifndef FYP_GREEDY_H
#define FYP_GREEDY_H

#include "../shared/Input.h"
#include "../shared/Output.h"
#include "../shared/utils.h"
#include "../shared/Graph.h"


class Greedy {
public:
    Input input;
    Output output;

    Greedy(Input _input);
    Output solve();
};

#endif //FYP_GREEDY_H
