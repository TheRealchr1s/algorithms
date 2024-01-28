import heapq

def a_star(graph, start, goal, heuristic):
    # Priority queue to store (f_score, node) tuples
    open_set = [(0, start)]
    # Dictionary to store g_scores for each node
    g_scores = {node: float('inf') for node in graph}
    g_scores[start] = 0
    # Dictionary to store parents for each node
    parents = {start: None}

    while open_set:
        _, current = heapq.heappop(open_set)

        if current == goal:
            path = reconstruct_path(parents, current)
            return path

        for neighbor, cost in graph[current]:
            tentative_g_score = g_scores[current] + cost

            if tentative_g_score < g_scores[neighbor]:
                g_scores[neighbor] = tentative_g_score
                f_score = tentative_g_score + heuristic(neighbor, goal)
                heapq.heappush(open_set, (f_score, neighbor))
                parents[neighbor] = current

    return None  # No path found

def reconstruct_path(parents, goal):
    path = []
    current = goal
    while current is not None:
        path.insert(0, current)
        current = parents[current]
    return path

# Example usage
graph = {
    'A': [('B', 1), ('C', 4)],
    'B': [('A', 1), ('C', 2), ('D', 5)],
    'C': [('A', 4), ('B', 2), ('D', 1)],
    'D': [('B', 5), ('C', 1)]
}

start_node = 'A'
goal_node = 'D'

# A simple heuristic function (Euclidean distance in this case)
def heuristic(node, goal):
    coordinates = {'A': (0, 0), 'B': (1, 2), 'C': (3, 1), 'D': (4, 3)}
    x1, y1 = coordinates[node]
    x2, y2 = coordinates[goal]
    return ((x2 - x1) ** 2 + (y2 - y1) ** 2) ** 0.5

result = a_star(graph, start_node, goal_node, heuristic)
print(result)
