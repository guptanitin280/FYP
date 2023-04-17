#ifndef FYP_SA_STATE_H
#define FYP_SA_STATE_H
#include "../shared/Graph.h"
class SAState {
public:
  const Graph &graph;
  bool enableHeuristic;
  vector<bool> clientsSatistied;
  SAState(const Graph &graph, const vector<bool> &clientsSatistied,
          bool enableHeuristic);
  SAState(const SAState &otherState);
  void operator=(const SAState &otherState);
  bool isValid() const;
  int score() const;
  int getNumClients() const;
  int getInvalidClientsPenalty() const;
  SAState getNeighbouringState() const;
};

#endif
