#pragma once

/**
 * @brief Enum to specify the sorting order.
 */
enum class SortOrder
{
    Ascending,  ///< Checks for non-decreasing order.
    Descending  ///< Checks for non-increasing order.
};

/**
 * @brief Checks if the elements in the range [begin, end) are sorted according to the specified order.
 *
 * This function iterates through the range and compares each element with the next one.
 * It checks whether the range is sorted in non-decreasing (ascending) or non-increasing (descending) order,
 * based on the given `order` parameter.
 *
 * @tparam Iterator Type of the iterator (can be raw pointer or any container iterator).
 * @param begin Iterator pointing to the start of the range.
 * @param end Iterator pointing to the end of the range.
 * @param order The order in which the range should be sorted (ascending or descending).
 * @return `true` if the range is sorted in the specified order, `false` otherwise.
 *
 * @complexity Time complexity: O(n), where n is the number of elements in the range.
 *               The function iterates through the range once and performs a comparison at each step.
 * @complexity Space complexity: O(1), since the function uses only a constant amount of extra space.
 */
template <typename Iterator>
bool isSorted(Iterator begin, Iterator end, SortOrder order = SortOrder::Ascending)
{
    // Return true for empty or single-element ranges
    if (begin == end || begin + 1 == end)
    {
        return true;
    }

    // Iterate over the range and check if the elements are in the specified order
    for (Iterator i = begin; i != end - 1; ++i)
    {
        if (order == SortOrder::Ascending)
        {
            if (*i > *(i + 1))  // Compare for ascending order
            {
                return false;  // If the current element is greater than the next, return false
            }
        }
        else if (order == SortOrder::Descending)
        {
            if (*i < *(i + 1))  // Compare for descending order
            {
                return false;  // If the current element is smaller than the next, return false
            }
        }
    }

    return true;  // Return true if no violations of the sorted order were found
}
