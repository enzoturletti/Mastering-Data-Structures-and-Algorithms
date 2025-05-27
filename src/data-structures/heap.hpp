#pragma once
#include <dynamic-array.hpp>

constexpr int DEFAULT_INITIAL_CAPACITY{10};

template <typename T>
class MinHeap
{
public:
    MinHeap() : mData(DEFAULT_INITIAL_CAPACITY)
    {
    }

    /**
     * @brief Inserts a new value into the heap, maintaining the min-heap property.
     *
     * The value is appended at the end of the internal array and then
     * "bubbled up" (heapified) by comparing it with its parent and swapping
     * if necessary, until the heap property is restored.
     *
     * @param value The value to insert into the heap.
     *
     * @note
     * This function assumes the heap is implemented as a binary min-heap.
     * The actual time complexity assumes that appending to the underlying storage
     * (e.g., dynamic array) is amortized O(1). However, if the internal array needs
     * to grow (i.e., reallocate memory), the operation can temporarily take longer.
     *
     * @complexity
     * Time: O(log n) in the average case. May be slower if memory reallocation occurs during append.
     * Space: O(1) auxiliary space.
     */
    void insert(const T& value)
    {
        mData.append(value);

        // Reordering
        int index = mData.getSize() - 1;
        while (index > 0)
        {
            int parentIndex = (index - 1) / 2;

            if (mData[index] < mData[parentIndex])
            {
                std::swap(mData[index], mData[parentIndex]);
                index = parentIndex;
            }
            else
            {
                break;
            }
        }
    }

    /**
     * @brief Removes the smallest element (root) from the heap, maintaining the min-heap property.
     *
     * The root is replaced by the last element in the internal array,
     * which is then "bubbled down" (heapified) to its correct position
     * by comparing with its children and swapping with the smallest if needed.
     *
     * If the heap is empty, the function does nothing.
     *
     * @note This function assumes the heap is implemented as a binary min-heap.
     *
     * @complexity
     * Time: O(log n), where n is the number of elements in the heap.
     * Space: O(1) auxiliary space.
     */
    void pop()
    {
        if (mData.isEmpty())
            return;

        int lastIndex = mData.getSize() - 1;
        std::swap(mData[0], mData[lastIndex]);
        mData.erase(lastIndex);

        int currentIndex = 0;

        while (true)
        {
            int left = 2 * currentIndex + 1;
            int right = 2 * currentIndex + 2;
            int smallest = currentIndex;

            if (left < mData.getSize() && mData[left] < mData[smallest])
            {
                smallest = left;
            }

            if (right < mData.getSize() && mData[right] < mData[smallest])
            {
                smallest = right;
            }

            if (smallest != currentIndex)
            {
                std::swap(mData[currentIndex], mData[smallest]);
                currentIndex = smallest;
            }
            else
            {
                break;
            }
        }
    }

    // For testing purpouses.
    std::vector<T> toVector() const
    {
        std::vector<T> out;
        for (int i = 0; i < mData.getSize(); ++i)
        {
            out.push_back(mData[i]);
        }
        return out;
    }

private:
    DynamicArray<T> mData;
};