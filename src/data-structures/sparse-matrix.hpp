#pragma once

#include <iostream>
#include <vector>

#include <matrix.hpp>

/**
 * @brief Structure representing an element in the sparse matrix.
 *
 * @tparam T Type of the value stored in the matrix.
 */
template <typename T>
struct Element
{
    size_t i;  ///< Row index of the element.
    size_t j;  ///< Column index of the element.
    T value;   ///< Value stored in the matrix at (i, j).

    /**
     * @brief Equality operator for comparing two `Element` objects.
     *
     * @param other Another `Element` object to compare with.
     * @return true if the two elements are equal, false otherwise.
     */
    bool operator==(const Element<T>& other) const
    {
        return i == other.i && j == other.j && value == other.value;
    }
};

/**
 * @brief SparseMatrix class representing a sparse matrix data structure.
 *
 * @tparam T The type of the values in the matrix.
 */
template <typename T>
class SparseMatrix : public MatrixBase<Element<T>, SparseMatrix<Element<T>>>
{
public:
    /**
     * @brief Constructor to create a SparseMatrix of the specified size.
     *
     * @param rows Number of rows in the matrix.
     * @param columns Number of columns in the matrix.
     */
    SparseMatrix(size_t rows, size_t columns) : MatrixBase<Element<T>, SparseMatrix<Element<T>>>(rows, columns, 1)
    {
        // Time complexity: O(1)
        // Space complexity: O(1) (Only initializing a matrix with rows and columns)
    }

    /**
     * @brief Copy constructor to create a SparseMatrix as a copy of another.
     *
     * @param other The matrix to copy from.
     */
    SparseMatrix(const SparseMatrix<T>& other)
        : MatrixBase<Element<T>, SparseMatrix<Element<T>>>(other.rows, other.columns, 1)
    {
        // Copy the data from the other matrix into the current matrix.
        this->data = other.data;

        // Time complexity: O(n), where n is the number of non-zero elements in the other matrix.
        // Space complexity: O(n), as we are copying the data from the other matrix to the new one.
    }

    /**
     * @brief Retrieves the value at position (i, j) in the matrix.
     *
     * This function searches the data vector to find an element with the given indices.
     *
     * @param i Row index.
     * @param j Column index.
     * @return The value at (i, j), or the default value of T if not found.
     */
    const T get(size_t i, size_t j) const
    {
        this->checkRange(i, j);  ///< Ensure indices are within range.

        for (Element element : this->data)
        {
            if (element.i == i && element.j == j)
            {
                return element.value;
            }
        }

        return T();  ///< Return default value if not found.

        // Time complexity: O(n) where n is the number of non-zero elements stored in the matrix.
        // Space complexity: O(1) (no additional memory is allocated except for local variables)
    }

    /**
     * @brief Sets the value at position (i, j) in the matrix.
     *
     * If the value is the default value, the element is removed from the matrix if it exists.
     * Otherwise, it either updates the value of an existing element or adds a new element at the correct position.
     *
     * @param i Row index.
     * @param j Column index.
     * @param value The value to set at position (i, j).
     */
    void set(size_t i, size_t j, const T& value)
    {
        this->checkRange(i, j);  ///< Ensure indices are within range.

        // Check if the value is the default value. If it is, we may want to skip adding it.
        if (value == T())
        {
            // Remove the element if it exists and it's set to the default value.
            auto it = std::remove_if(this->data.begin(), this->data.end(), [i, j](const Element<T>& element) {
                return element.i == i && element.j == j;
            });
            this->data.erase(it, this->data.end());
        }
        else
        {
            // Check if the element already exists
            auto it = std::find_if(this->data.begin(), this->data.end(), [i, j](const Element<T>& element) {
                return element.i == i && element.j == j;
            });

            if (it != this->data.end())
            {
                // Update the existing element
                it->value = value;
            }
            else
            {
                // Element not found, insert it in the correct position
                Element<T> newElement{i, j, value};

                // Find the correct position to insert (keeping sorted order)
                auto insertPos = std::lower_bound(
                    this->data.begin(), this->data.end(), newElement, [](const Element<T>& a, const Element<T>& b) {
                        // Compare first by row, then by column
                        return a.i == b.i ? a.j < b.j : a.i < b.i;
                    });

                // Insert the element at the found position
                this->data.insert(insertPos, newElement);
            }
        }

        // Time complexity: O(n) for searching for the element and inserting/removing.
        // Space complexity: O(n) (in the worst case, when we need to insert or remove an element in the matrix)
    }

    /**
     * @brief Adds two sparse matrices element-wise.
     *
     * This function checks that the matrices have the same dimensions and adds their corresponding elements.
     *
     * @param other The matrix to add to the current matrix.
     * @return A new `SparseMatrix` representing the sum of the two matrices.
     * @throws std::invalid_argument if the matrices have different dimensions.
     */
    SparseMatrix<T> add(const SparseMatrix<T>& other) const
    {
        // Ensure both matrices have the same dimensions
        if (this->rows != other.rows || this->columns != other.columns)
        {
            throw std::invalid_argument("Matrices must have the same dimensions for addition.");
        }

        // Use the copy constructor to create a copy of the current matrix
        SparseMatrix<T> result(*this);

        // Iterate through the elements of the other matrix and add them to the result
        for (const Element<T>& element : other.data)
        {
            T existingValue = result.get(element.i, element.j);
            result.set(element.i, element.j, existingValue + element.value);
        }

        return result;

        // Worst cases:
        // Time complexity: O(n * m), where:
        //    - n is the number of non-zero elements in the current matrix.
        //    - m is the number of non-zero elements in the other matrix.
        // In the worst case, each element of the other matrix requires a `get` operation, which takes O(n) time.
        // Hence, the time complexity is O(n * m), where n is the number of non-zero elements in the current matrix
        // and m is the number of non-zero elements in the other matrix.

        // Space complexity: O(n + m), where:
        //    - n is the number of non-zero elements in the current matrix.
        //    - m is the number of non-zero elements in the other matrix.
        // This is for storing the result matrix (which is a copy of the current matrix) and intermediate values during
        // the addition.
    }
};
