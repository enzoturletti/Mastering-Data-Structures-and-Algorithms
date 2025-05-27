#pragma once

/**
 * @brief Finds the iterator pointing to the maximum element in a range of elements.
 *
 * This function performs a linear search to find the maximum element in the range
 * defined by the iterators `begin` and `end`. It compares each element sequentially
 * and returns an iterator pointing to the element with the highest value.
 *
 * @tparam Iterator The type of the iterator, which should support dereferencing
 *                  and comparison operations.
 *
 * @param begin The iterator pointing to the first element of the range.
 * @param end The iterator pointing to one past the last element of the range.
 *
 * @return Iterator An iterator pointing to the maximum element in the range.
 *                   If the range is empty (`begin == end`), returns the `end` iterator.
 *
 * @note **Time Complexity**:
 * - Best case: O(1) when the first element is the maximum.
 * - Worst case: O(n) when the maximum element is at the end of the range,
 *   where `n` is the number of elements in the range (`end - begin`).
 * - Average case: O(n), as all elements are visited in the general case.
 *
 * @note **Space Complexity**:
 * - O(1) because this function uses only a constant amount of extra space
 *   for the iterators.
 */
template <typename Iterator>
Iterator maxElement(Iterator begin, Iterator end)
{
    // Return 'end' iterator if the range is empty
    if (begin == end)
    {
        return end;
    }

    // Initialize the iterator to the maximum element with the first element
    Iterator maxValue = begin;

    // Iterate over each element starting from the second
    for (Iterator i = begin; i != end; ++i)
    {
        // Update the iterator to the maximum element if a larger value is found
        if (*i > *maxValue)
        {
            maxValue = i;
        }
    }

    // Return the iterator to the maximum element
    return maxValue;
}

/**
 * @brief Finds the iterator pointing to the minimum element in a range of elements.
 *
 * This function performs a linear search to find the minimum element in the range
 * defined by the iterators `begin` and `end`. It compares each element sequentially
 * and returns an iterator pointing to the element with the lowest value.
 *
 * @tparam Iterator The type of the iterator, which should support dereferencing
 *                  and comparison operations.
 *
 * @param begin The iterator pointing to the first element of the range.
 * @param end The iterator pointing to one past the last element of the range.
 *
 * @return Iterator An iterator pointing to the minimum element in the range.
 *                   If the range is empty (`begin == end`), returns the `end` iterator.
 *
 * @note **Time Complexity**:
 * - Best case: O(1) when the first element is the minimum.
 * - Worst case: O(n) when the minimum element is at the end of the range,
 *   where `n` is the number of elements in the range (`end - begin`).
 * - Average case: O(n), as all elements are visited in the general case.
 *
 * @note **Space Complexity**:
 * - O(1) because this function uses only a constant amount of extra space
 *   for the iterators.
 */
template <typename Iterator>
Iterator minElement(Iterator begin, Iterator end)
{
    // Return 'end' iterator if the range is empty
    if (begin == end)
    {
        return end;
    }

    // Initialize the iterator to the minimum element with the first element
    Iterator minValue = begin;

    // Iterate over each element starting from the second
    for (Iterator i = begin; i != end; ++i)
    {
        // Update the iterator to the minimum element if a smaller value is found
        if (*i < *minValue)
        {
            minValue = i;
        }
    }

    // Return the iterator to the minimum element
    return minValue;
}
