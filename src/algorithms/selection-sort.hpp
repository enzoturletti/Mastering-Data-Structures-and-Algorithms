#pragma once

/**
 * @brief Sorts a range of elements using the selection sort algorithm.
 *
 * @tparam Iterator A forward or bidirectional iterator type.
 * @param begin Iterator to the beginning of the range.
 * @param end Iterator to one past the end of the range.
 *
 * @note Selection sort is not stable and performs poorly on large datasets.
 *
 * @complexity
 * Time Complexity: O(n^2) comparisons, O(n) swaps.
 * Space Complexity: O(1) — in-place.
 */
template <typename Iterator>
void selectionSort(Iterator begin, Iterator end)
{
    if (begin == end || std::next(begin) == end)
    {
        return;  // Empty or single element
    }

    for (Iterator i = begin; i != end; ++i)
    {
        Iterator k = i;  // Iterator to the minimum element

        for (Iterator j = std::next(i); j != end; ++j)
        {
            if (*j < *k)
            {
                k = j;
            }
        }

        if (k != i)
        {
            std::swap(*i, *k);
        }
    }
}