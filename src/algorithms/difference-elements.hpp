#pragma once

#include <linear-search.hpp>
#include <useful-concepts.hpp>

// TODO: Improve efficience

/**
 * @brief Computes the difference of two containers, returning elements that are in `container1` but not in
 * `container2`.
 *
 * @tparam T The type of the container, which must satisfy the requirements:
 *           - HasCustomBeginEnd<T>: The container provides custom begin and end iterators.
 *           - HasAppend<T>: The container provides an append method.
 * @param container1 The first container.
 * @param container2 The second container.
 * @return A new container containing the elements from `container1` that are not present in `container2`.
 *
 * @note This function performs a linear search to check for elements from `container1` that are missing from
 * `container2`, making it more efficient for small containers or when the overlap is minimal.
 *
 * ### Time Complexity
 * - **Worst-case:** O(n1 * n2), where `n1` is the size of `container1` and `n2` is the size of `container2`.
 *   - For each element in `container1` (outer loop, O(n1)), a linear search is performed over `container2` (O(n2)).
 *   - In the worst case, this results in O(n1 * n2).
 * - **Best-case:** O(n1), when all elements in `container1` are not present in `container2` and no linear searches are
 * needed.
 *
 * ### Space Complexity
 * - **Worst-case:** O(n1), where `n1` is the size of `container1`. This occurs when no elements from `container1` are
 * found in `container2`, and all elements from `container1` are appended to the result.
 * - **Best-case:** O(1), when all elements in `container1` are found in `container2`, and the result container remains
 * empty.
 */
template <typename T>
[[nodiscard]] T differenceElements(
    const T& container1, const T& container2) requires HasCustomBeginEnd<T>&& HasAppend<T>
{
    T result;

    // First loop: Iterate over container1 to find elements that are not in container2
    for (auto it = container1.begin(); it != container1.end(); it++)
    {
        // Perform linear search in container2 to check if the element is present
        // In the worst case, this search will take O(n2), where n2 is the size of container2.
        // For each element in container1 (total of n1 elements), a linear search is done on container2 (size n2).
        // This results in a total time complexity of O(n1 * n2).
        const bool valueIsPresent = (linearSearch(container2.begin(), container2.end(), *it) != container2.end());

        // If the element is found in container2, skip it; otherwise, add it to the result
        if (valueIsPresent)
        {
            continue;  // Skip appending if the element is found in container2
        }

        result.append(*it);  // Append element to the result container
    }

    return result;
}
