#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>

#include <matrix.hpp>

/// A class representing a lower triangular matrix of arbitrary size.
template <typename T>
class LowerTriangularMatrix : public MatrixBase<T, LowerTriangularMatrix<T>>
{
public:
    /**
     * @brief Constructor that creates a lower triangular matrix of size `n` by `m`.
     * This constructor initializes a matrix with the given number of rows (`n`) and columns (`m`),
     * and stores only the lower triangular elements (including the diagonal).
     *
     * @param n Number of rows.
     * @param m Number of columns.
     *
     * Time Complexity: O(n^2), where `n` is the number of rows and columns. This is the time
     * taken to initialize the lower triangular portion of the matrix.
     * Space Complexity: O(n * (n + 1) / 2), as we only store the lower triangular part.
     */
    LowerTriangularMatrix(size_t n, size_t m) : MatrixBase<T, LowerTriangularMatrix<T>>(n, m, n * (n + 1) / 2)
    {
        if (n != m)
        {
            throw std::invalid_argument("Matrix must be square for symmetric matrix.");
        }
    };

    /**
     * @brief Constructor that initializes the matrix using a 2D vector, where each row contains the lower
     * triangular elements of the matrix (including the diagonal).
     * This constructor ensures that the matrix is square (i.e., the number of rows and columns are equal),
     * and only the lower triangular elements are provided.
     * The non-triangular elements will be implicitly set to the default value (usually zero).
     *
     * @param values A 2D vector representing the lower triangular part of the matrix. Each row should contain
     * the lower triangular elements for the corresponding row of the matrix.
     *
     * @throws std::invalid_argument if the provided matrix is not square.
     *
     * Time Complexity: O(n^2), where `n` is the size of the matrix. This is because we are iterating
     * over all the lower triangular elements in the matrix.
     * Space Complexity: O(n * (n + 1) / 2), as we only store the lower triangular part of the matrix.
     */
    LowerTriangularMatrix(const std::vector<std::vector<T>>& values)
        : MatrixBase<T, LowerTriangularMatrix<T>>(values, values.size() * (values.size() + 1) / 2)
    {
        // Check that the matrix is square
        if (values.size() != values[0].size())
        {
            throw std::invalid_argument("Non-square matrix provided for lower-triangle matrix");
        }

        // Initialize the lower triangular elements
        for (size_t i = 0; i < values.size(); i++)
        {
            if (values[i].size() != values.size())  // Ensure all rows have the same number of columns
            {
                throw std::invalid_argument("Non-square matrix provided for lower-triangle matrix");
            }

            // Fill the lower triangular part of the matrix
            for (size_t j = 0; j <= i; j++)  // Only the lower triangular elements (including diagonal) are set
            {
                this->set(i, j, values[i][j]);
            }
        }
    }

    /**
     * @brief Access an element at position (i, j).
     * If `i >= j`, the corresponding lower triangular element is returned. Otherwise,
     * the default value (typically zero) is returned for non-lower triangular elements.
     *
     * @param i Row index.
     * @param j Column index.
     *
     * @return A reference to the lower triangular element if `i >= j`, otherwise returns the default value.
     *
     * Time Complexity: O(1). Accessing an element by index is constant time.
     * Space Complexity: O(1). The function returns a reference to an existing element in the data array.
     */
    const T get(size_t i, size_t j) const
    {
        // Check if indices are within the valid range
        this->checkRange(i, j);

        // If i < j, return the default value (non-lower triangular elements)
        if (i < j)
        {
            return this->defaultValue;  // Non-lower triangular elements return the default value
        }

        // Return the lower triangular element from the data array
        return this->data[(i * (i + 1)) / 2 + j];
    }

    /**
     * @brief Set an element at position (i, j).
     * Only lower triangular elements, where `i >= j`, can be modified.
     * Any attempt to set elements outside the lower triangular part will throw an exception.
     *
     * @param i Row index.
     * @param j Column index.
     * @param value The value to set at (i, j).
     *
     * Time Complexity: O(1). Setting an element by index is constant time.
     * Space Complexity: O(1). No additional space is used, as the existing `data` array is modified.
     */
    void set(size_t i, size_t j, const T& value)
    {
        // Check if indices are within the valid range
        this->checkRange(i, j);

        // If i < j, throw an error as we can't set non-lower triangular elements
        if (i < j)
        {
            throw std::logic_error("Non-lower triangular elements cannot be set");
        }

        // Set the lower triangular element in the data array
        this->data[(i * (i + 1)) / 2 + j] = value;
    }
};
