#include <gtest/gtest.h>
#include <stdexcept>
#include <unordered_map>
#include "sparse-matrix.hpp"

// Test insertion and retrieval of a single element
TEST(SparseMatrixTest, InsertionAndRetrievalTest)
{
    SparseMatrix<int> matrix(4, 4);

    // Insert a few non-zero elements
    matrix.set(0, 0, 10);
    matrix.set(1, 2, 20);
    matrix.set(2, 3, 30);

    // Retrieve and check the inserted values
    EXPECT_EQ(matrix.get(0, 0), 10);
    EXPECT_EQ(matrix.get(1, 2), 20);
    EXPECT_EQ(matrix.get(2, 3), 30);

    // Retrieve and check not inserted values.
    EXPECT_EQ(matrix.get(1, 1), 0);
    EXPECT_EQ(matrix.get(2, 2), 0);
}

// Test retrieving a non-existing element (should return 0, default value)
TEST(SparseMatrixTest, NonExistingElementTest)
{
    SparseMatrix<int> matrix(3, 3);

    // Retrieve an element that has not been inserted
    EXPECT_EQ(matrix.get(0, 1), 0);  // Default value for int is 0
}

// Test updating an existing element
TEST(SparseMatrixTest, UpdateElementTest)
{
    SparseMatrix<int> matrix(3, 3);

    // Insert initial value
    matrix.set(0, 0, 10);

    // Update the value
    matrix.set(0, 0, 20);

    // Retrieve and check if the value was updated
    EXPECT_EQ(matrix.get(0, 0), 20);
}

// Test removing an element
TEST(SparseMatrixTest, RemoveElementTest)
{
    SparseMatrix<int> matrix(3, 3);

    // Insert an element
    matrix.set(0, 0, 10);

    // Remove the element by setting it to the default value (0)
    matrix.set(0, 0, 0);  // Assuming setting it to 0 removes it from storage

    // Check if the element was removed (should return 0, default value)
    EXPECT_EQ(matrix.get(0, 0), 0);
}

// Test inserting multiple elements and checking sparsity
TEST(SparseMatrixTest, SparsityTest)
{
    SparseMatrix<int> matrix(4, 4);

    // Insert only a few elements (sparse matrix)
    matrix.set(0, 0, 10);
    matrix.set(1, 1, 20);
    matrix.set(2, 3, 30);

    EXPECT_EQ(matrix.getSize(), 16);

    // Check specific values
    EXPECT_EQ(matrix.get(0, 0), 10);
    EXPECT_EQ(matrix.get(1, 1), 20);
    EXPECT_EQ(matrix.get(2, 3), 30);

    // Verify that accessing non-inserted elements returns the default value (0)
    EXPECT_EQ(matrix.get(0, 1), 0);
    EXPECT_EQ(matrix.get(1, 2), 0);
    EXPECT_EQ(matrix.get(3, 3), 0);
}

// Test handling large matrices
TEST(SparseMatrixTest, LargeMatrixTest)
{
    SparseMatrix<int> matrix(10, 10);

    // Insert a few elements in a large 10x10 matrix
    matrix.set(0, 0, 10);
    matrix.set(9, 9, 20);
    matrix.set(5, 5, 30);

    // Verify the inserted values
    EXPECT_EQ(matrix.get(0, 0), 10);
    EXPECT_EQ(matrix.get(9, 9), 20);
    EXPECT_EQ(matrix.get(5, 5), 30);

    // Verify non-inserted elements return 0
    EXPECT_EQ(matrix.get(1, 1), 0);
    EXPECT_EQ(matrix.get(8, 8), 0);
    EXPECT_EQ(matrix.get(7, 9), 0);
}

// Test handling of non-square matrices
TEST(SparseMatrixTest, NonSquareMatrixTest)
{
    SparseMatrix<int> matrix(3, 4);  // Non-square matrix (3 rows, 4 columns)

    // Insert elements into a 3x4 sparse matrix
    matrix.set(0, 0, 5);
    matrix.set(1, 3, 10);
    matrix.set(2, 2, 15);

    // Verify the inserted values
    EXPECT_EQ(matrix.get(0, 0), 5);
    EXPECT_EQ(matrix.get(1, 3), 10);
    EXPECT_EQ(matrix.get(2, 2), 15);

    // Verify non-inserted elements return 0
    EXPECT_EQ(matrix.get(0, 1), 0);
    EXPECT_EQ(matrix.get(1, 0), 0);
    EXPECT_EQ(matrix.get(2, 3), 0);
}

// Test adding two sparse matrices
TEST(SparseMatrixTest, AddMatricesTest)
{
    SparseMatrix<int> matrix1(3, 3);
    matrix1.set(0, 0, 5);
    matrix1.set(1, 1, 10);
    matrix1.set(2, 2, 15);

    SparseMatrix<int> matrix2(3, 3);
    matrix2.set(0, 0, 3);
    matrix2.set(1, 1, 20);
    matrix2.set(2, 2, 7);

    // Add matrices
    SparseMatrix<int> result = matrix1.add(matrix2);

    // Check the result of the addition
    EXPECT_EQ(result.get(0, 0), 8);   // 5 + 3
    EXPECT_EQ(result.get(1, 1), 30);  // 10 + 20
    EXPECT_EQ(result.get(2, 2), 22);  // 15 + 7

    // Verify other elements are still 0 (not present in the original matrices)
    EXPECT_EQ(result.get(0, 1), 0);
    EXPECT_EQ(result.get(1, 0), 0);
    EXPECT_EQ(result.get(2, 1), 0);
}

// Test adding matrices with non-overlapping elements
TEST(SparseMatrixTest, AddMatricesNoOverlapTest)
{
    SparseMatrix<int> matrix1(3, 3);
    matrix1.set(0, 0, 5);
    matrix1.set(1, 1, 10);

    SparseMatrix<int> matrix2(3, 3);
    matrix2.set(2, 2, 15);

    // Add matrices
    SparseMatrix<int> result = matrix1.add(matrix2);

    // Check the result of the addition
    EXPECT_EQ(result.get(0, 0), 5);
    EXPECT_EQ(result.get(1, 1), 10);
    EXPECT_EQ(result.get(2, 2), 15);

    // Verify other elements are still 0 (not present in the original matrices)
    EXPECT_EQ(result.get(0, 1), 0);
    EXPECT_EQ(result.get(1, 0), 0);
    EXPECT_EQ(result.get(2, 0), 0);
}

// Test adding matrices with different dimensions (should throw an error)
TEST(SparseMatrixTest, AddMatricesDimensionMismatchTest)
{
    SparseMatrix<int> matrix1(3, 3);
    matrix1.set(0, 0, 5);

    SparseMatrix<int> matrix2(4, 4);  // Different dimensions
    matrix2.set(0, 0, 3);

    // This should throw an exception because the matrices have different dimensions
    EXPECT_THROW(matrix1.add(matrix2), std::invalid_argument);
}
