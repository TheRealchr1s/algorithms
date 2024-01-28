import random

# Impl of Union-Find data structure
class UnionFind:
    def __init__(self, n):
        # Initialize parent array and rank array for each element
        self.parent = [i for i in range(n)]
        self.rank = [0] * n

    # Recursive function to find the root of the set to which x belongs
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # Path compression for optimization
        return self.parent[x]

    # Union operation to merge sets of x and y
    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)

        if root_x != root_y:
            # Union by rank for optimization
            if self.rank[root_x] < self.rank[root_y]:
                self.parent[root_x] = root_y
            elif self.rank[root_x] > self.rank[root_y]:
                self.parent[root_y] = root_x
            else:
                self.parent[root_x] = root_y
                self.rank[root_y] += 1


# Function to find connected blocks using Union-Find
def find_adjacent_blocks_union_find(matrix):
    rows, cols = len(matrix), len(matrix[0])
    uf = UnionFind(rows * cols)

    # Iterate through the matrix to perform union operation for adjacent filled blocks
    for i in range(rows):
        for j in range(cols):
            if matrix[i][j] == 1:
                current_index = i * cols + j

                # Check right and down neighbors
                if j + 1 < cols and matrix[i][j + 1] == 1:
                    uf.union(current_index, i * cols + j + 1)
                if i + 1 < rows and matrix[i + 1][j] == 1:
                    uf.union(current_index, (i + 1) * cols + j)

    # Create a dictionary to store connected blocks
    blocks = {}
    for i in range(rows):
        for j in range(cols):
            if matrix[i][j] == 1:
                current_index = i * cols + j
                root = uf.find(current_index)
                if root not in blocks:
                    blocks[root] = []
                blocks[root].append((i, j))

    return list(blocks.values())


# Function to print a colored matrix with labeled connected blocks
def print_colored_matrix(matrix, blocks):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            block_number = -1
            for idx, block in enumerate(blocks):
                if (i, j) in block:
                    block_number = idx
                    break

            if block_number != -1:
                # Use ANSI escape codes for text color
                color_code = 31 + (block_number % 6)  # 31 to 36 are ANSI color codes for red to cyan
                print("\033[1;{}m{}\033[0m".format(color_code, '■' if matrix[i][j] == 1 else '□'), end=" ")
            else:
                print('□' if matrix[i][j] == 0 else '■', end=" ")
        print()

# matrix = [
#     [0, 0, 0, 1, 0, 0, 1, 1],
#     [0, 0, 0, 1, 1, 0, 1, 1],
#     [0, 0, 0, 1, 0, 0, 1, 1],
#     [0, 0, 0, 1, 0, 0, 1, 1],
#     [0, 0, 0, 1, 0, 0, 1, 1],
#     [1, 0, 1, 1, 0, 0, 1, 1]
# ]


matrix = [[0 if random.random() < 0.8 else 1 for _ in range(100)] for _ in range(10)]



# Find and print connected blocks using Union-Find
result_union_find = find_adjacent_blocks_union_find(matrix)
print_colored_matrix(matrix, result_union_find)
