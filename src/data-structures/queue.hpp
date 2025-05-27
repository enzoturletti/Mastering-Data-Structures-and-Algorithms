#pragma once

#include <list.hpp>
#include <useful-concepts.hpp>
#include <utility>

template <typename T, typename Container = List<T>>
requires(HasAppend<Container>&& HasGetSize<Container>) class Queue
{
public:
    static_assert(std::is_same<typename Container::value_type, T>::value, "Container items should be same type as T.");

    /**
     * @brief Adds an element to the back of the queue.
     * @param value The element to be enqueued.
     * @complexity Time: O(1) on average or O(n) if resizing is needed (DynamicArray), O(1) always (List). Space: O(1).
     */
    void push(const T& value)
    {
        data.append(value);
    }

    /**
     * @brief Removes the front element from the queue.
     * @throws std::out_of_range if the queue is empty.
     * @complexity Time: O(n) (DynamicArray), O(1) (List). Space: O(1).
     */
    void pop()
    {
        if (isEmpty())
        {
            throw std::out_of_range("Queue::pop() called on empty queue");
        }

        data.erase(0);
    }

    /**
     * @brief Returns a const reference to the front element of the queue.
     * @return Const reference to the front element.
     * @throws std::out_of_range if the queue is empty.
     * @complexity Time: O(1). Space: O(1).
     */
    [[nodiscard]] const T& front() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("Queue::front() Empty queue");
        }

        return *(data.begin());
    }

    /**
     * @brief Returns a reference to the front element of the queue.
     * @return Reference to the front element.
     * @throws std::out_of_range if the queue is empty.
     * @complexity Time: O(1). Space: O(1).
     */
    [[nodiscard]] T& front()
    {
        return const_cast<T&>(std::as_const(*this).front());
    }

    /**
     * @brief Returns a const reference to the last element in the queue.
     * @return Const reference to the back element.
     * @throws std::out_of_range if the queue is empty.
     * @complexity Time: O(1). Space: O(1).
     */
    [[nodiscard]] const T& back() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("Queue::back() Empty queue");
        }

        return *(data.end() - 1);
    }

    /**
     * @brief Returns a reference to the last element in the queue.
     * @return Reference to the back element.
     * @throws std::out_of_range if the queue is empty.
     * @complexity Time: O(1). Space: O(1).
     */
    [[nodiscard]] T& back()
    {
        return const_cast<T&>(std::as_const(*this).back());
    }

    /**
     * @brief Checks if the queue is empty.
     * @return True if the queue is empty, otherwise false.
     */
    [[nodiscard]] bool isEmpty() const
    {
        return data.getSize() == 0;
    }

    /**
     * @brief Gets the number of elements in the queue.
     * @return The size of the queue.
     */
    [[nodiscard]] int getSize() const
    {
        return data.getSize();
    };

private:
    Container data;  ///< The underlying container storing queue elements.
};
