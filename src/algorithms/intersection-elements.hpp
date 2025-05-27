#pragma once

#include <linear-search.hpp>
#include <useful-concepts.hpp>

// TODO: Improve efficience

/**
 * @brief Computes the intersection of two containers, returning elements that are present in both containers.
 *
 * @tparam T The type of the container, which must satisfy the requirements:
 *           - HasCustomBeginEnd<T>: The container provides custom begin and end iterators.
 *           - HasAppend<T>: The container provides an append method.
 * @param container1 The first container.
 * @param container2 The second container.
 * @return A new container containing the intersection of `container1` and `container2`.
 *
 * @note This function performs a linear search to check for matching elements, making it most efficient for
 *       small containers or containers with relatively few common elements.
 *
 * ### Time Complexity
 * - **Worst-case:** O(n1 * n2), where `n1` is the size of `container1` and `n2` is the size of `container2`.
 *   - For each element in `container1` (outer loop, O(n1)), a linear search is performed over `container2` (O(n2)).
 * - **Best-case:** O(n1), if all elements in `container1` are found in `container2`, as the loop continues
 *   without appending any elements after finding the matches.
 *
 * ### Space Complexity
 * - **Worst-case:** O(n1), where `n1` is the size of `container1`, if all elements in `container1` are present in
 * `container2` and no duplicates are found. The space complexity is proportional to the number of elements in the
 * result container.
 * - **Best-case:** O(1), if no elements from `container1` are found in `container2`, the result container remains
 * empty.
 */
template <typename T>
[[nodiscard]] T intersectionElements(
    const T& container1, const T& container2) requires HasCustomBeginEnd<T>&& HasAppend<T>
{
    T result;

    // First loop: Iterate over container1 to find common elements with container2
    for (auto it = container1.begin(); it != container1.end(); it++)
    {
        // Perform linear search in container2 to check if the element is present
        // In the worst case, this search will take O(n2), where n2 is the size of container2.
        // For each element in container1 (total of n1 elements), a linear search is done on container2 (size n2).
        // This results in a total time complexity of O(n1 * n2).
        const bool valueIsPresent = (linearSearch(container2.begin(), container2.end(), *it) != container2.end());

        // If the element is found in container2, add it to the result
        if (!valueIsPresent)
        {
            continue;  // Skip appending if the element is not found in container2
        }

        result.append(*it);  // Append element to the result container
    }

    return result;
}
