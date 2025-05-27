#pragma once

#include <set>
#include <utility>  // for std::pair
#include <cstdint>  // for uint16_t

//////////////////////////////////////////////////////////////////
//                    Dynamic Programming (DP)                   //
//////////////////////////////////////////////////////////////////

/*
Dynamic Programming is an optimization technique used to solve problems
that exhibit **overlapping subproblems** and **optimal substructure**.
Follows principle of optimality.

- Overlapping Subproblems: The same subproblems are solved repeatedly.
- Optimal Substructure: An optimal solution can be built from optimal
  solutions to its subproblems.

DP avoids redundant computations by storing intermediate results
(e.g., in a table or array) and reusing them when needed.

Example:
0/1 Knapsack Problem — Given a set of items with weights and values,
determine the maximum total value that can be obtained in a knapsack
of fixed capacity, where each item can be either taken or not taken
(you can't take a fraction of an item).
*/

/*
DP Algorithm Framework (0/1 Knapsack)

Inputs:
    weights[]  — array of item weights
    values[]   — array of item values
    n          — number of items
    W          — maximum capacity of the knapsack

Algorithm KnapsackDP(weights, values, n, W)
{
    Create a table dp[n+1][W+1];

    // Initialize base case: 0 items or 0 capacity
    for (i = 0 to n)
        for (w = 0 to W)
            if (i == 0 || w == 0)
                dp[i][w] = 0;

    // Fill table in bottom-up manner
    for (i = 1 to n)
    {
        for (w = 1 to W)
        {
            if (weights[i-1] <= w)
            {
                // Max of including or not including the item
                dp[i][w] = max(values[i-1] + dp[i-1][w - weights[i-1]],
                               dp[i-1][w]);
            }
            else
            {
                dp[i][w] = dp[i-1][w]; // Cannot include the item
            }
        }
    }

    return dp[n][W]; // Maximum value that can be carried
}

*/

////////////////////// 0-1 KNAPSACK ////////////////////////////
// Pn(m) = max {Pn-1(m), Pn-1(m-w(n)+P(n))} -> Profit recursive formula for object n with a bag of capacity m.

using ProfitWeight = std::pair<uint16_t, uint16_t>;
using ProfitWeightVector = std::vector<ProfitWeight>;

struct KnapSackSolution
{
    uint16_t profit;
    uint16_t weight;
    std::vector<bool> chosenItems;

    KnapSackSolution(uint16_t p, uint16_t w, size_t n) : profit(p), weight(w), chosenItems(n, false)
    {
    }

    KnapSackSolution(uint16_t p, uint16_t w, const std::vector<bool>& chosen)
        : profit(p), weight(w), chosenItems(chosen)
    {
    }
};

/**
 * @brief Solves the 0/1 Knapsack problem using the Set-based method with dominance pruning.
 *
 * This function iteratively builds up possible solutions using a set of partial results.
 * After adding each item, it prunes dominated solutions (i.e., those that are heavier and
 * do not offer better profit).
 *
 * @param items Vector of (profit, weight) pairs representing the available items.
 * @param bagCapacity The maximum weight the knapsack can carry.
 * @return A boolean vector where each index indicates whether the corresponding item is included in the optimal
 * solution.
 *
 * @note Uses a set with a custom comparator to automatically sort and deduplicate solutions.
 *
 * @complexity Time: O(n * s log s), where n is the number of items, and s is the number of partial solutions at each
 * step (which can grow exponentially in the worst case). Space: O(s), where s is the number of partial solutions
 * retained. (s log s is the cost of inserting s elements in the set)
 */
