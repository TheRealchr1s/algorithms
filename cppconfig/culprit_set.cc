#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
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
findCulpritNodes(const std::vector<EdgeMetric> &edgeMetrics) {
  // Step 1: Identify faulty edges
  std::vector<std::pair<std::string, std::string>>
      faultyEdges; // List of faulty edges (node1, node2)
  for (const auto &metric : edgeMetrics) {
    if (metric.packetLoss > PACKET_LOSS_THRESHOLD ||
        metric.latency > LATENCY_THRESHOLD) {
      faultyEdges.emplace_back(metric.node1, metric.node2);
    }
  }

  // Step 2: Construct adjacency list for hitting set
  std::unordered_map<std::string, std::unordered_set<int>>
      nodeToEdges; // Map nodes to the faulty edges they touch
  for (int i = 0; i < static_cast<int>(faultyEdges.size()); ++i) {
    nodeToEdges[faultyEdges[i].first].insert(i);
    nodeToEdges[faultyEdges[i].second].insert(i);
  }

  // Step 3: Greedy hitting set algorithm
  std::unordered_set<std::string> suspects; // Final set of suspect nodes
  std::unordered_set<int> coveredEdges; // Set of edges that are already covered

  while (coveredEdges.size() < faultyEdges.size()) {
    // Find the node that covers the most uncovered edges
    std::string bestNode;
    int maxCoverage = 0;

    for (const auto &[node, edges] : nodeToEdges) {
      int coverage = 0;
      for (int edge : edges) {
        if (coveredEdges.find(edge) == coveredEdges.end()) {
          coverage++;
        }
      }

      if (coverage > maxCoverage) {
        maxCoverage = coverage;
        bestNode = node;
      }
    }

    // Add the best node to suspects and mark its edges as covered
    suspects.insert(bestNode);
    for (int edge : nodeToEdges[bestNode]) {
      coveredEdges.insert(edge);
    }

    // Remove the selected node from the map
    nodeToEdges.erase(bestNode);
  }

  return suspects;
}

int main() {
  // Example edge metrics
  std::vector<EdgeMetric> edgeMetrics = {
      {"A", "B", 2.0, 50.0},  // Normal
      {"B", "C", 6.0, 80.0},  // Packet loss exceeds threshold
      {"C", "D", 3.0, 120.0}, // Latency exceeds threshold
      {"A", "D", 1.0, 30.0},  // Normal
      {"B", "D", 0.5, 90.0}   // Normal
  };

  // Find and print suspect nodes
  std::unordered_set<std::string> suspects = findCulpritNodes(edgeMetrics);

  std::cout << "Suspect nodes are:" << std::endl;
  for (const auto &node : suspects) {
    std::cout << node << std::endl;
  }

  return 0;
}
