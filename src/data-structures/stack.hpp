#pragma once

#include <dynamic-array.hpp>
#include <useful-concepts.hpp>

/**
 * @brief A stack data structure with customizable underlying container.
 *
 * @tparam T The type of elements stored in the stack.
 * @tparam Container The underlying container type (defaults to DynamicArray<T>).
 * @requires Container must support append() and getSize() operations.
 * @note Using a DynamicArray provides O(1) average time for push but may require O(n) for resizing. Using a List
 * ensures O(1) push and pop but requires O(n) for indexed access.
 */
template <typename T, typename Container = DynamicArray<T>>
requires(HasAppend<Container>&& HasGetSize<Container>) class Stack
{
    static_assert(std::is_same<typename Container::value_type, T>::value, "Container items should be same type as T.");

public:
    /**
     * @brief Pushes an element onto the stack.
     * @param value The element to be added.
     * @complexity Time: O(1) on average or O(n) if resizing is needed (DynamicArray), O(1) always (List). Space: O(1).
     */
    void push(const T& value)
    {
        data.append(value);
    };

    /**
     * @brief Removes the top element from the stack.
     * @throws std::out_of_range if the stack is empty.
     * @complexity Time: O(1) (DynamicArray and List). Space: O(1).
     */
    void pop()
    {
        if (isEmpty())
        {
            throw std::out_of_range("Stack::pop() called on empty stack");
        }
        data.erase(getSize() - 1);
    };

    /**
     * @brief Gets an element at a specific index.
     * @param index The index of the element.
     * @return The element at the given index.
     * @throws std::out_of_range if the index is out of bounds.
     * @complexity Time: O(1) (DynamicArray), O(n) (List). Space: O(1).
     */
    [[nodiscard]] const T& get(int index) const
    {
        if (index >= getSize())
        {
            throw std::out_of_range("Index out of bounds in Stack::get");
        }
        return data[index];
    };

    [[nodiscard]] T& get(int index)
    {
        return const_cast<T&>(std::as_const(*this).get(index));
    }

    /**
     * @brief Returns the top element of the stack.
     * @return The top element.
     * @throws std::out_of_range if the stack is empty.
     * @complexity Time: O(1) (DynamicArray and List). Space: O(1).
     */
    [[nodiscard]] const T& top() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("Empty stack in Stack::top");
        }
        return data[getSize() - 1];
    };

    [[nodiscard]] T& top()
    {
        return const_cast<T&>(std::as_const(*this).top());
    }

    /**
     * @brief Checks if the stack is empty.
     * @return True if the stack is empty, otherwise false.
     * @complexity Time: O(1) (DynamicArray and List). Space: O(1).
     */
    [[nodiscard]] bool isEmpty() const
    {
        return data.getSize() == 0;
    }

    /**
     * @brief Gets the number of elements in the stack.
     * @return The size of the stack.
     * @complexity Time: O(1) (DynamicArray and List). Space: O(1).
     */
    [[nodiscard]] int getSize() const
    {
        return data.getSize();
    };

private:
    Container data;  ///< The underlying container storing stack elements.
};
