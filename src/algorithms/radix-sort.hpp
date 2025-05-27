#pragma once
#include <algorithm>
#include <iterator>
#include <list>
#include <stdexcept>
#include <vector>

/**
 * @brief Sorts a range of non-negative integers using Radix Sort.
 *
 * @tparam Iterator Random access or at least forward iterator for integer values.
 * @param begin Iterator to the first element.
 * @param end Iterator one past the last element.
 *
 * @throws std::invalid_argument if any element is negative.
 *
 * @note This version assumes base-10 and non-negative integers.
 * @complexity Time: O(d·(n + k)), where d = number of digits, n = number of elements, and k = radix (10).
 *             Space: O(n + k)
 */
template <typename Iterator>
void radixSort(Iterator begin, Iterator end)
{
    if (begin == end || std::next(begin) == end)
    {
        return;  // Nothing to sort
    }

    // Check for negative values
    for (auto it = begin; it != end; ++it)
    {
        if (*it < 0)
        {
            throw std::invalid_argument("Radix sort requires non-negative integers.");
        }
    }

    // Find the maximum number to know the number of digits
    auto maxIt = std::max_element(begin, end);
    int maxValue = *maxIt;

    // Place values into bins by digit (starting from least significant)
    int exp = 1;  // digit position: 1, 10, 100, ...

    while (maxValue / exp > 0)
    {
        std::vector<std::list<int>> bins(10);  // base-10

        // Distribute elements into bins based on current digit
        for (auto it = begin; it != end; ++it)
        {
            int digit = (*it / exp) % 10;
            bins[digit].push_back(*it);
        }

        // Collect back into the container
        auto it = begin;
        for (int i = 0; i < 10; ++i)
        {
            for (int val : bins[i])
            {
                *it = val;
                ++it;
            }
        }

        exp *= 10;
    }
}
