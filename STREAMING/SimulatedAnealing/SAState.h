#ifndef FYP_SA_STATE_H
#define FYP_SA_STATE_H
#include "../shared/Input.h"
class SAState {
public:
  const Input &input;
  double maxTotalLatency;
  bool enableHeuristic;
  std::vector<vector<bool>> videoServed;
  SAState(const Input &input, std::vector<vector<bool>> &videoServed,
          bool enableHeuristic);
  SAState(const Input &input, std::vector<vector<bool>> &videoServed,
          double maxTotalLatency, bool enableHeuristic);
  SAState(const SAState &otherState);
  void operator=(const SAState &otherState);
  bool isValid() const;
  int score() const;
  double getAvgLatencyContri() const;
  pair<double, double> cacheServerUtilisation() const;
  SAState getNeighbouringState() const;
};

#endif
