//
// Created by risha on 12-04-2023.
//

#include "Greedy.h"
std::vector<std::vector<bool>> Greedy(const Input &input) {
  int nCaches = input.cacheServer, nVideos = input.videos,
      nRequests = input.requests;
  std::vector<std::vector<bool>> bits(nCaches + 1,
                                      std::vector<bool>(nVideos, false));
  auto vecRequests = input.requestsDescription;
  std::sort(vecRequests.begin(), vecRequests.end(),
            [](const std::vector<int> &v1, const std::vector<int> &v2) {
              return v1[2] < v2[2];
            });
  std::reverse(vecRequests.begin(), vecRequests.end());
  vector<int> spaceUsed(nCaches + 1, 0);
  for (auto req : vecRequests) {
    int endPoint = req[1], video = req[0], count = req[2];
    vector<pair<int, int>> tempVec;
    for (int i = 1; i <= nCaches; i++) {
      if (spaceUsed[i] + input.videoSizes[video] <= input.cacheServerCapacity) {
        tempVec.push_back({input.latency[endPoint][i], i});
      }
    }
    sort(tempVec.begin(), tempVec.end());
    if (tempVec.empty())
      continue;
    int selectedInd = tempVec[0].second;
    if (bits[selectedInd][video])
      continue;
    spaceUsed[selectedInd] += input.videoSizes[video];
    bits[selectedInd][video] = true;
  }
  return bits;
}
