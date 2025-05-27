#pragma once

#include <initializer_list>  // for std::initializer_list
#include <stdexcept>         // for std::out_of_range

/**
 * @brief A fixed-size array that provides bounds-checked element access and appending functionality.
 *
 * This class represents a statically-sized array with the ability to append elements
 * and perform bounds-checked access to elements. If the array is full or an index is out
 * of bounds, exceptions are thrown.
 *
 * @tparam T The type of elements in the array.
 * @tparam size The number of elements in the array.
 */
template <typename T, int size>
class StaticArray
{
public:
    using value_type = T;
    using iterator = T*;

    // Default constructor - Initializes all elements to default value of T (e.g., 0 for int)
    StaticArray()
    {
        for (int i = 0; i < size; ++i)
        {
            mData[i] = T();
        }
    }

    // Constructor to initialize with an initializer list
    StaticArray(std::initializer_list<T> list)
    {
        int i = 0;
        for (auto& item : list)
        {
            if (i < size)
            {
                mData[i++] = item;
            }
            else
            {
                throw std::out_of_range("Initializer list exceeds static array size");
            }
        }
    }

    /**
     * @brief Access an element at the given index.
     *
     * @param index The index of the element to access.
     * @return A reference to the element at the specified index.
     *
     * @throws std::out_of_range if the index is out of bounds.
     *
     * @complexity
     * - Time Complexity: O(1) (direct array access).
     * - Space Complexity: O(1) (no additional memory is used).
     */
    T& operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of bounds in StaticArray::operator[]");
        }
        return mData[index];
    }

    /**
     * @brief Access a constant element at the given index (const version).
     *
     * @param index The index of the element to access.
     * @return A constant reference to the element at the specified index.
     *
     * @throws std::out_of_range if the index is out of bounds.
     *
     * @complexity
     * - Time Complexity: O(1) (direct array access).
     * - Space Complexity: O(1) (no additional memory is used).
     */
    const T& operator[](int index) const
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of bounds in StaticArray::operator[]");
        }
        return mData[index];
    }

    /**
     * @brief Compares two StaticArray objects for equality.
     *
     * This operator checks if two StaticArray objects contain the same elements at each index.
     *
     * @param other The StaticArray object to compare to.
     * @return True if all elements are equal, false otherwise.
     *
     * @throws std::out_of_range if the size of the StaticArray is mismatched (inconsistent use of template
     * specialization).
     *
     * @complexity
     * - Time Complexity: O(n), where n is the number of elements in the array (`size`). Each element is compared once.
     * - Space Complexity: O(1), as no additional memory is allocated besides the local variables for the loop.
     */
    bool operator==(const StaticArray<T, size>& other) const
    {
        for (int i = 0; i < size; ++i)
        {
            if (mData[i] != other.mData[i])
            {
                return false;  // If any elements differ, return false
            }
        }
        return true;  // All elements are equal
    }

    /**
     * @brief Returns an iterator pointing to the first element in the array.
     *
     * This method returns a pointer to the first element in the dynamic array.
     * It can be used to start traversing the array from the beginning.
     *
     * @return A pointer to the first element of the array.
     */
    T* begin()
    {
        return mData;
    }
    const T* begin() const
    {
        return mData;
    }

    /**
     * @brief Returns an iterator pointing past the last element in the array.
     *
     * This method returns a pointer to the element one past the last element
     * in the array. This is used as a sentinel value to mark the end of the array.
     *
     * @return A pointer to one past the last element of the array.
     */
    T* end()
    {
        return mData + size;
    }
    const T* end() const
    {
        return mData + size;
    }

    /**
     * @brief Get the size of the array (static size).
     *
     * @return The total number of elements the array can hold (size).
     */
    [[nodiscard]] constexpr int getSize() const noexcept
    {
        return size;
    }

    /**
     * @brief Checks if the container has no elements.
     *
     * @return True if the container is empty, false otherwise.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept
    {
        return size == 0;
    }

private:
    T mData[size];  ///< The actual data of the static array
};
