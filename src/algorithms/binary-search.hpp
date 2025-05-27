#pragma once

/**
 * @brief Performs a binary search for a value within a sorted range of elements.
 *
 * This function performs a binary search for the given value within the specified range
 * using the provided iterators. The range is assumed to be sorted in ascending order.
 *
 * @param begin Iterator pointing to the first element of the range.
 * @param end Iterator pointing to one past the last element of the range.
 * @param value The value to search for.
 * @return Iterator pointing to the found element, or `end` if the element is not found.
 *
 * @note
 * Time Complexity:
 *   - **O(log N)**, where `N` is the number of elements in the range.
 *     Binary search works by repeatedly halving the search space.
 *     Each comparison eliminates half of the remaining elements, leading to a logarithmic time complexity.
 *
 * Space Complexity:
 *   - **O(1)**, constant space complexity.
 *     The algorithm only uses a few iterators and variables for tracking the search bounds (low, high, mid),
 *     regardless of the size of the input range. Thus, no additional space is used that scales with the input.
 */
template <typename Iterator, typename T>
Iterator binarySearch(Iterator begin, Iterator end, const T& value)
{
    if (begin == end)
    {
        return end;  // Return end iterator immediately
    }

    Iterator low = begin;
    Iterator high = end - 1;

    while (low <= high)
    {
        // Calculate the middle iterator
        Iterator mid = low + (std::distance(low, high)) / 2;

        // Compare the middle element with the target value
        if (*mid == value)
        {
            return mid;  // Element found
        }
        else if (*mid < value)
        {
            if (mid == high)
                break;
            low = mid + 1;  // Search in the right half
        }
        else
        {
            if (mid == low)
                break;
            high = mid - 1;  // Search in the left half
        }
    }

    return end;  // Element not found, return end iterator
}