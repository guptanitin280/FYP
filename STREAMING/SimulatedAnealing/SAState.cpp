#include "SAState.h"

SAState::SAState(const Input &input, std::vector<vector<bool>> &videoServed)
    : input(input), videoServed(videoServed) {
  double totalLatency = 0;
  for (auto request : this->input.requestsDescription) {
    int video_id = request[0], endpoint_id = request[1],
        numRequests = request[2];
    totalLatency += (this->input.latency[endpoint_id][0] * numRequests);
  }
  maxTotalLatency = totalLatency;
}

SAState::SAState(const Input &input, std::vector<vector<bool>> &videoServed,
                 double maxTotalLatency)
    : input(input), videoServed(videoServed), maxTotalLatency(maxTotalLatency) {
}
void SAState::operator=(const SAState &otherState) {
  this->videoServed = otherState.videoServed;
}

bool SAState::isValid() const {
  for (int cacheServer_id = 1; cacheServer_id <= this->input.cacheServer;
       cacheServer_id++) {
    int filled_cap = 0;
    for (int video_id = 0; video_id < this->input.videos; video_id++) {
      if (this->videoServed[cacheServer_id][video_id]) {
        filled_cap += this->input.videoSizes[video_id];
      }
    }
    if (filled_cap > this->input.cacheServerCapacity)
      return false;
  }
  return true;
}

double SAState::getAvgLatencyContri() const {
  double totalLatency = 0;
  for (auto request : this->input.requestsDescription) {
    int video_id = request[0], endpoint_id = request[1],
        numRequests = request[2];
    int min_latency = this->input.latency[endpoint_id][0];
    for (int cacheServer_id = 1; cacheServer_id <= this->input.cacheServer;
         cacheServer_id++) {
      if (this->input.latency[endpoint_id][cacheServer_id] != -1 and
          this->videoServed[cacheServer_id][video_id]) {
        min_latency =
            min(min_latency, this->input.latency[endpoint_id][cacheServer_id]);
      }
    }
    totalLatency += (min_latency * numRequests);
  }
  return 100 * totalLatency / this->maxTotalLatency;
}

pair<double, double> SAState::cacheServerUtilisation() const {
  double filled_cap_perc = 0, excess_cap_perc = 0;
  for (int cacheServer_id = 1; cacheServer_id <= this->input.cacheServer;
       cacheServer_id++) {
    int filled_cap = 0;
    for (int video_id = 0; video_id < this->input.videos; video_id++) {
      if (this->videoServed[cacheServer_id][video_id]) {
        filled_cap += this->input.videoSizes[video_id];
      }
    }
    filled_cap_perc +=
        min((double)100,
            (double)filled_cap / 100 * (double)this->input.cacheServerCapacity);
    excess_cap_perc +=
        max((double)0,
            100 * (double)(filled_cap - this->input.cacheServerCapacity) /
                (double)this->input.cacheServerCapacity);
  }
  return {filled_cap_perc / this->input.cacheServer,
          excess_cap_perc / this->input.cacheServer};
}
