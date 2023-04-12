#include "SAState.h"
#include "../shared/utils.h"
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

SAState::SAState(const SAState &otherState)
    : input(otherState.input), videoServed(otherState.videoServed),
      maxTotalLatency(otherState.maxTotalLatency) {}

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

SAState next_good_neighbour(const SAState &state, double perc) {
  const Input &input = state.input;
  int numChanges = (perc * input.videos * input.cacheServer);
  int maxPt = state.input.videos * input.cacheServer;
  SAState nextState(state);
  for (int i = 0; i < numChanges; i++) {
    int pt = rng() % maxPt;
    int video_id = pt % input.videos;
    int server_id = (pt % input.cacheServer) + 1;
    if (nextState.videoServed[server_id][video_id]) {
      nextState.videoServed[server_id][video_id] = false;
    }
  }
  for (int cacheServer_id = 1; cacheServer_id <= input.cacheServer;
       cacheServer_id++) {
    int filled_cap = 0;
    for (int video_id = 0; video_id < input.videos; video_id++) {
      if (nextState.videoServed[cacheServer_id][video_id]) {
        filled_cap += input.videoSizes[video_id];
      }
    }

    vector<int> videos;
    int rem_cap = input.cacheServerCapacity - filled_cap;
    for (int video_id = 0; video_id < input.videos; video_id++) {
      if (!nextState.videoServed[cacheServer_id][video_id] and
          input.videoSizes[video_id] < rem_cap) {
        videos.push_back(video_id);
      }
    }
    while (videos.size() > 0) {
      int idx = rng() % videos.size();
      int v_id = videos[idx];
      if (input.videoSizes[v_id] <= rem_cap and
          !nextState.videoServed[cacheServer_id][v_id]) {
        rem_cap -= input.videoSizes[v_id];
        nextState.videoServed[cacheServer_id][v_id] = true;
        swap(videos[idx], videos.back());
        videos.pop_back();
      } else
        break;
    }
  }
  return nextState;
}

SAState swap_random(const SAState &state) {
  const Input &input = state.input;
  SAState nextState(state);

  int maxPt = state.input.videos * input.cacheServer;
  int pt = rng() % maxPt;
  int video_id = pt % input.videos;
  int server_id = (pt % input.cacheServer) + 1;
  nextState.videoServed[server_id][video_id] =
      !nextState.videoServed[server_id][video_id];
  return nextState;
}

SAState SAState::getNeighbouringState() const {
  double prob = get_probability();
  if (prob < 0.33) {
    return next_good_neighbour(*this, prob * 2);
  }
  return swap_random(*this);
}
