#pragma once

#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>

/**
 * @brief Sorts a range of non-negative integers using the Counting Sort algorithm.
 *
 * @tparam Iterator Random access iterator type pointing to a container of integers.
 * @param begin Iterator pointing to the beginning of the range.
 * @param end Iterator pointing to one past the last element of the range.
 *
 * @note This sort is not comparison-based and only works on non-negative integers.
 * @throws std::invalid_argument if the range contains negative numbers.
 *
 * @complexity Time: O(n + k), where n = number of elements and k = max element value.
 *             Space: O(k), additional memory for count array.
 */
template <typename Iterator>
void countSort(Iterator begin, Iterator end)
{
    if (begin == end || std::next(begin) == end)
    {
        return;  // Empty or single element
    }

    auto [minIt, maxIt] = std::minmax_element(begin, end);

    int minValue = *minIt;
    int maxValue = *maxIt;

    if (minValue < 0)
    {
        throw std::invalid_argument("Counting sort requires non-negative integers.");
    }

    std::vector<int> count(maxValue + 1, 0);

    for (auto it = begin; it != end; ++it)
    {
        ++count[*it];
    }

    // Overwrite input with sorted values
    auto it = begin;
    for (int val = 0; val <= maxValue; ++val)
    {
        while (count[val]-- > 0)
        {
            *it = val;
            ++it;
        }
    }
}