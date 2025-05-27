#pragma once
#include <iostream>
#include <matrix.hpp>
#include <stdexcept>

/// Base class for matrices with common operations for rows, columns, and size.
template <typename T, typename Derived>
class MatrixBase
{
public:
    /**
     * @brief Get an element at (i, j).
     * Calls the derived class' `get` function to access the element.
     *
     * @param i Row index.
     * @param j Column index.
     *
     * @return The element at (i, j).
     *
     * Time Complexity: O(1). Accessing the element is constant time.
     * Space Complexity: O(1). No additional space is used.
     */
    [[nodiscard]] const T& get(size_t i, size_t j) const
    {
        return static_cast<const Derived*>(this)->get(i, j);
    }

    /**
     * @brief Set an element at (i, j).
     * Calls the derived class' `set` function to set the element.
     *
     * @param i Row index.
     * @param j Column index.
     * @param value Value to set at (i, j).
     *
     * Time Complexity: O(1). Setting the element is constant time.
     * Space Complexity: O(1). No additional space is used.
     */
    void set(size_t i, size_t j, const T& value)
    {
        static_cast<Derived*>(this)->set(i, j, value);
    }

    /**
     * @brief Get the total size (rows * columns) of the matrix.
     *
     * @return The total size of the matrix.
     *
     * Time Complexity: O(1). Retrieving the size is constant time.
     * Space Complexity: O(1). No additional space is used.
     */
    [[nodiscard]] size_t getSize() const
    {
        return rows * columns;
    }

    /**
     * @brief Get the number of rows in the matrix.
     *
     * @return The number of rows.
     *
     * Time Complexity: O(1). Retrieving the row count is constant time.
     * Space Complexity: O(1). No additional space is used.
     */
    [[nodiscard]] size_t getRowsSize() const
    {
        return rows;
    }

    /**
     * @brief Get the number of columns in the matrix.
     *
     * @return The number of columns.
     *
     * Time Complexity: O(1). Retrieving the column count is constant time.
     * Space Complexity: O(1). No additional space is used.
     */
    [[nodiscard]] size_t getColumnsSize() const
    {
        return columns;
    }

protected:
    /**
     * @brief Default constructor for MatrixBase.
     * Initializes the matrix, setting all elements to the default value.
     */
    MatrixBase(size_t n, size_t m, size_t memorySize) : rows(n), columns(m), data(memorySize, T())
    {
    }

    /**
     * @brief Constructor from a 2D vector.
     * Initializes the matrix using the provided 2D vector.
     *
     * @param values A 2D vector representing the matrix.
     *
     * Time Complexity: O(n*m), where `n` is rows and `m` is columns.
     * Space Complexity: O(n*m), storing all matrix elements.
     */
    MatrixBase(const std::vector<std::vector<T>>& values, size_t memorySize)
        : rows(values.size()), columns(values.empty() ? 0 : values[0].size()), data(memorySize, T())
    {
    }

    /**
     * @brief Check the index range for valid values of i and j.
     * Throws an exception if the indices are out of range.
     *
     * @param i Row index.
     * @param j Column index.
     *
     * Time Complexity: O(1). Checking the indices is constant time.
     * Space Complexity: O(1). No additional space is used.
     */
    void checkRange(size_t i, size_t j) const
    {
        if (i >= rows || j >= columns)  // Fixed incorrect 'size' usage
        {
            throw std::out_of_range("Index out of range");
        }
    }

    std::vector<T> data;  ///< Storage for matrix data
    T defaultValue{T()};  ///< Default value (typically 0)

    size_t rows;
    size_t columns;
};
