#pragma once

#include <linear-search.hpp>
#include <useful-concepts.hpp>

// TODO: Improve efficience

/**
 * @brief Computes the union of two containers, adding elements from the second container to the first
 *        only if they are not already present.
 *
 * @tparam T The type of the container, which must satisfy the requirements:
 *           - HasCustomBeginEnd<T>: The container provides custom begin and end iterators.
 *           - HasGetSize<T>: The container provides a method to get its size.
 *           - HasAppend<T>: The container provides an append method.
 * @param container1 The first container.
 * @param container2 The second container.
 * @return A new container containing the union of `container1` and `container2`.
 *
 * @note This function performs a linear search to check for duplicates, so it is most efficient for
 *       small containers or containers with relatively few overlapping elements.
 *
 * ### Time Complexity
 * - **Worst-case:** O(n1² + n1 * n2 + n2²), where `n1` is the size of `container1` and `n2` is the size of
 * `container2`.
 *   - The first loop performs O(n1²) linear searches over `result`.
 *   - The second loop performs O(n1 * n2 + n2²) linear searches over `result`.
 * - **Best-case:** O(n2), if all elements in `container2` are already present in `container1`, as the loop continues
 * without appending any elements.
 *
 * ### Space Complexity
 * - **Worst-case:** O(n1 + n2), where `n1` is the size of `container1` and `n2` is the size of `container2`.
 *   - This occurs when no elements in `container2` are present in `container1`, requiring all elements to be appended.
 * - **Best-case:** O(n1), if all elements in `container2` are already present in `container1`, as no new elements are
 * appended.
 */
template <typename T>
[[nodiscard]] T unionElements(const T& container1, const T& container2) requires HasCustomBeginEnd<T>&& HasAppend<T>
{
    T result;

    // First loop: Iterates over container1 to add elements to result
    for (auto it = container1.begin(); it != container1.end(); it++)
    {
        // Perform linear search in 'result' to check if the element is already present
        // In the worst case, the search complexity will be O(n1) since 'result' grows as we add elements.
        // For the first element, linear search takes 1 operation, for the second element it takes 2 operations,
        // and so on, up to n1 operations for the nth element. Hence the total complexity for this loop is:
        // 1 + 2 + 3 + ... + n1 = (n1 * (n1 + 1)) / 2 = O(n1^2).
        const bool valueIsPresent = (linearSearch(result.begin(), result.end(), *it) != result.end());
        if (valueIsPresent)
        {
            continue;  // Skip appending if the element is already in result
        }

        result.append(*it);  // Append element to result (assuming not cost)
    }

    // Second loop: Iterates over container2 to add elements to result
    for (auto it = container2.begin(); it != container2.end(); it++)
    {
        // Perform linear search in 'result' to check if the element is already present.
        // Here, 'result' has at most n1 elements from the first loop.
        // For the first element of container2, we perform n1 searches, for the second element we perform (n1 + 1)
        // searches, and so on. In the worst case, the total number of linear searches for this loop is: n1 + (n1+1) +
        // (n1+2) + ... + (n1 + n2) = n2 * n1 + (n2/2)*(n2+1). So the complexity for this loop is O(n2 * n1 + n2^2).
        const bool valueIsPresent = (linearSearch(result.begin(), result.end(), *it) != result.end());
        if (valueIsPresent)
        {
            continue;  // Skip appending if the element is already in result
        }

        result.append(*it);  // Append element to result (assuming not cost)
    }

    return result;
}
