#pragma once

/**
 * @brief Reverses the elements in the range [begin, end).
 *
 * This function takes two iterators, `begin` and `end`, and reverses the order of elements
 * in the range between these iterators. It uses the two-pointer approach, starting from the
 * beginning (`low`) and end (`high`) of the range, and swapping the elements until the two
 * pointers meet in the middle.
 *
 * @tparam Iterator The iterator type. It can be any type that supports dereferencing and incrementing.
 *
 * @param begin The iterator pointing to the first element of the range.
 * @param end The iterator pointing to one past the last element of the range (typically `array + size`).
 *
 * @note This function works on any iterable container or raw pointer range.
 *
 * @complexity
 * - Time Complexity: O(n), where n is the number of elements in the range. The function iterates through the range
 * once.
 * - Space Complexity: O(1), because the function uses a constant amount of extra space (only one temporary variable for
 * swapping).
 */
template <typename Iterator>
void reverseElements(Iterator begin, Iterator end)
{
    // If the range is empty (begin == end), there's nothing to reverse.
    if (begin == end)
    {
        return;
    }

    // Iterator pointing to the first element of the range
    Iterator low = begin;

    // Iterator pointing to the last element of the range (end-1, because end is past the last element)
    Iterator high = end - 1;

    // While the low pointer is still less than the high pointer, swap elements.
    while (low < high)
    {
        // Store the value at the low pointer in a temporary variable
        auto auxiliarValue = *low;

        // Swap the values at low and high iterators
        *low = *high;

        // Set the value of the high iterator to the original value at low
        *high = auxiliarValue;

        // Move the low iterator forward
        low++;

        // Move the high iterator backward
        high--;
    }
}
