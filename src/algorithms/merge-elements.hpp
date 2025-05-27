#pragma once

#include <useful-concepts.hpp>
#include <static-array.hpp>

/**
 * @brief Merges two containers in sorted order and returns the result.
 *
 * This function merges two containers that satisfy the HasCustomBeginEnd and HasGetSize concepts,
 * assuming both containers are sorted in ascending order. It combines them into a single container
 * with all elements in sorted order.
 *
 * @tparam T The container type.
 * @param array1 The first container to merge.
 * @param array2 The second container to merge.
 *
 * @return The merged container containing all elements from array1 and array2, in sorted order.
 *
 * @note The input containers should be sorted before calling this function.
 *
 * @complexity Time complexity: O(n + m), where n is the size of array1 and m is the size of array2.
 *              This is because each element from both arrays is processed exactly once.
 *
 * @complexity Space complexity: O(n + m), where n is the size of array1 and m is the size of array2.
 *              This is because a new container of size n + m is created for the result.
 */
template <typename T>
[[nodiscard]] T mergeElements(
    const T& array1, const T& array2) requires HasCustomBeginEnd<T>&& HasGetSize<T>&& HasAppend<T>
{
    const int size1 = array1.getSize();
    const int size2 = array2.getSize();

    T result(size1 + size2);

    auto i = array1.begin();
    auto j = array2.begin();

    // Merge elements from both arrays in sorted order
    while (i != array1.end() && j != array2.end())
    {
        if (*i < *j)
        {
            result.append(*i);
            ++i;
        }
        else
        {
            result.append(*j);
            ++j;
        }
    }

    // Append remaining elements from array1
    while (i != array1.end())
    {
        result.append(*i);
        ++i;
    }

    // Append remaining elements from array2
    while (j != array2.end())
    {
        result.append(*j);
        ++j;
    }

    return result;
}

/**
 * @brief Specialization of mergeElements for StaticArray.
 *
 * This specialization merges two StaticArrays into a new StaticArray in sorted order.
 * It is optimized for StaticArray types that have known sizes at compile time.
 *
 * @tparam T The type of elements in the StaticArray.
 * @tparam N1 The size of the first StaticArray.
 * @tparam N2 The size of the second StaticArray.
 * @param staticArray1 The first StaticArray to merge.
 * @param staticArray2 The second StaticArray to merge.
 *
 * @return A StaticArray containing the merged elements of staticArray1 and staticArray2, in sorted order.
 *
 * @complexity Time complexity: O(n + m), where n is the size of staticArray1 and m is the size of staticArray2.
 *              Similar to the general mergeElements function, since each element is processed once.
 *
 * @complexity Space complexity: O(n + m), where n is the size of staticArray1 and m is the size of staticArray2.
 *              A new StaticArray of size n + m is created.
 */
template <typename T, size_t N1, size_t N2>
[[nodiscard]] StaticArray<T, N1 + N2> mergeElements(
    const StaticArray<T, N1>& staticArray1, const StaticArray<T, N2>& staticArray2)
{
    StaticArray<T, N1 + N2> result;

    auto i = staticArray1.begin();
    auto j = staticArray2.begin();
    auto k = result.begin();

    // Merge elements from both arrays in sorted order
    while (i != staticArray1.end() && j != staticArray2.end())
    {
        if (*i < *j)
        {
            *k = *i;
            ++i;
        }
        else
        {
            *k = *j;
            ++j;
        }
        ++k;
    }

    // Append remaining elements from staticArray1
    while (i != staticArray1.end())
    {
        *k = *i;
        ++i;
        ++k;
    }

    // Append remaining elements from staticArray2
    while (j != staticArray2.end())
    {
        *k = *j;
        ++j;
        ++k;
    }

    return result;
}
