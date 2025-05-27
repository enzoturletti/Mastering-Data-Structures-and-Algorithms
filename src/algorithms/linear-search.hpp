#pragma once

/**
 * @brief Performs a linear search for a value in a range of elements.
 *
 * This function searches for a specific value in the range defined by the
 * iterator `begin` and `end`. It checks each element in the range sequentially
 * and returns the iterator to the first occurrence of the value.
 * If the value is not found, it returns the `end` iterator to indicate the absence
 * of the value.
 *
 * @tparam Iterator The type of the iterator, which should support dereferencing
 *                  and comparison with the value type.
 * @tparam T The type of the value being searched for. This type should be comparable
 *           with the elements in the range.
 *
 * @param begin The iterator pointing to the first element of the range.
 * @param end The iterator pointing to one past the last element of the range.
 * @param value The value to search for.
 *
 * @return Iterator An iterator pointing to the first occurrence of the value
 *                  in the range, or the `end` iterator if the value is not found.
 *
 * @note **Time Complexity**:
 * - Best case: O(1) when the first element is the value being searched for.
 * - Worst case: O(n) when the value is at the end of the range or not present at all,
 *   where `n` is the number of elements in the range (`end - begin`).
 * - Average case: (possible of cases / number of cases) = (1+2+..+n) / n = (n + 1) / 2 -> O(n)
 *
 * @note **Space Complexity**:
 * - O(1) because this function only uses a constant amount of extra space for the iterator.
 */
template <typename Iterator, typename T>
Iterator linearSearch(Iterator begin, Iterator end, const T& value)
{
    // Iterate over each element in the range
    for (Iterator i = begin; i != end; ++i)
    {
        // Check if the current element is equal to the search value
        if (value == *i)
        {
            return i;  // Return iterator to the found value
        }
    }

    // Return 'end' iterator if the value was not found
    return end;
}
