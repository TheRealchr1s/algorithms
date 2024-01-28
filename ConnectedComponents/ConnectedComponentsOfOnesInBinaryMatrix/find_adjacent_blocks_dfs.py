def is_valid(row, col, matrix, visited):
    # Check if the given position is within the matrix boundaries,
    # contains a 1, and has not been visited yet.
    return 0 <= row < len(matrix) and 0 <= col < len(matrix[0]) and matrix[row][col] == 1 and not visited[row][col]

def dfs(row, col, matrix, visited, current_block):
    # Mark the current position as visited and add it to the current block.
    visited[row][col] = True
    current_block.append((row, col))

    # Define the possible directions: up, down, left, right
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    # Explore each direction recursively.
    for dr, dc in directions:
        new_row, new_col = row + dr, col + dc
        if is_valid(new_row, new_col, matrix, visited):
            dfs(new_row, new_col, matrix, visited, current_block)

def find_adjacent_blocks(matrix):
    # Initialize a matrix to track visited positions and a list to store blocks.
    visited = [[False for _ in range(len(matrix[0]))] for _ in range(len(matrix))]
    blocks = []

    # Iterate through each cell in the matrix.
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            # If the cell contains 1 and has not been visited, start a new block.
            if matrix[i][j] == 1 and not visited[i][j]:
                current_block = []
                dfs(i, j, matrix, visited, current_block)
                blocks.append(current_block)

    return blocks

def print_colored_matrix(matrix, blocks):
    # Print the matrix with colored blocks based on the block number.
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            block_number = -1
            for idx, block in enumerate(blocks):
                if (i, j) in block:
                    block_number = idx
                    break

            if block_number != -1:
                # Use ANSI escape codes for text color (31 to 36 for red to cyan).
                color_code = 31 + (block_number % 6)
                print("\033[1;{}m{}\033[0m".format(color_code, matrix[i][j]), end=" ")
            else:
                print(matrix[i][j], end=" ")
        print()

# Example usage
matrix = [
    [0, 0, 0, 1, 0, 0, 1, 1],
    [0, 0, 0, 1, 1, 0, 1, 1],
    [0, 0, 0, 1, 0, 0, 1, 1],
    [0, 0, 0, 1, 0, 0, 1, 1],
    [0, 0, 0, 1, 0, 0, 1, 1],
    [1, 0, 1, 1, 0, 0, 1, 1]
]

# Find and print adjacent blocks with colored representation.
result = find_adjacent_blocks(matrix)
print_colored_matrix(matrix, result)