std::vector<bool> KnapSackAlgorithmSetMethod(const ProfitWeightVector& items, uint16_t bagCapacity)
{
    // Comparator to sort solutions by weight ascending and for equal weight by profit descending
    struct CompareByWeight
    {
        bool operator()(const KnapSackSolution& a, const KnapSackSolution& b) const
        {
            if (a.weight != b.weight)
            {
                return a.weight < b.weight;
            }
            return a.profit > b.profit;
        }
    };

    std::set<KnapSackSolution, CompareByWeight> possibleSolutions;
    possibleSolutions.insert(KnapSackSolution(0, 0, items.size()));  // start with empty solution

    for (size_t idx = 0; idx < items.size(); ++idx)
    {
        const auto& item = items[idx];
        std::set<KnapSackSolution, CompareByWeight> auxSet;

        for (const auto& sol : possibleSolutions)
        {
            uint16_t newProfit = sol.profit + item.first;
            uint16_t newWeight = sol.weight + item.second;

            if (newWeight <= bagCapacity)
            {
                std::vector<bool> newChosen = sol.chosenItems;
                newChosen[idx] = true;
                auxSet.insert(KnapSackSolution(newProfit, newWeight, newChosen));
            }
        }

        // Merge auxSet into possibleSolutions
        possibleSolutions.insert(auxSet.begin(), auxSet.end());

        // Prune dominated solutions
        std::set<KnapSackSolution, CompareByWeight> prunedSet;
        KnapSackSolution best(0, 0, items.size());  // impossible best

        for (const auto& sol : possibleSolutions)
        {
            if (prunedSet.empty() || sol.profit > best.profit)
            {
                prunedSet.insert(sol);
                best = sol;
            }
        }

        possibleSolutions = std::move(prunedSet);
    }

    // Find best solution (max profit, weight <= capacity)
    KnapSackSolution bestSol(0, 0, items.size());
    for (const auto& sol : possibleSolutions)
    {
        if (sol.profit > bestSol.profit)
        {
            bestSol = sol;
        }
    }

    return bestSol.chosenItems;
}

/**
 * @brief Computes the maximum profit for the 0/1 Knapsack problem using a plain recursive approach.
 *
 * This recursive implementation explores all combinations of including or excluding items.
 * It does not use memoization or backtracking to track selected items — only the max profit is returned.
 *
 * @param items Vector of (profit, weight) pairs representing the available items.
 * @param bagCapacity The maximum weight the knapsack can carry.
 * @return The maximum profit that can be achieved without exceeding the bag capacity.
 *
 * @warning This method has exponential time complexity and should not be used for large input sizes.
 *
 * @complexity Time: O(2^n), where n is the number of items.
 *             Space: O(n), due to recursive call stack depth.
 */
uint16_t KnapSackAlgorithmRecursiveMethod(const ProfitWeightVector& items, uint16_t bagCapacity)
{
    std::function<uint16_t(uint16_t, uint16_t)> computeMaxProfit = [&](uint16_t itemCount,
                                                                       uint16_t remainingCapacity) -> uint16_t {
        if (itemCount == 0 || remainingCapacity == 0)
        {
            return 0;
        }

        const auto& currentItem = items[itemCount - 1];
        uint16_t currentProfit = currentItem.first;
        uint16_t currentWeight = currentItem.second;

        // If current item doesn't fit, skip it
        if (currentWeight > remainingCapacity)
        {
            return computeMaxProfit(itemCount - 1, remainingCapacity);
        }

        // Case 1: Include the current item
        uint16_t profitIncluding = computeMaxProfit(itemCount - 1, remainingCapacity - currentWeight) + currentProfit;

        // Case 2: Exclude the current item
        uint16_t profitExcluding = computeMaxProfit(itemCount - 1, remainingCapacity);

        // Return the better of the two
        return std::max(profitIncluding, profitExcluding);
    };

    return computeMaxProfit(items.size(), bagCapacity);
}

/**
 * @brief Solves the 0/1 Knapsack problem using a top-down recursive approach with memoization.
 *
 * Given a list of items (each with a profit and weight) and a maximum capacity,
 * this function computes the maximum profit that can be achieved without exceeding
 * the capacity. It also tracks which items are included in the optimal solution.
 *
 * @param items A vector of pairs representing items, where each pair consists of:
 *              - first: profit (uint16_t)
 *              - second: weight (uint16_t)
 * @param bagCapacity The maximum weight capacity of the knapsack.
 *
 * @return A std::pair consisting of:
 *         - uint16_t: The maximum profit achievable.
 *         - std::vector<bool>: A boolean vector where each index indicates whether the
 *                              corresponding item is included in the optimal solution.
 *
 * @note This implementation uses memoization (top-down DP) to avoid redundant
 *       computations. The memoization matrix is filled recursively, and the item
 *       selection is determined through a backtracking step using the filled matrix.
 *
 * @complexity Time: O(n * W), where n = number of items, W = bagCapacity.
 *             Space: O(n * W) for the memoization table.
 */
