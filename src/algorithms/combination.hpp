#pragma once

#include <functional>
#include <string>
#include <unordered_set>
#include <vector>

std::vector<std::string> combination(std::string input, int elementsSize)
{
    std::vector<std::string> solution;
    std::string partialSolution;

    // Sort the input string to group duplicates together
    std::sort(input.begin(), input.end());

    // Backtracking helper function
    std::function<void(int, int)> backtrack = [&](int start, int count) {
        // Base case: When the partial solution has the desired size
        if (count == elementsSize)
        {
            solution.push_back(partialSolution);  // Add the current combination to the result
            return;
        }

        // Generate combinations
        for (int i = start; i < input.size(); ++i)
        {
            // Skip duplicate characters (to avoid repeated combinations)
            if (i > start && input[i] == input[i - 1])
                continue;

            // Add the current character to the partial solution
            partialSolution.push_back(input[i]);

            // Recurse with the next character, with the updated combination size
            backtrack(i + 1, count + 1);

            // Backtrack: remove the last character added to the partial solution
            partialSolution.pop_back();
        }
    };

    // Start the backtracking process from index 0
    constexpr int start{0};
    constexpr int count{0};
    backtrack(start, count);
    return solution;
}
