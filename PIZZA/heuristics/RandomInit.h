#ifndef FYP_RANDOMINIT_H
#define FYP_RANDOMINIT_H

#include "../shared/Graph.h"
#include "../shared/utils.h"
#include <bits/stdc++.h>

// take the node with minimum degree and randomly from the nodes which
vector<bool> RandomInit(Graph &input);
vector<bool> RandomInitConst(const Graph &input);

#endif
