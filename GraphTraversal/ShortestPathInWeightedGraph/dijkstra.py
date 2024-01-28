import heapq
import random

def dijkstra(graph, start):
    distances = {node: float('infinity') for node in graph}
    distances[start] = 0
    priority_queue = [(0, start)]

    while priority_queue:
        current_distance, current_node = heapq.heappop(priority_queue)

        if current_distance > distances[current_node]:
            continue

        print(f"Visited node: {current_node}, Distance from start: {current_distance}")

        for neighbor, weight in graph[current_node].items():
            distance = current_distance + weight

            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(priority_queue, (distance, neighbor))

    return distances

def visualize_graph(graph):
    print("Graph Visualization:")
    for node, neighbors in graph.items():
        print(f"{node} -> {', '.join(neighbors)}")

def generate_complex_graph(num_nodes, num_edges):
    graph = {}
    nodes = [str(i) for i in range(num_nodes)]

    for node in nodes:
        graph[node] = {}

    for _ in range(num_edges):
        node1, node2 = random.sample(nodes, 2)
        weight = random.randint(1, 10)
        graph[node1][node2] = weight
        graph[node2][node1] = weight

    return graph

# Example usage:
num_nodes = 10
num_edges = 20
complex_graph = generate_complex_graph(num_nodes, num_edges)

# Visualize the generated complex graph
visualize_graph(complex_graph)

# Run Dijkstra's algorithm on the generated graph
print("\nRunning Dijkstra's algorithm on the complex graph...")
start_node = '0'
shortest_distances_complex = dijkstra(complex_graph, start_node)

# Print final shortest distances
print("\nFinal Shortest Distances:")
for node, distance in shortest_distances_complex.items():
    print(f"Node: {node}, Shortest Distance from {start_node}: {distance}")
