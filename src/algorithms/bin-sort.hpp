#pragma once

#include <list>
#include <vector>

#include <algorithm>
#include <iterator>
#include <list>
#include <stdexcept>
#include <vector>

/**
 * @brief Sorts a range of non-negative integers using bin sort (a variant of bucket sort).
 *
 * @tparam Iterator Forward or random access iterator over a range of non-negative integers.
 * @param begin Iterator to the beginning of the range.
 * @param end Iterator to one past the last element in the range.
 *
 * @note Bin sort assumes the input contains non-negative integers.
 * @throws std::invalid_argument if any value in the range is negative.
 * @complexity Time: O(n + k), Space: O(n + k), where n is number of elements and k is max value.
 */
template <typename Iterator>
void binSort(Iterator begin, Iterator end)
{
    if (begin == end || std::next(begin) == end)
    {
        return;  // Nothing to sort
    }

    auto [minIt, maxIt] = std::minmax_element(begin, end);
    int minValue = *minIt;
    int maxValue = *maxIt;

    if (minValue < 0)
    {
        throw std::invalid_argument("Bin sort requires non-negative integers.");
    }

    std::vector<std::list<int>> bins(maxValue + 1);

    for (auto it = begin; it != end; ++it)
    {
        bins[*it].push_back(*it);
    }

    auto it = begin;
    for (int val = 0; val <= maxValue; ++val)
    {
        while (!bins[val].empty())
        {
            *it = bins[val].front();
            bins[val].pop_front();
            ++it;
        }
    }
}
