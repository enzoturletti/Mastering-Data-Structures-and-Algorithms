#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>

#include <matrix.hpp>

/**
 * @class SymmetricMatrix
 * @brief A class representing a symmetric matrix.
 *
 * This class inherits from the `MatrixBase` class and provides a specialized implementation
 * for symmetric matrices, where the upper triangular part mirrors the lower triangular part.
 *
 * Symmetric matrices are space-efficient since only the lower triangular part is stored.
 * The storage is optimized by using a 1D array to store the lower triangular elements.
 *
 * @tparam T The type of elements stored in the matrix.
 */
template <typename T>
class SymmetricMatrix : public MatrixBase<T, SymmetricMatrix<T>>
{
public:
    /**
     * @brief Constructor for a symmetric matrix of size n x m.
     *
     * This constructor initializes a symmetric matrix given its dimensions. The matrix is
     * represented in a compact form where only the lower triangular elements (including the diagonal)
     * are stored. The number of elements is `n*(n+1)/2` where `n` is the row count of the matrix.
     *
     * @param n The number of rows in the matrix.
     * @param m The number of columns in the matrix.
     *
     * @throws std::invalid_argument If the matrix dimensions are invalid for a symmetric matrix.
     */
    SymmetricMatrix(size_t n, size_t m) : MatrixBase<T, SymmetricMatrix<T>>(n, m, n * (n + 1) / 2)
    {
        if (n != m)
        {
            throw std::invalid_argument("Matrix must be square for symmetric matrix.");
        }
    }

    /**
     * @brief Constructor for a symmetric matrix using a 2D vector of values.
     *
     * This constructor initializes a symmetric matrix from a 2D vector of values. Only the
     * lower triangular part (including the diagonal) is initialized from the input, and the
     * matrix is compressed into a 1D array.
     *
     * @param values A 2D vector representing the initial values of the matrix.
     *
     * @throws std::invalid_argument If the matrix is not square.
     */
    SymmetricMatrix(const std::vector<std::vector<T>>& values)
        : MatrixBase<T, SymmetricMatrix<T>>(values, values.size() * (values.size() + 1) / 2)
    {
        // Check that the matrix is square
        if (values.size() != values[0].size())
        {
            throw std::invalid_argument("Non-square matrix provided for symmetric matrix.");
        }

        // Initialize the lower triangular elements
        for (size_t i = 0; i < values.size(); i++)
        {
            if (values[i].size() != values.size())  // Ensure all rows have the same number of columns
            {
                throw std::invalid_argument("Non-square matrix provided for symmetric matrix.");
            }

            // Fill the lower triangular part of the matrix
            for (size_t j = 0; j <= i; j++)  // Only the lower triangular elements (including diagonal) are set
            {
                this->set(i, j, values[i][j]);
            }
        }
    }

    /**
     * @brief Get the value of the matrix at position (i, j).
     *
     * This method retrieves the value from the matrix at the specified row (i) and column (j).
     * If the provided indices are outside of the matrix bounds, it will throw an `out_of_range` exception.
     * For symmetry, it ensures the proper indexing by swapping i and j if i < j.
     *
     * @param i Row index of the matrix.
     * @param j Column index of the matrix.
     *
     * @return The value at position (i, j).
     *
     * @throws std::out_of_range If the indices are out of the bounds of the matrix.
     */
    const T get(size_t i, size_t j) const
    {
        // Check if the indices are within bounds
        this->checkRange(i, j);

        // Ensure the correct indices for symmetric access
        if (i < j)
        {
            std::swap(i, j);
        }

        // Return the value from the compressed array representation
        return this->data[(i * (i + 1)) / 2 + j];
    }

    /**
     * @brief Set the value of the matrix at position (i, j).
     *
     * This method sets the value of the matrix at the specified row (i) and column (j).
     * If the provided indices are outside of the matrix bounds or if the indices are non-symmetric,
     * it will throw an appropriate exception.
     *
     * @param i Row index of the matrix.
     * @param j Column index of the matrix.
     * @param value The value to set at position (i, j).
     *
     * @throws std::out_of_range If the indices are out of bounds.
     * @throws std::logic_error If the set operation is attempted on non-symmetric elements.
     */
    void set(size_t i, size_t j, const T& value)
    {
        // Check if the indices are within bounds
        this->checkRange(i, j);

        // Ensure the correct indices for symmetric access
        if (i < j)
        {
            std::swap(i, j);
        }

        // Set the value in the compressed array representation
        this->data[(i * (i + 1)) / 2 + j] = value;
    }
};
