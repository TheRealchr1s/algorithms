#ifndef NETWORK_ANALYSIS_H
#define NETWORK_ANALYSIS_H

#include <string>
#include <unordered_set>
#include <vector>

// Thresholds for determining anomalies
const double PACKET_LOSS_THRESHOLD = 5.0; // 5% packet loss
const double LATENCY_THRESHOLD = 100.0;   // 100 ms latency

// Structure for edge metrics
struct EdgeMetric {
  std::string node1;
  std::string node2;
  double packetLoss;
  double latency;
};

// Function to find culprit nodes using a greedy hitting set algorithm
std::unordered_set<std::string>
findCulpritNodes(const std::vector<EdgeMetric> &edgeMetrics);

#endif // NETWORK_ANALYSIS_H
