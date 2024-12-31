#include <queue>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"

// Thresholds for determining anomalies
const double kPacketLossThreshold = 5.0; // 5% packet loss
const double kLatencyThreshold = 100.0;  // 100 ms latency

// Structure for edge metrics
struct EdgeMetric {
  std::string node1;
  std::string node2;
  double packet_loss;
  double latency;
  bool has_packet_loss; // Indicates if packet loss data is available
  bool has_latency;     // Indicates if latency data is available
};

// Function to find culprit nodes using a greedy hitting set algorithm
absl::flat_hash_set<std::string>
FindCulpritNodes(const std::vector<EdgeMetric> &edge_metrics) {
  // Step 1: Identify faulty edges with available metrics
  std::vector<std::pair<std::string, std::string>>
      faulty_edges; // List of faulty edges (node1, node2)

  for (const auto &metric : edge_metrics) {
    bool is_faulty = false;
    if (metric.has_packet_loss && metric.packet_loss > kPacketLossThreshold) {
      is_faulty = true;
    }
    if (metric.has_latency && metric.latency > kLatencyThreshold) {
      is_faulty = true;
    }
    if (is_faulty) {
      faulty_edges.emplace_back(metric.node1, metric.node2);
    }
  }

  // Step 2: Construct adjacency list for hitting set
  absl::flat_hash_map<std::string, absl::flat_hash_set<int>>
      node_to_edges; // Map nodes to the faulty edges they touch
  for (int i = 0; i < static_cast<int>(faulty_edges.size()); ++i) {
    node_to_edges[faulty_edges[i].first].insert(i);
    node_to_edges[faulty_edges[i].second].insert(i);
  }

  // Step 3: Greedy hitting set algorithm with priority queue
  absl::flat_hash_set<std::string> suspects; // Final set of suspect nodes
  absl::flat_hash_set<int>
      covered_edges; // Set of edges that are already covered

  // Priority queue to select the node with maximum coverage
  auto cmp = [&](const std::string &a, const std::string &b) -> bool {
    return node_to_edges[a].size() < node_to_edges[b].size();
  };

  std::priority_queue<std::string, std::vector<std::string>, decltype(cmp)> pq(
      cmp);

  for (const auto &pair : node_to_edges) {
    pq.push(pair.first);
  }

  while (covered_edges.size() < faulty_edges.size() && !pq.empty()) {
    std::string best_node = pq.top();
    pq.pop();

    // Recalculate coverage to handle dynamic changes
    int coverage = 0;
    for (int edge : node_to_edges[best_node]) {
      if (covered_edges.find(edge) == covered_edges.end()) {
        coverage++;
      }
    }

    if (coverage == 0) {
      continue;
    }

    // Add the best node to suspects and mark its edges as covered
    suspects.insert(best_node);
    for (int edge : node_to_edges[best_node]) {
      covered_edges.insert(edge);
    }
  }

  return suspects;
}

int main() {
  // Example edge metrics with missing data
  std::vector<EdgeMetric> edge_metrics = {
      {"A", "B", 2.0, 50.0, true, true},  // Normal
      {"B", "C", 6.0, 80.0, true, true},  // Packet loss exceeds threshold
      {"C", "D", 3.0, 120.0, true, true}, // Latency exceeds threshold
      {"A", "D", 1.0, 30.0, true, true},  // Normal
      {"B", "D", 0.5, 90.0, true, true},  // Normal
      {"D", "E", 0.0, 0.0, false, false}  // Missing metrics
  };

  // Find and print suspect nodes
  absl::flat_hash_set<std::string> suspects = FindCulpritNodes(edge_metrics);

  std::cout << "Suspect nodes are:" << std::endl;
  for (const auto &node : suspects) {
    std::cout << node << std::endl;
  }

  return 0;
}