std::pair<uint16_t, std::vector<bool>> KnapSackAlgorithmRecursiveMethodWithMemorization(
    const ProfitWeightVector& items, uint16_t bagCapacity)
{
    std::vector<std::vector<int>> memo(items.size() + 1, std::vector<int>(bagCapacity + 1, -1));

    // Recursive DP with memoization
    std::function<int(size_t, size_t)> computeMaxProfit = [&](size_t i, size_t capacity) -> int {
        if (i == 0 || capacity == 0)
            return 0;

        if (memo[i][capacity] != -1)
            return memo[i][capacity];

        const auto& [profit, weight] = items[i - 1];

        if (weight > capacity)
            return memo[i][capacity] = computeMaxProfit(i - 1, capacity);

        int include = computeMaxProfit(i - 1, capacity - weight) + profit;
        int exclude = computeMaxProfit(i - 1, capacity);
        return memo[i][capacity] = std::max(include, exclude);
    };

    uint16_t maxProfit = computeMaxProfit(items.size(), bagCapacity);

    // Backtrack to find which items were included
    std::vector<bool> included(items.size(), false);
    size_t i = items.size();
    size_t capacity = bagCapacity;

    while (i > 0 && capacity > 0)
    {
        if (memo[i][capacity] != memo[i - 1][capacity])
        {
            included[i - 1] = true;
            capacity -= items[i - 1].second;
        }
        --i;
    }

    return {maxProfit, included};
}

/**
 * @brief Solves the 0/1 Knapsack problem using bottom-up tabulation.
 *
 * @param items Vector of (profit, weight) pairs.
 * @param bagCapacity Maximum capacity of the knapsack.
 * @return A pair containing:
 *         - Maximum achievable profit.
 *         - Vector of bools indicating which items are included in the optimal solution.
 */
std::pair<uint16_t, std::vector<bool>> KnapSackAlgorithmTabulationMethod(
    const ProfitWeightVector& items, uint16_t bagCapacity)
{
    size_t n = items.size();

    // Matrix[i][j] with the best profit I can take using the first i items with a bag of size j.
    std::vector<std::vector<int>> tabulation(n + 1, std::vector<int>(bagCapacity + 1, 0));

    // Fill the DP table
    for (size_t i = 1; i <= n; ++i)
    {
        uint16_t profit = items[i - 1].first;
        uint16_t weight = items[i - 1].second;

        for (size_t j = 0; j <= bagCapacity; ++j)
        {
            if (weight > j)
            {
                tabulation[i][j] = tabulation[i - 1][j];
            }
            else
            {
                // Decide whether to take the current item:
                // - Add its profit: + profit
                // - Reduce the bag's capacity: j - weight
                // - See how much profit you could have gotten with the remaining space and previous items: tabulation[i
                // - 1][j - weight] “If I include this, what’s the best profit I could have gotten earlier, when I had
                // less space left (i.e. j - weight) and only i - 1 items to choose from?”
                tabulation[i][j] = std::max(tabulation[i - 1][j], tabulation[i - 1][j - weight] + profit);
            }
        }
    }

    // Extract max profit
    uint16_t maxProfit = tabulation[n][bagCapacity];

    // Backtrack to find included items
    std::vector<bool> included(n, false);
    size_t i = n;
    size_t w = bagCapacity;

    while (i > 0 && w > 0)
    {
        if (tabulation[i][w] != tabulation[i - 1][w])
        {
            included[i - 1] = true;
            w -= items[i - 1].second;
        }
        --i;
    }

    return {maxProfit, included};
}

////////////////////// MATRIX CHAIN MULTIPLICATION ////////////////////////////

using Matrix = std::vector<std::vector<int>>;
using MatrixChain = std::vector<Matrix>;

/**
 * @brief Computes the minimum number of scalar multiplications needed
 *        to multiply a chain of matrices using a recursive method.
 *
 * This function takes a sequence of matrices and determines the most efficient way
 * to parenthesize them such that the total number of scalar multiplications is minimized.
 * The method uses a naive recursive approach (without memoization), and it assumes
 * matrices are represented as 2D vectors where matrix[i] is the i-th matrix.
 *
 * Each matrix must be compatible with the next in the chain for multiplication:
 * if matrix A has dimensions (m x n), then the next matrix B must have dimensions (n x p).
 *
 * @param matrixes A vector of matrices (each a 2D vector of uint16_t values) to be multiplied.
 *                 The vector must contain at least one matrix, and all matrices must be
 *                 properly sized and chain-compatible.
 *
 * @return The minimum number of scalar multiplications needed to compute the product.
 *
 * @throws std::invalid_argument if the matrix list is empty, improperly initialized,
 *         or contains incompatible dimensions for chain multiplication.
 *
 * @note The algorithm has exponential time complexity due to the lack of memoization.
 *       For large chains, consider using a dynamic programming approach instead.
 */
