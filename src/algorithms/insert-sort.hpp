#pragma once

/**
 * @brief Performs insertion sort on a range defined by two iterators.
 *
 * This function sorts the elements in the range [begin, end) using the insertion sort algorithm.
 * It is stable and works well on small or nearly sorted ranges. The algorithm compares each element
 * with the previous sorted portion and shifts elements forward to insert the current one into its proper position.
 *
 * It works efficiently on linked lists as it only requires iterator traversal and assignments,
 * avoiding expensive random access or element swaps.
 *
 * @tparam Iterator A bidirectional iterator type that supports dereference, increment, and decrement.
 * @param begin Iterator to the beginning of the range to sort.
 * @param end Iterator to one past the end of the range to sort.
 *
 * @note This function requires that the iterator supports bidirectional access (e.g., list or vector).
 *
 * @throw std::runtime_error If dereferencing an invalid iterator.
 *
 * @complexity
 * Time Complexity: O(n^2) in the worst case (reverse-sorted input),
 *                  O(n) in the best case (already sorted).
 * Space Complexity: O(1) — In-place sorting using only a temporary copy of one element.
 */
template <typename Iterator>
void insertSort(Iterator begin, Iterator end)
{
    if (begin == end || std::next(begin) == end)
    {
        return;  // Empty or single element
    }

    for (Iterator it1 = std::next(begin); it1 != end; ++it1)
    {
        auto key = *it1;
        Iterator it2 = it1;

        while (it2 != begin && key < *std::prev(it2))
        {
            *it2 = *std::prev(it2);
            --it2;
        }

        *it2 = key;  // Insert key into correct position
    }
}