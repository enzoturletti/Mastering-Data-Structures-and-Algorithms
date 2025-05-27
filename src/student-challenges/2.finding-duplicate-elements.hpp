#pragma once

#include <max-element.hpp>
#include <optional>
#include <unordered_map>
#include <useful-concepts.hpp>

/**
 * @brief Finds the duplicate elements in a container.
 *
 * This function identifies all elements that appear more than once in a container.
 * It uses a hash table to track the occurrences of each element and returns an optional
 * container that contains all the elements that appear multiple times. If no duplicates
 * are found, it returns an empty result (std::nullopt).
 *
 * @tparam T The container type (e.g., DynamicArray, StaticArray).
 * @tparam Iterator The iterator type used to traverse the container.
 *
 * @param begin Iterator pointing to the first element in the range.
 * @param end Iterator pointing to one past the last element in the range.
 *
 * @return std::optional<T> A container containing the duplicate elements, or
 *         std::nullopt if no duplicates are found.
 *
 * @note **Time Complexity**:
 * - Best case: O(n) when there are no duplicates or duplicates are found early,
 *   where `n` is the number of elements in the container.
 * - Worst case: O(n) when all elements are checked, and no duplicates are skipped.
 *
 * @note **Space Complexity**:
 * - O(n) due to the hash table storing the counts of each element, where `n` is
 *   the number of unique elements in the container.
 */
template <typename T, typename Iterator>
[[nodiscard]] std::optional<T> findingDuplicateElementsInContainer(
    Iterator begin, Iterator end) requires HasGetSize<T>&& HasAppend<T>
{
    if (begin == end)
    {
        return std::nullopt;  // Return nullopt if the container is empty.
    }

    // Initialize the result container to store duplicate elements
    T result;

    // Create a hash table to store element counts
    std::unordered_map<typename T::value_type, int> hashTable;

    // Loop through the container and populate the hash table with element counts
    for (auto it = begin; it != end; ++it)
    {
        hashTable[*it]++;  // Increment the count for the current element
    }

    // Loop through the hash table to find elements with count >= 2 (duplicates)
    for (auto [key, value] : hashTable)
    {
        if (value >= 2)
        {
            result.append(key);  // Append the element to the result container
        }
    }

    // If no duplicates were found, return nullopt
    if (result.getSize() == 0)
    {
        return std::nullopt;
    }

    // Return the container with duplicates
    return result;
}