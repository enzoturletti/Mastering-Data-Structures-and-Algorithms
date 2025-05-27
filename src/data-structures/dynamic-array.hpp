#pragma once

#include <initializer_list>  // for std::initializer_list
#include <stdexcept>         // for std::out_of_range

template <typename T>
class DynamicArray
{
public:
    using value_type = T;
    using iterator = T*;

    DynamicArray() : mSize(0), mCapacity(getDefaultCapacity()), mData(new T[mCapacity])
    {
    }

    DynamicArray(int initialCapacity) : mSize(0), mCapacity(initialCapacity), mData(new T[mCapacity])
    {
    }

    // Constructor to initialize with an initializer list
    DynamicArray(std::initializer_list<T> list) : mSize(list.size()), mCapacity(list.size()), mData(new T[mCapacity])
    {
        int i = 0;
        for (auto& item : list)
        {
            mData[i++] = item;
        }
    }

    ~DynamicArray()
    {
        delete[] mData;  // Free the dynamically allocated memory
    }

    // Copy constructor
    DynamicArray(const DynamicArray& other) : mSize(other.mSize), mCapacity(other.mCapacity), mData(new T[mCapacity])
    {
        for (int i = 0; i < mSize; ++i)
        {
            mData[i] = other.mData[i];  // Copy the elements
        }
    }

