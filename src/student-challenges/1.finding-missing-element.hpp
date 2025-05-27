#pragma once

#include <max-element.hpp>
#include <optional>
#include <useful-concepts.hpp>

/**
 * @brief Finds the first missing element in a sorted container.
 *
 * This function identifies the first missing integer in a sorted container where elements
 * are expected to increment by 1. If no missing element is found, it returns `std::nullopt`.
 *
 * @tparam T The container type, which must have a member type `value_type` of `int`.
 * @tparam Iterator The iterator type used to traverse the container.
 * @param begin The iterator pointing to the beginning of the container.
 * @param end The iterator pointing to the end of the container.
 * @return std::optional<typename T::value_type> The first missing integer if found, or `std::nullopt` if none are
 * missing.
 *
 * @note This function requires that the input container is sorted in ascending order.
 *
 * ### Time Complexity
 * - **O(n)**: The function iterates through the container once, comparing adjacent elements. (worst case)
 *
 * ### Space Complexity
 * - **O(1)**: The function uses a constant amount of additional memory regardless of the input size.
 */
template <typename T, typename Iterator>
[[nodiscard]] std::optional<typename T::value_type> findingSimpleMissingIntInSortedContainer(
    Iterator begin, Iterator end) requires HasValueTypeInt<T>
{
    if (begin == end)
    {
        return std::nullopt;
    }

    for (auto it = begin; it != (end - 1); ++it)
    {
        typename T::value_type expectedNextValue = *it + 1;
        typename T::value_type currentNextValue = *(it + 1);

        if (expectedNextValue != currentNextValue)
        {
            return expectedNextValue;
        }
    }

    return std::nullopt;
}

/**
 * @brief Finds all missing elements in a sorted container.
 *
 * This function identifies all missing integers in a sorted container where elements
 * are expected to increment by 1. If no missing elements are found, it returns `std::nullopt`.
 *
 * @tparam T The container type, which must have a member type `value_type` of `int`.
 *           The container must also support an `append` method and a method to check if it is empty (`isEmpty`).
 * @tparam Iterator The iterator type used to traverse the container.
 * @param begin The iterator pointing to the beginning of the container.
 * @param end The iterator pointing to the end of the container.
 * @return std::optional<T> A container of all missing integers if any are found, or `std::nullopt` if none are missing.
 *
 * @note This function assumes that the input container is sorted in ascending order and contains unique integers.
 *
 * ### Time Complexity
 * - **O(n+m)**: The function iterates through the container once, checking gaps between consecutive elements.
 *
 * ### Space Complexity
 * - **O(m)**: Additional space is used for the container holding missing elements, where \(m\) is the number of missing
 * elements.
 */
template <typename T, typename Iterator>
[[nodiscard]] std::optional<T> findingMultipleMissingIntsInSortedContainer(
    Iterator begin, Iterator end) requires HasValueTypeInt<T>&& HasAppend<T>
{
    T result;

    if (begin == end)
    {
        return std::nullopt;
    }

    for (auto it = begin; it != (end - 1); ++it)
    {
        typename T::value_type expectedNextValue = *it + 1;
        typename T::value_type currentNextValue = *(it + 1);

        // Handle duplicates
        if (*it == currentNextValue)
        {
            continue;
        }

        while (expectedNextValue != currentNextValue)
        {
            result.append(expectedNextValue);
            expectedNextValue++;
        }
    }

    if (result.isEmpty())
    {
        return std::nullopt;
    }

    return result;
}

template <typename T, typename Iterator>
[[nodiscard]] std::optional<T> findingMultipleMissingIntInContainer(
    Iterator begin, Iterator end) requires HasValueTypeInt<T>&& HasAppend<T>
{
    T result;

    if (begin == end)
    {
        return std::nullopt;
    }

    int low = *minElement(begin, end);
    int high = *maxElement(begin, end);

    std::cout << "low: " << low << std::endl;
    std::cout << "high: " << high << std::endl;

    // Init HashTable
    auto hashTable = T(high - low + 1);
    for (int i = low; i <= high; i++)
    {
        hashTable.append(0);
    }

    // Count elements between low and high
    for (auto it = begin; it != end; ++it)
    {
        auto hash = (*it) - low;  // The index 0 correspond to the low value.
        hashTable[hash]++;
    }

    // Save the values which it count is zero.
    for (int i = 0; i <= (high - low); i++)
    {
        if (hashTable[i] == 0)
        {
            result.append(i + low);
        }
    }

    if (result.isEmpty())
    {
        return std::nullopt;
    }

    return result;
}