uint16_t MatrixChainMultiplicationRecursionMethod(const MatrixChain& matrixes)
{
    const size_t n = matrixes.size();

    // Validation: matrix dimensions must be chain-compatible.
    for (size_t i = 0; i < n - 1; ++i)
    {
        size_t cols_i = matrixes[i][0].size();
        size_t rows_next = matrixes[i + 1].size();
        if (cols_i != rows_next)
        {
            throw std::invalid_argument("Matrix dimensions are incompatible for chain multiplication.");
        }
    }

    // Construct dimension vector d = [p0, p1, ..., pn]
    std::vector<uint16_t> d;
    if (n == 0 || matrixes[0].empty() || matrixes[0][0].empty())
    {
        throw std::invalid_argument("Matrix list is empty or improperly initialized.");
    }

    d.reserve(n + 1);
    d.push_back(static_cast<uint16_t>(matrixes[0].size()));
    for (const auto& matrix : matrixes)
    {
        if (matrix.empty() || matrix[0].empty())
        {
            throw std::invalid_argument("One of the matrices is empty or has empty rows.");
        }
        d.push_back(static_cast<uint16_t>(matrix[0].size()));
    }

    // Recursive function (1-based indexing for matrix labels A1...An)
    std::function<uint16_t(uint16_t, uint16_t)> computeMinimumCost = [&](uint16_t i, uint16_t j) {
        if (i == j)
        {
            return static_cast<uint16_t>(0);  // No multiplication needed
        }

        uint16_t minCost = std::numeric_limits<uint16_t>::max();

        for (uint16_t k = i; k < j; k++)
        {
            uint16_t costLeft = computeMinimumCost(i, k);
            uint16_t costRight = computeMinimumCost(k + 1, j);
            uint16_t costMultiply = d[i - 1] * d[k] * d[j];

            uint16_t totalCost = costLeft + costRight + costMultiply;
            if (totalCost < minCost)
            {
                minCost = totalCost;
            }
        }

        return minCost;
    };

    // Compute the minimum cost for full chain: A1 to An
    return computeMinimumCost(1, static_cast<uint16_t>(n));
}

/**
 * @brief Computes the minimum number of scalar multiplications needed
 *        to multiply a chain of matrices using a recursive method with memoization.
 *
 * This function takes a sequence of matrices and determines the most efficient way
 * to parenthesize them such that the total number of scalar multiplications is minimized.
 * The method uses top-down recursion with memoization to optimize overlapping subproblems.
 *
 * Each matrix must be compatible with the next in the chain for multiplication:
 * if matrix A has dimensions (m x n), then the next matrix B must have dimensions (n x p).
 *
 * @param matrixes A vector of matrices (each a 2D vector of uint16_t values) to be multiplied.
 *                 The vector must contain at least one matrix, and all matrices must be
 *                 properly sized and chain-compatible.
 *
 * @return The minimum number of scalar multiplications needed to compute the product.
 *
 * @throws std::invalid_argument if the matrix list is empty, improperly initialized,
 *         or contains incompatible dimensions for chain multiplication.
 *
 * @note This method has polynomial time complexity (O(n^3)) due to memoization.
 */
