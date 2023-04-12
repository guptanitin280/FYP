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
  void operator=(const SAState &operState);
  bool isValid() const;
  double getAvgLatencyContri() const;
  pair<double, double> cacheServerUtilisation() const;
};

#endif
