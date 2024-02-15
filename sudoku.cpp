#include <iostream>
#include <vector>

const int SIZE = 9;
const int EMPTY = 0;

// Function to print the Sudoku grid
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << grid[i][j] << " ";
            if ((j + 1) % 3 == 0 && j < SIZE - 1) {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;
        if ((i + 1) % 3 == 0 && i < SIZE - 1) {
            std::cout << "------+-------+------" << std::endl;
        }
    }
}

// Function to find an empty cell in the Sudoku grid
bool findEmptyCell(const std::vector<std::vector<int>>& grid, int& row, int& col) {
    for (row = 0; row < SIZE; ++row) {
        for (col = 0; col < SIZE; ++col) {
            if (grid[row][col] == EMPTY) {
                return true;
            }
        }
    }
    return false;
}

// Function to check if a value can be placed in a specific cell
bool isSafe(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
    // Check if the number already exists in the row or column
    for (int i = 0; i < SIZE; ++i) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Check if the number already exists in the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(std::vector<std::vector<int>>& grid) {
    int row, col;
    if (!findEmptyCell(grid, row, col)) {
        return true; // Puzzle solved
    }

    for (int num = 1; num <= 9; ++num) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true;
            }
            grid[row][col] = EMPTY; // Backtrack
        }
    }

    return false; // No solution found
}

int main() {
    std::vector<std::vector<int>> sudokuGrid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    std::cout << "Sudoku Puzzle:" << std::endl;
    printGrid(sudokuGrid);
    std::cout << std::endl;

    if (solveSudoku(sudokuGrid)) {
        std::cout << "Solution:" << std::endl;
        printGrid(sudokuGrid);
    } else {
        std::cout << "No solution exists." << std::endl;
    }

    return 0;
}