uint16_t MatrixChainMultiplicationRecursionMethodWithMemorization(const MatrixChain& matrixes)
{
    const size_t n = matrixes.size();

    // Validation: matrix dimensions must be chain-compatible.
    for (size_t i = 0; i < n - 1; ++i)
    {
        size_t cols_i = matrixes[i][0].size();
        size_t rows_next = matrixes[i + 1].size();
        if (cols_i != rows_next)
        {
            throw std::invalid_argument("Matrix dimensions are incompatible for chain multiplication.");
        }
    }

    // Construct dimension vector d = [p0, p1, ..., pn]
    std::vector<uint16_t> d;
    if (n == 0 || matrixes[0].empty() || matrixes[0][0].empty())
    {
        throw std::invalid_argument("Matrix list is empty or improperly initialized.");
    }

    d.reserve(n + 1);
    d.push_back(static_cast<uint16_t>(matrixes[0].size()));
    for (const auto& matrix : matrixes)
    {
        if (matrix.empty() || matrix[0].empty())
        {
            throw std::invalid_argument("One of the matrices is empty or has empty rows.");
        }
        d.push_back(static_cast<uint16_t>(matrix[0].size()));
    }

    // Initialize memoization table with UINT16_MAX as a sentinel for "not computed"
    std::vector<std::vector<uint16_t>> memo(n + 1, std::vector<uint16_t>(n + 1, std::numeric_limits<uint16_t>::max()));

    std::function<uint16_t(uint16_t, uint16_t)> computeMinimumCost = [&](uint16_t i, uint16_t j) {
        if (i == j)
        {
            return static_cast<uint16_t>(0);
        }

        if (memo[i][j] != std::numeric_limits<uint16_t>::max())
        {
            return memo[i][j];
        }

        uint16_t minCost = std::numeric_limits<uint16_t>::max();

        for (uint16_t k = i; k < j; ++k)
        {
            uint16_t costLeft = computeMinimumCost(i, k);
            uint16_t costRight = computeMinimumCost(k + 1, j);
            uint16_t costMultiply = d[i - 1] * d[k] * d[j];

            uint16_t totalCost = costLeft + costRight + costMultiply;
            if (totalCost < minCost)
            {
                minCost = totalCost;
            }
        }

        memo[i][j] = minCost;
        return minCost;
    };

    return computeMinimumCost(1, static_cast<uint16_t>(n));
}

/**
 * @brief Computes the minimum number of scalar multiplications needed
 *        to multiply a chain of matrices using bottom-up dynamic programming.
 *
 * This function uses the classic matrix chain multiplication dynamic programming
 * approach (tabulation) to determine the most efficient order of multiplication.
 *
 * Each matrix must be compatible with the next in the chain for multiplication:
 * if matrix A has dimensions (m x n), then the next matrix B must have dimensions (n x p).
 *
 * @param matrixes A vector of matrices (each a 2D vector of uint16_t values) to be multiplied.
 *                 The vector must contain at least one matrix, and all matrices must be
 *                 properly sized and chain-compatible.
 *
 * @return The minimum number of scalar multiplications needed to compute the product.
 *
 * @throws std::invalid_argument if the matrix list is empty, improperly initialized,
 *         or contains incompatible dimensions for chain multiplication.
 *
 * @note Time complexity: O(n^3), Space complexity: O(n^2)
 */
uint16_t MatrixChainMultiplicationTabulationMethod(const MatrixChain& matrixes)
{
    const size_t n = matrixes.size();

    // Validation: matrix dimensions must be chain-compatible.
    for (size_t i = 0; i < n - 1; ++i)
    {
        size_t cols_i = matrixes[i][0].size();
        size_t rows_next = matrixes[i + 1].size();
        if (cols_i != rows_next)
        {
            throw std::invalid_argument("Matrix dimensions are incompatible for chain multiplication.");
        }
    }

    // Construct dimension vector d = [p0, p1, ..., pn]
    std::vector<uint16_t> d;
    if (n == 0 || matrixes[0].empty() || matrixes[0][0].empty())
    {
        throw std::invalid_argument("Matrix list is empty or improperly initialized.");
    }

    d.reserve(n + 1);
    d.push_back(static_cast<uint16_t>(matrixes[0].size()));
    for (const auto& matrix : matrixes)
    {
        if (matrix.empty() || matrix[0].empty())
        {
            throw std::invalid_argument("One of the matrices is empty or has empty rows.");
        }
        d.push_back(static_cast<uint16_t>(matrix[0].size()));
    }

    // m[i][j] = minimum cost to multiply matrices A_i through A_j
    std::vector<std::vector<uint16_t>> m(n + 1, std::vector<uint16_t>(n + 1, 0));

    // l is the chain length
    for (uint16_t l = 2; l <= n; ++l)
    {
        for (uint16_t i = 1; i <= n - l + 1; ++i)
        {
            uint16_t j = i + l - 1;
            m[i][j] = std::numeric_limits<uint16_t>::max();

            for (uint16_t k = i; k < j; ++k)
            {
                uint16_t cost = m[i][k] + m[k + 1][j] + d[i - 1] * d[k] * d[j];
                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                }
            }
        }
    }

    return m[1][n];
}
