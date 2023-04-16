#ifndef FYP_SA_STATE_H
#define FYP_SA_STATE_H
#include "../shared/Input.h"
class SAState {
public:
  const Input &input;
  double maxTotalLatency;
  std::vector<vector<bool>> videoServed;
  SAState(const Input &input, std::vector<vector<bool>> &videoServed);
  SAState(const Input &input, std::vector<vector<bool>> &videoServed,
          double maxTotalLatency);
  SAState(const SAState &otherState);
  void operator=(const SAState &otherState);
  bool isValid() const;
  int score() const;
  double getAvgLatencyContri() const;
  pair<double, double> cacheServerUtilisation() const;
  SAState getNeighbouringState() const;
};

#endif
