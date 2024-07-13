#include <iostream>
#include <vector>
#include <cstdlib>   // for rand() and srand()
#include <ctime>     // for time()

bool isValid(int row, int col, const std::vector<std::vector<int>>& matrix, const std::vector<std::vector<bool>>& visited) {
    return 0 <= row && row < matrix.size() &&
           0 <= col && col < matrix[0].size() &&
           matrix[row][col] == 1 &&
           !visited[row][col];
}

void dfs(int row, int col, const std::vector<std::vector<int>>& matrix, std::vector<std::vector<bool>>& visited, std::vector<std::pair<int, int>>& currentBlock) {
    visited[row][col] = true; // mark the cell as visited
    currentBlock.push_back(std::make_pair(row, col)); // add the cell to the current block

    std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // up, down, left, right directions

    // DFS all the adjacent cells in the current block (connected component)
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
    std::vector<std::vector<bool>> visited(matrix.size(), std::vector<bool>(matrix[0].size(), false)); // visited cells
    std::vector<std::vector<std::pair<int, int>>> blocks;

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
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
    // Seed the random number generator with the current time
    std::srand(std::time(0));

    // Generate a random binary matrix
    std::vector<std::vector<int>> matrix(10, std::vector<int>(70));
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 70; ++j) {
            matrix[i][j] = std::rand() % 2;  // 0 or 1
        }
    }

    std::cout << "Original matrix:" << std::endl;
    for (const auto& row : matrix) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n\n\n";
    std::cout << "Connected component matrix:" << std::endl;

    auto result = findAdjacentBlocks(matrix);
    printColoredMatrix(matrix, result);

    return 0;
}
