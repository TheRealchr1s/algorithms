#include <iostream>
#include <vector>

bool isValid(int row, int col, const std::vector<std::vector<int>>& matrix, const std::vector<std::vector<bool>>& visited) {
    // Check if the given position is within the matrix boundaries,
    // contains a 1, and has not been visited yet.
    return 0 <= row && row < matrix.size() &&
           0 <= col && col < matrix[0].size() &&
           matrix[row][col] == 1 &&
           !visited[row][col];
}

void dfs(int row, int col, const std::vector<std::vector<int>>& matrix, std::vector<std::vector<bool>>& visited, std::vector<std::pair<int, int>>& currentBlock) {
    // Mark the current position as visited and add it to the current block.
    visited[row][col] = true;
    currentBlock.push_back(std::make_pair(row, col));

    // Define the possible directions: up, down, left, right
    std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    // Explore each direction recursively.
    for (const auto& direction : directions) {
        int dr = direction.first;
        int dc = direction.second;
        int newRow = row + dr;
        int newCol = col + dc;
        if (isValid(newRow, newCol, matrix, visited)) {
            dfs(newRow, newCol, matrix, visited, currentBlock);
        }
    }
}

std::vector<std::vector<std::pair<int, int>>> findAdjacentBlocks(const std::vector<std::vector<int>>& matrix) {
    // Initialize a matrix to track visited positions and a vector to store blocks.
    std::vector<std::vector<bool>> visited(matrix.size(), std::vector<bool>(matrix[0].size(), false));
    std::vector<std::vector<std::pair<int, int>>> blocks;

    // Iterate through each cell in the matrix.
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            // If the cell contains 1 and has not been visited, start a new block.
            if (matrix[i][j] == 1 && !visited[i][j]) {
                std::vector<std::pair<int, int>> currentBlock;
                dfs(i, j, matrix, visited, currentBlock);
                blocks.push_back(currentBlock);
            }
        }
    }

    return blocks;
}

void printColoredMatrix(const std::vector<std::vector<int>>& matrix, const std::vector<std::vector<std::pair<int, int>>>& blocks) {
    // Print the matrix with colored blocks based on the block number.
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            int blockNumber = -1;
            for (int idx = 0; idx < blocks.size(); ++idx) {
                const auto& block = blocks[idx];
                for (const auto& cell : block) {
                    if (cell.first == i && cell.second == j) {
                        blockNumber = idx;
                        break;
                    }
                }
                if (blockNumber != -1) {
                    // Use ANSI escape codes for text color (31 to 36 for red to cyan).
                    int colorCode = 31 + (blockNumber % 6);
                    std::cout << "\033[1;" << colorCode << "m" << matrix[i][j] << "\033[0m ";
                    break;
                }
            }
            if (blockNumber == -1) {
                std::cout << matrix[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<int>> matrix = {
        {0, 0, 0, 1, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 1, 1},
        {0, 0, 0, 1, 0, 0, 1, 1},
        {0, 0, 0, 1, 0, 0, 1, 1},
        {0, 0, 0, 1, 0, 0, 1, 1},
        {1, 0, 1, 1, 0, 0, 1, 1}
    };

    // Find and print adjacent blocks with colored representation.
    auto result = findAdjacentBlocks(matrix);
    printColoredMatrix(matrix, result);

    return 0;
}
