#pragma once
#include <iostream>
#include <matrix.hpp>
#include <stdexcept>

/// A class representing a diagonal matrix with dynamic allocation.
template <typename T>
class DiagonalMatrix : public MatrixBase<T, DiagonalMatrix<T>>
{
public:
    /**
     * @brief Constructor for DiagonalMatrix.
     * Initializes all diagonal elements to the default value (zero).
     *
     * @param diagonalSize number of elements in the diagonal.
     *
     * Time Complexity: O(n), where `n` is the number of rows or columns. This function iterates over the diagonal
     * elements. Space Complexity: O(n), storing only diagonal elements.
     */
    DiagonalMatrix(size_t diagonalSize) : MatrixBase<T, DiagonalMatrix<T>>(diagonalSize, diagonalSize, diagonalSize)
    {
    }

    /**
     * @brief Constructor for DiagonalMatrix.
     * Initializes all diagonal elements to values.
     *
     * @param diagonalSize number of elements in the diagonal.
     * @param values A vector representing the values of the diagnoal.
     *
     * Time Complexity: O(n), where `n` is the number of rows or columns. This function iterates over the diagonal
     * elements. Space Complexity: O(n), storing only diagonal elements.
     */
    DiagonalMatrix(const std::vector<T>& values)
        : MatrixBase<T, DiagonalMatrix<T>>(values.size(), values.size(), values.size())
    {
        for (size_t i = 0; i < values.size(); i++)
        {
            this->set(i, i, values[i]);
        }
    }

    /**
     * @brief Constructor that takes a 2D vector.
     * Initializes the diagonal elements using the provided values.
     *
     * @param values A matrix representing the values of the matrix.
     *
     * Time Complexity: O(n), where `n` is the number of rows or columns. This function iterates over the diagonal
     * elements. Space Complexity: O(n), storing only diagonal elements.
     */
    DiagonalMatrix(const std::vector<std::vector<T>>& values) : MatrixBase<T, DiagonalMatrix<T>>(values, values.size())
    {
        if (values.size() != values[0].size())
        {
            throw std::invalid_argument("Non-square matrix provided for diagonal matrix");
        }
        for (size_t i = 0; i < values.size(); i++)
        {
            if (values[i].size() != values.size())
            {
                throw std::invalid_argument("Non-square matrix provided for diagonal matrix");
            }
            this->set(i, i, values[i][i]);
        }
    }

    /**
     * @brief Access diagonal element at (i, j).
     * Non-diagonal elements return the default value.
     *
     * @param i Row index.
     * @param j Column index.
     *
     * @return The diagonal element if `i == j`, otherwise the default value.
     *
     * Time Complexity: O(1). Accessing an element in the array by index is constant time.
     * Space Complexity: O(1). Only a reference to the element is returned.
     */
    const T get(size_t i, size_t j) const
    {
        this->checkRange(i, j);
        return (i == j) ? this->data[i] : this->defaultValue;
    }

    /**
     * @brief Set diagonal element at (i, j).
     * Only diagonal elements (where `i == j`) can be set.
     *
     * @param i Row index.
     * @param j Column index.
     * @param value Value to set at (i, j).
     *
     * Time Complexity: O(1). Setting an element in the array by index is constant time.
     * Space Complexity: O(1). No additional space used, modifies the existing `data` array.
     */
    void set(size_t i, size_t j, const T& value)
    {
        this->checkRange(i, j);
        if (i != j)
        {
            throw std::logic_error("Non-diagonal elements cannot be set");
        }
        this->data[i] = value;
    }
};