    // Copy assignment operator
    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this == &other)
        {
            return *this;  // Return *this to avoid self-assignment
        }

        // Release any existing resources
        delete[] mData;

        mCapacity = other.mCapacity;
        mSize = other.mSize;

        mData = new T[mCapacity];  // Allocate new memory
        for (int i = 0; i < mSize; ++i)
        {
            mData[i] = other.mData[i];  // Copy the elements
        }

        return *this;
    }

    // Move constructor
    DynamicArray(DynamicArray&& other) noexcept : mData(other.mData), mCapacity(other.mCapacity), mSize(other.mSize)
    {
        // Transfer ownership of the resources
        other.mData = nullptr;
        other.mCapacity = 0;
        other.mSize = 0;
    }

    // Move assignment operator
    DynamicArray& operator=(DynamicArray&& other) noexcept
    {
        if (this == &other)
        {
            return *this;  // Return *this to avoid self-assignment
        }

        // Release any existing resources
        delete[] mData;

        // Transfer ownership of the resources
        mData = other.mData;
        mCapacity = other.mCapacity;
        mSize = other.mSize;

        // Set the other object to a valid state
        other.mData = nullptr;
        other.mCapacity = 0;
        other.mSize = 0;

        return *this;
    }

    /**
     * @brief Returns an iterator pointing to the first element in the array.
     *
     * This method returns a pointer to the first element in the dynamic array.
     * It can be used to start traversing the array from the beginning.
     *
     * @return A pointer to the first element of the array.
     */
    iterator begin()
    {
        return mData;
    }
    iterator begin() const
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
    iterator end()
    {
        return mData + mSize;
    }
    iterator end() const
    {
        return mData + mSize;
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
        if (index < 0 || index >= mSize)
        {
            throw std::out_of_range("Index out of bounds in DynamicArray::operator[]");
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
        if (index < 0 || index >= mSize)
        {
            throw std::out_of_range("Index out of bounds in DynamicArray::operator[]");
        }
        return mData[index];
    }

    /**
     * @brief Compares two DynamicArray objects for equality.
     *
     * This operator checks if two DynamicArray instances are equal by comparing their
     * sizes and the elements in the arrays. The arrays are considered equal if they
     * have the same size and each corresponding element is equal.
     *
     * @param other The DynamicArray to compare with the current array.
     * @return True if the arrays are equal (same size and same elements), false otherwise.
     *
     * @throws None
     *
     * @complexity
     * - Time Complexity: O(n), where n is the size of the arrays (each element is compared).
     * - Space Complexity: O(1), as no additional space is used besides temporary variables.
     */
    bool operator==(const DynamicArray& other) const
    {
        // First, check if the sizes are the same
        if (mSize != other.mSize)
        {
            return false;
        }

        // Then, compare each element in the array
        for (int i = 0; i < mSize; ++i)
        {
            if (mData[i] != other.mData[i])
            {
                return false;
            }
        }

        // If both checks passed, the arrays are equal
        return true;
    }

    /**
     * @brief Append an item to the array.
     *
     * Adds a new element to the end of the array. If the array is full,
     * the capacity is doubled, and the array is resized automatically.
     *
     * @param item The item to append to the array.
     *
     * @complexity
     * - Time Complexity:
     *   - O(1) for most cases when there is space in the array.
     *   - O(n) for resizing when the array is full, where n is the current capacity.
     * - Space Complexity: 0(1) or O(n) if takes place resizing, where n is the new capacity.
     */
    void append(const T& item)
    {
        if (mSize == mCapacity)
        {
            constexpr int resizeFactor = 2;
            resize(mCapacity * resizeFactor);
        }
        mData[mSize] = item;
        mSize++;
    }

    /**
     * @brief Insert an element at the specified position in the array.
     *
     * This method shifts existing elements to the right starting from the specified
     * position to create space for the new element, then inserts the new element at
     * the given index. If the array is full, the capacity is doubled before the
     * insertion.
     *
     * @param item The element to insert.
     * @param pos The position at which the element should be inserted.
     * @return iterator to the inserted value.
     *
     * @throws std::out_of_range if the position is out of bounds (less than 0 or greater than the current size).
     *
     * @complexity
     * - Time Complexity: worse case O(n) (shifting all elements to the right and resizing if necessary).
     * - Space Complexity: 0(1) or O(n) if takes place resizing, where n is the new capacity.
     */
    iterator insert(const T& item, int pos)
    {
        if (pos < 0 || pos > mSize)
        {
            throw std::out_of_range("Index out of bounds in DynamicArray::insert");
        }

        if (mSize == mCapacity)
        {
            constexpr int resizeFactor = 2;
            resize(mCapacity * resizeFactor);
        }

        for (int i = mSize; i > pos; i--)
        {
            mData[i] = mData[i - 1];
        }

        mData[pos] = item;
        mSize++;

        return &mData[pos];
    }

    /**
     * @brief Erase an element from the array at the specified position.
     *
     * This function removes the element at the specified position in the array and shifts
     * all subsequent elements to fill the gap. The size of the array is decreased by 1.
     *
     * @param pos The index of the element to erase.
     * @return iterator to the value after erased value.
     *
     * @throws std::out_of_range if the position is invalid (either negative or greater than the current size).
     * @throws std::out_of_range if the array is empty.
     *
     * @complexity
     * - Time Complexity: worst case O(n) for shifting elements after removal (where n is the size of the array).
     * - Space Complexity: O(1) (no additional memory is used except for a small amount of memory used for temporary
     * variables).
     */
    iterator erase(int pos)
    {
        if (isEmpty())
        {
            throw std::out_of_range("The array is empty in DynamicArray::erase");
        }

        if (pos < 0 || pos >= mSize)
        {
            throw std::out_of_range("Index out of bounds in DynamicArray::erase");
        }

        for (int i = pos; i < mSize - 1; i++)
        {
            mData[i] = mData[i + 1];
        }
        mSize--;

        return &mData[pos];
    }

    /**
     * @brief Get the size of the array (dynamic size).
     *
     * @return The total number of elements inside the array.
     */
    [[nodiscard]] int getSize() const noexcept
    {
        return mSize;
    }

    /**
     * @brief Get the capacity of the array.
     * @return The number of elements that can be held in currently allocated storage).
     */
    [[nodiscard]] int getCapacity() const noexcept
    {
        return mCapacity;
    }

    /**
     * @brief Checks if the container has no elements.
     *
     * @return True if the container is empty, false otherwise.
     */
    [[nodiscard]] bool isEmpty() const noexcept
    {
        return mSize == 0;
    }

    /**
     * @return Return the default capacity of a DynamicArray<T>.
     */
    [[nodiscard]] static constexpr int getDefaultCapacity() noexcept
    {
        constexpr int defaultCapacity = 5;
        return defaultCapacity;
    }

private:
    /**
     * @brief Resize the array to a new capacity.
     *
     * Allocates new storage with the specified capacity and moves existing elements
     * to the new storage. Deletes the old storage after resizing.
     *
     * @param newCapacity The new capacity of the array.
     */
    void resize(int newCapacity)
    {
        T* newData = new T[newCapacity];

        // Move elements to the new array
        for (int i = 0; i < mSize; i++)
        {
            newData[i] = mData[i];
        }

        // Delete old array and update the pointer
        delete[] mData;
        mData = newData;
        mCapacity = newCapacity;
    }

    int mSize{0};      ///< The number of elements.
    int mCapacity{0};  ///< The number of elements that can be held in currently allocated storage.

    T* mData;
};
