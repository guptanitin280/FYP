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
    Graph input;
    vector<bool> output;

    explicit Greedy(Graph _input);
    vector<bool> get();
};

#endif //FYP_GREEDY_H
