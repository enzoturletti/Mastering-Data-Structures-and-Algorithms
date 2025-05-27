#pragma once

#include <optional>
#include <functional>
#include <vector>
#include <stdexcept>
#include <algorithm>

/*
Algorithm DAC(Problem)
{
    if (small(Problem))
    {
        Solve(Problem);
        return;
    }

    Divide Problem in SubProblems.
    P1, P2, P3, P4.

    Apply DAC(P1), DAC(P2), ...

    Combine solutions.
}
*/

/**
 * @brief Performs a binary search on a sorted vector of integers.
 *
 * This function implements the Divide and Conquer (DAC) paradigm to search for a given value
 * in a sorted array using recursion.
 *
 * @param data A sorted vector of integers in ascending order.
 * @param target The integer value to search for.
 * @return The index of the target value in the vector if found, otherwise std::nullopt.
 *
 * @note The function assumes the input vector is sorted in ascending order.
 *
 * @complexity
 * Time Complexity: O(log n), where n is the number of elements in the vector.
 * Space Complexity: O(log n) due to recursion stack in the worst case.
 */
std::optional<int> binarySearch(const std::vector<int>& data, int target)
{
    std::function<std::optional<int>(int, int)> recursiveSearch = [&](int low, int high) -> std::optional<int> {
        if (low > high)
        {
            return std::nullopt;
        }

        int mid = (low + high) / 2;
        int current = data[mid];

        if (target == current)
        {
            return mid;
        }
        else if (target < current)
        {
            return recursiveSearch(low, mid - 1);
        }
        else
        {
            return recursiveSearch(mid + 1, high);
        }
    };

    return recursiveSearch(0, static_cast<int>(data.size()) - 1);
}

/**
 * @brief Merges K sorted integer vectors into a single sorted vector.
 *
 * This function supports both recursive (divide-and-conquer) and iterative merging strategies,
 * controlled via the template parameter `RECURSIVE_MODE`.
 *
 * @tparam RECURSIVE_MODE If true, uses recursive divide-and-conquer merging; otherwise, iterative pairwise merging.
 * @param vectors A vector of sorted integer vectors to be merged.
 * @return std::optional<std::vector<int>> A single merged and sorted vector if input is non-empty;
 *         std::nullopt otherwise.
 *
 * @note Time complexity: O(N log K), where K is the number of input vectors, and N is the total number of elements.
 *       Space complexity: O(N) for the output vector and temporary merged results.
 */
template <bool RECURSIVE_MODE>
std::optional<std::vector<int>> mergeKSort(const std::vector<std::vector<int>>& vectors)
{
    if (vectors.empty())
    {
        return std::nullopt;
    }

    if (vectors.size() == 1)
    {
        return vectors[0];
    }

    // Helper function to merge two sorted vectors
    static auto mergeTwo = [](const std::vector<int>& v1, const std::vector<int>& v2) -> std::vector<int> {
        std::vector<int> result;
        size_t i = 0, j = 0;

        while (i < v1.size() && j < v2.size())
        {
            if (v1[i] < v2[j])
            {
                result.push_back(v1[i++]);
            }
            else
            {
                result.push_back(v2[j++]);
            }
        }

        while (i < v1.size())
            result.push_back(v1[i++]);
        while (j < v2.size())
            result.push_back(v2[j++]);

        return result;
    };

    if constexpr (!RECURSIVE_MODE)
    {
        std::vector<std::vector<int>> current = vectors;

        while (current.size() > 1)
        {
            std::vector<std::vector<int>> next;
            for (size_t i = 0; i + 1 < current.size(); i += 2)
            {
                next.push_back(mergeTwo(current[i], current[i + 1]));
            }
            if (current.size() % 2 == 1)
            {
                next.push_back(current.back());
            }
            current = std::move(next);
        }

        return current[0];
    }
    else
    {
        std::function<std::vector<int>(int, int)> recursiveMerge = [&](int left, int right) -> std::vector<int> {
            if (left == right)
            {
                return vectors[left];
            }

            int mid = (left + right) / 2;
            std::vector<int> leftMerged = recursiveMerge(left, mid);
            std::vector<int> rightMerged = recursiveMerge(mid + 1, right);
            return mergeTwo(leftMerged, rightMerged);
        };

        return recursiveMerge(0, vectors.size() - 1);
    }
}

