#pragma once
#include <algorithm>  // for std::swap
#include <iterator>   // for std::distance

/**
 * @brief Sorts the elements in a range using the bubble sort algorithm.
 *
 * This function sorts the elements in the range [begin, end) using the
 * bubble sort algorithm. It operates in-place and is compatible with
 * any forward iterator (including bidirectional and random-access).
 * The elements must be comparable with `operator>` and swappable via `std::swap`.
 *
 * @tparam Iterator A forward iterator type. The value type pointed to by the
 *         iterator must support `operator>` and be swappable.
 * @param begin Iterator pointing to the beginning of the range to sort.
 * @param end Iterator pointing one past the last element in the range.
 *
 * @note The input range is modified in-place. The function is intended
 *       for very small datasets, as bubble sort
 *       is inefficient on large collections.
 *
 * @warning is inefficient (quadratic time complexity).
 *
 * @complexity
 * - Best-case:    O(n)     when the range is already sorted
 * - Average-case: O(n²)
 * - Worst-case:   O(n²)
 * - Space:        O(1)     (in-place, no extra memory used)
 *
 */
template <typename Iterator>
void bubbleSort(Iterator begin, Iterator end)
{
    if (begin == end || std::next(begin) == end)
    {
        return;  // Empty or single element
    }

    bool swapped{false};
    auto new_end = end;
    do
    {
        swapped = false;
        Iterator it = begin;
        Iterator next = std::next(it);

        while (next != new_end)
        {
            if (*it > *next)
            {
                std::swap(*it, *next);
                swapped = true;
            }
            ++it;
            ++next;
        }

        new_end = it;  // Last sorted element — we can stop earlier in the next pass
    } while (swapped);
}
