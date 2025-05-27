#pragma once

#include <vector>
#include <string>
#include <functional>
#include <utility>

//////////////////////////////////////////////////////

/**
 * @brief Generates all permutations of a given input string using backtracking.
 *
 * This function assumes that all characters in the input string are unique.
 * It generates every possible ordering (permutation) of the characters using
 * a recursive backtracking approach.
 *
 * @note
 * If the input contains duplicate characters, this implementation will produce
 * duplicate permutations. To avoid duplicates, you need to sort the input and
 * skip repeated characters accordingly.
 *
 * @param input A string whose characters will be permuted. Must not contain duplicates.
 * @return A vector containing all permutations of the input string.
 *
 * @example
 * @code
 * auto perms = permutations("abc");
 * // perms = {"abc", "acb", "bac", "bca", "cab", "cba"}
 * @endcode
 */
std::vector<std::string> permutations(const std::string& input)
{
    std::vector<std::string> solutions;           // Store the resulting permutations
    std::string solution;                         // Current partial permutation being built
    std::vector<bool> used(input.size(), false);  // Track which characters have been used

    // Recursive backtracking function to build permutations
    std::function<void()> backtracking = [&]() {
        // Base case: when the partial solution has the same length as the input,
        // we've formed a complete permutation
        if (solution.size() == input.size())
        {
            solutions.push_back(solution);  // Save the current permutation
            return;
        }

        // Try each unused character in the current position
        for (size_t i = 0; i < input.size(); ++i)
        {
            if (!used[i])
            {
                used[i] = true;                // Mark character as used
                solution.push_back(input[i]);  // Add it to the current permutation
                backtracking();                // Recurse
                solution.pop_back();           // Backtrack: remove last character
                used[i] = false;               // Unmark the character
            }
        }
    };

    backtracking();
    return solutions;
}

std::vector<std::string> permutationsWithBounding(const std::string& input)
{
    std::vector<std::string> solutions;           // Store the resulting permutations
    std::string solution;                         // Current partial permutation being built
    std::vector<bool> used(input.size(), false);  // Track which characters have been used

    // Recursive backtracking function to build permutations
    std::function<void()> backtracking = [&]() {
        // Base case: when the partial solution has the same length as the input,
        // we've formed a complete permutation
        if (solution.size() == input.size())
        {
            solutions.push_back(solution);  // Save the current permutation
            return;
        }

        // Try each unused character in the current position
        for (size_t i = 0; i < input.size(); ++i)
        {
            // Bounding
            if (!solution.empty())
            {
                char prev = solution.back();
                char curr = input[i];
                if (curr - prev == 1)  // only forbid increasing consecutive
                {
                    continue;
                }
            }

            if (!used[i])
            {
                used[i] = true;                // Mark character as used
                solution.push_back(input[i]);  // Add it to the current permutation
                backtracking();                // Recurse
                solution.pop_back();           // Backtrack: remove last character
                used[i] = false;               // Unmark the character
            }
        }
    };

    backtracking();
    return solutions;
}

//////////////////////////////////////////////////////

using ColumnNumbers = std::vector<uint8_t>;

/**
 * @brief Solves the N-Queens problem using backtracking.
 *
 * Given an integer N, this function finds all possible arrangements of N queens
 * on an N×N chessboard such that no two queens threaten each other. That means
 * no two queens share the same row, column, or diagonal.
 *
 * The solution is represented as a vector of vectors, where each inner vector
 * contains the column positions of queens for each row.
 *
 * @param numberOfQueens The size of the board and number of queens to place.
 * @return std::vector<ColumnNumbers> A vector containing all valid solutions. Each
 *         solution is a vector of size N, where the element at index i represents
 *         the column position of the queen in row i.
 *
 * @note This implementation uses three helper vectors to track which columns and
 *       diagonals are occupied for O(1) attack checks:
 *       - colsUsed: columns already occupied by queens.
 *       - diag1Used: "/" diagonals occupied, indexed by (row + col).
 *       - diag2Used: "\" diagonals occupied, indexed by (row - col + N - 1).
 */
std::vector<ColumnNumbers> nQueensProblem(uint8_t numberOfQueens)
{
    std::vector<ColumnNumbers> solutions;    // Store solutions as vectors of column positions
    ColumnNumbers solution(numberOfQueens);  // solution[row] = column of queen in that row

    std::vector<bool> colsUsed(numberOfQueens, false);
    std::vector<bool> diag1Used(2 * numberOfQueens - 1, false);  // "/" diagonals
    std::vector<bool> diag2Used(2 * numberOfQueens - 1, false);  // "\" diagonals

    std::function<void(int)> backtracking = [&](int row) {
        if (row == numberOfQueens)
        {
            solutions.push_back(solution);
            return;
        }

        for (int col = 0; col < numberOfQueens; ++col)
        {
            int d1 = row + col;
            int d2 = row - col + numberOfQueens - 1;

            // Check if column or diagonals are under attack
            if (colsUsed[col] || diag1Used[d1] || diag2Used[d2])
            {
                continue;
            }

            // Place queen
            solution[row] = col;
            colsUsed[col] = true;
            diag1Used[d1] = true;
            diag2Used[d2] = true;

            backtracking(row + 1);

            // Remove queen (backtrack)
            colsUsed[col] = false;
            diag1Used[d1] = false;
            diag2Used[d2] = false;
        }
    };

    backtracking(0);

    return solutions;
}

//////////////////////////////////////////////////////

using Maze = std::vector<std::vector<bool>>;
using MazeSolution = std::vector<std::pair<int, int>>;  // row, column path.

enum class Direction
{
    RIGHT,
    DOWN,
    LEFT,
    TOP
};

constexpr std::array<Direction, 4> directions{Direction::RIGHT, Direction::DOWN, Direction::LEFT, Direction::TOP};

// Exit is always (n-1, n-1)
std::vector<MazeSolution> ratInAmaze(const Maze& maze, int initRow, int initCol)
{
    std::vector<MazeSolution> solutions;
    MazeSolution solution;
    int n = maze.size();

    // Visited matrix to prevent cycles
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));

    std::function<void(int, int)> backtracking = [&](int row, int column) {
        // Base case: reached destination
        if (row == n - 1 && column == n - 1)
        {
            solution.push_back({row, column});  // Add the final cell
            solutions.push_back(solution);
            solution.pop_back();  // Backtrack
            return;
        }

        // Mark current cell as part of the path
        visited[row][column] = true;
        solution.push_back({row, column});

        for (auto direction : directions)
        {
            int nextRow = row;
            int nextColumn = column;

            if (direction == Direction::RIGHT)
            {
                nextColumn += 1;
            }
            else if (direction == Direction::DOWN)
            {
                nextRow += 1;
            }
            else if (direction == Direction::LEFT)
            {
                nextColumn -= 1;
            }
            else if (direction == Direction::TOP)
            {
                nextRow -= 1;
            }

            // Check boundaries and whether cell is accessible and not visited
            if (nextRow >= 0 && nextRow < n && nextColumn >= 0 && nextColumn < n && maze[nextRow][nextColumn] &&
                !visited[nextRow][nextColumn])
            {
                backtracking(nextRow, nextColumn);
            }
        }

        // Backtrack
        visited[row][column] = false;
        solution.pop_back();
    };

    // Only proceed if the initial cell is accessible
    if (maze[initRow][initCol])
    {
        backtracking(initRow, initCol);
    }

    return solutions;
}