#pragma once

#include <unordered_map>
#include <useful-concepts.hpp>

/**
 * @brief Removes duplicate elements from a container, keeping only the first occurrence of each value.
 *
 * This function iterates through the given container and removes any duplicate elements, ensuring
 * that only the first occurrence of each value is kept. The container must support custom begin
 * and end iterators as well as a method to get its size. The erase operation may cause elements to shift
 * in dynamic containers such as vectors or arrays.
 *
 * @tparam T The type of the container, which must satisfy the requirements:
 *           - HasCustomBeginEnd<T>: The container provides custom begin and end iterators.
 *           - HasGetSize<T>: The container provides a method to get the size of the container.
 *
 * @param container The container from which duplicate elements will be removed.
 *
 * @note This function uses an unordered map to track seen elements and removes duplicates in linear time,
 *       making it efficient for containers that support fast `erase` operations. However, for dynamic arrays
 *       or vectors, the `erase` operation might trigger shifting of elements, which could impact performance.
 *
 * ### Time Complexity
 * - **Worst-case:** O(n), where `n` is the size of the container. Each element is visited once, and
 *   the insertion and lookup operations in the unordered map are on average O(1).
 * - **Note:** If the container involves shifting elements during `erase`, the overall time complexity could
 *   degrade to O(n^2) in the worst case for dynamic arrays/vectors, where n is the number of elements.
 *
 * ### Space Complexity
 * - **Worst-case:** O(n), where `n` is the size of the container, as the unordered map stores
 *   all unique elements from the container.
 * - **Best-case:** O(n), if all elements are unique, as the unordered map will store each element.
 */
template <typename T>
void deleteDuplicates(T& container) requires HasCustomBeginEnd<T>&& HasGetSize<T>
{
    if (container.getSize() <= 1)
    {
        return;
    }

    std::unordered_map<typename T::value_type, bool> seen;

    auto it = container.begin();
    ssize_t pos = 0;
    while (it != container.end())
    {
        const typename T::value_type& value = *it;
        if (seen[value])
        {
            it = container.erase(pos);
        }
        else
        {
            seen[value] = true;
            it++;
            pos++;
        }
    }
}
