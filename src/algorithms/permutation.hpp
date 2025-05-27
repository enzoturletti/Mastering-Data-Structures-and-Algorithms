#pragma once

#include <functional>
#include <string>
#include <vector>

/**
 * @brief Generates all unique permutations of a given string.
 *
 * This function generates all unique permutations of the input string using a backtracking approach.
 * It ensures that no duplicate permutations are added by skipping over repeated characters during
 * the recursion process. The input string is sorted initially to make it easier to identify duplicates.
 *
 * @param input The input string for which permutations are generated.
 * @return A vector of strings containing all unique permutations of the input string.
 *
 * @note
 * - The function handles duplicate characters by skipping over them during the backtracking process.
 *   This ensures that each character is used the correct number of times in each permutation.
 * - The result is accurate and complete for strings with both unique and duplicate characters.
 *
 * ### Time Complexity
 * - **Worst-case (unique characters):** O(n * n!), where `n` is the length of the input string.
 *   - There are `n!` permutations, and each permutation requires O(n) time to construct.
 * - **Best-case (all identical characters):** O(n), as only one unique permutation exists.
 *
 * ### Space Complexity
 * - **O(n):** For the recursion stack and the `input` string.
 * - **O(k):** For the recursion stack (where `k` is the number of recursive calls), though the space usage is minimal
 *in comparison to the total number of permutations.
 *
 * ### Implementation Details
 * - The function first sorts the input string to group duplicate characters together.
 * - A recursive backtracking helper function constructs permutations by swapping characters in the input string.
 * - Upon reaching a valid permutation (when the starting index reaches the end of the string),
 *   the function stores the result in the `solution` vector.
 * - Backtracking ensures all possible permutations are explored by restoring the state after each recursive call.
 * - Duplicate characters are skipped by checking that characters at the current index are not equal
 *   to characters at the previous index.
 **/
std::vector<std::string> permutation(std::string input)
{
    std::vector<std::string> solution;

    // Sort the input string to group duplicates together
    std::sort(input.begin(), input.end());

    // Backtracking helper function
    std::function<void(int)> backtrack = [&](int start) {
        // Base case: When the starting index reaches the end of the string
        if (start == input.size())
        {
            solution.push_back(input);  // Add the current permutation to the result
            return;
        }

        // Generate permutations by swapping
        for (int i = start; i < input.size(); ++i)
        {
            // Skip duplicate characters
            if (i != start && input[i] == input[start])
                continue;

            std::swap(input[start], input[i]);  // Swap current index with the loop index
            backtrack(start + 1);               // Recurse to fix the next position
            std::swap(input[start], input[i]);  // Undo the swap (backtrack)
        }
    };

    // Start the backtracking process from index 0
    backtrack(0);
    return solution;
}