std::vector<std::vector<int>> matrixMultiplication(
    const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2)
{
    // Check if either matrix is empty
    if (matrix1.empty() || matrix2.empty())
    {
        throw std::invalid_argument("Input matrices must not be empty.");
    }

    size_t n = matrix1.size();
    if (matrix1[0].size() != n || matrix2.size() != n || matrix2[0].size() != n)
    {
        throw std::invalid_argument("Only square matrices of equal size are supported.");
    }

    // Simple 2x2 multiplication
    static auto matrixSimpleMultiplication =
        [](const std::vector<std::vector<int>>& A,
           const std::vector<std::vector<int>>& B) -> std::vector<std::vector<int>> {
        std::vector<std::vector<int>> C(2, std::vector<int>(2));
        C[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
        C[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
        C[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
        C[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
        return C;
    };

    // Matrix addition
    static auto add = [](const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
        size_t n = A.size();
        std::vector<std::vector<int>> C(n, std::vector<int>(n));
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
        return C;
    };

    // Split matrix into 4 submatrices
    static auto splitMatrix = [](const std::vector<std::vector<int>>& M, std::vector<std::vector<int>>& M11,
                                 std::vector<std::vector<int>>& M12, std::vector<std::vector<int>>& M21,
                                 std::vector<std::vector<int>>& M22) {
        size_t n = M.size();
        size_t half = n / 2;
        M11.resize(half, std::vector<int>(half));
        M12.resize(half, std::vector<int>(half));
        M21.resize(half, std::vector<int>(half));
        M22.resize(half, std::vector<int>(half));
        for (size_t i = 0; i < half; ++i)
        {
            std::copy(M[i].begin(), M[i].begin() + half, M11[i].begin());
            std::copy(M[i].begin() + half, M[i].end(), M12[i].begin());
            std::copy(M[i + half].begin(), M[i + half].begin() + half, M21[i].begin());
            std::copy(M[i + half].begin() + half, M[i + half].end(), M22[i].begin());
        }
    };

    // Merge 4 submatrices into 1 matrix
    static auto mergeMatrix = [](const std::vector<std::vector<int>>& C11, const std::vector<std::vector<int>>& C12,
                                 const std::vector<std::vector<int>>& C21,
                                 const std::vector<std::vector<int>>& C22) -> std::vector<std::vector<int>> {
        size_t half = C11.size();
        size_t n = 2 * half;
        std::vector<std::vector<int>> result(n, std::vector<int>(n));
        for (size_t i = 0; i < half; ++i)
        {
            std::copy(C11[i].begin(), C11[i].end(), result[i].begin());
            std::copy(C12[i].begin(), C12[i].end(), result[i].begin() + half);
            std::copy(C21[i].begin(), C21[i].end(), result[i + half].begin());
            std::copy(C22[i].begin(), C22[i].end(), result[i + half].begin() + half);
        }
        return result;
    };

    // Recursive multiplication function
    std::function<std::vector<std::vector<int>>(
        const std::vector<std::vector<int>>&, const std::vector<std::vector<int>>&)>
        multiply;

    multiply = [&](const std::vector<std::vector<int>>& A,
                   const std::vector<std::vector<int>>& B) -> std::vector<std::vector<int>> {
        size_t n = A.size();
        if (n == 2)
        {
            return matrixSimpleMultiplication(A, B);
        }

        // Split A and B into submatrices
        std::vector<std::vector<int>> A11, A12, A21, A22;
        std::vector<std::vector<int>> B11, B12, B21, B22;
        splitMatrix(A, A11, A12, A21, A22);
        splitMatrix(B, B11, B12, B21, B22);

        // Compute submatrix results recursively
        auto C11 = add(multiply(A11, B11), multiply(A12, B21));
        auto C12 = add(multiply(A11, B12), multiply(A12, B22));
        auto C21 = add(multiply(A21, B11), multiply(A22, B21));
        auto C22 = add(multiply(A21, B12), multiply(A22, B22));

        return mergeMatrix(C11, C12, C21, C22);
    };

    return multiply(matrix1, matrix2);
}