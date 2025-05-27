#pragma once

/**
 * @brief Sorts a range of elements using the QuickSort algorithm.
 *
 * @tparam Iterator Random access iterator type.
 * @param begin Iterator pointing to the beginning of the range.
 * @param end Iterator pointing to one past the last element of the range.
 *
 * @note This version uses Lomuto partitioning and is not stable.
 * @complexity Time: O(n log n) average, O(n^2) worst (if elements are already sorted). Space: O(log n) recursion stack.
 */
template <typename Iterator>
void quickSort(Iterator begin, Iterator end)
{
    if (begin == end || std::next(begin) == end)  // 0 or 1 element
    {
        return;
    }

    // Choose pivot as first element
    auto pivotValue = *begin;

    Iterator left = std::next(begin);
    Iterator right = std::prev(end);

    while (true)
    {
        while (left != end && *left <= pivotValue)
        {
            ++left;
        }

        while (right != begin && *right > pivotValue)
        {
            --right;
        }

        if (left == end || right == begin || left >= right)
        {
            break;
        }

        std::swap(*left, *right);
    }

    // Place pivot in its correct position
    std::swap(*begin, *right);

    // Recursively sort the partitions
    quickSort(begin, right);
    quickSort(std::next(right), end);
}
