#include <gtest/gtest.h>
#include <diagonal-matrix.hpp>
#include <stdexcept>

// Test constructor and correct initialization with a vector of values
TEST(DiagonalMatrixTest, ConstructorTest)
{
    std::vector<int> values = {1, 2, 3, 4, 5};
    DiagonalMatrix<int> matrix(values);

    // Check if diagonal elements are initialized correctly
    EXPECT_EQ(matrix.get(0, 0), 1);
    EXPECT_EQ(matrix.get(1, 1), 2);
    EXPECT_EQ(matrix.get(2, 2), 3);
    EXPECT_EQ(matrix.get(3, 3), 4);
    EXPECT_EQ(matrix.get(4, 4), 5);
}

// Test constructor with a 2D vector for matrix initialization
TEST(DiagonalMatrixTest, ConstructorWith2DVector)
{
    std::vector<std::vector<int>> values = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
    DiagonalMatrix<int> matrix(values);

    // Check if diagonal elements are initialized correctly
    EXPECT_EQ(matrix.get(0, 0), 1);
    EXPECT_EQ(matrix.get(1, 1), 2);
    EXPECT_EQ(matrix.get(2, 2), 3);

    // Non-diagonal elements should be default value (0)
    EXPECT_EQ(matrix.get(0, 1), 0);
    EXPECT_EQ(matrix.get(1, 0), 0);
    EXPECT_EQ(matrix.get(2, 1), 0);
    EXPECT_EQ(matrix.get(1, 2), 0);
}

// Test constructor with non-square matrix (should throw an exception)
TEST(DiagonalMatrixTest, ConstructorWithNonSquareMatrix)
{
    std::vector<std::vector<int>> values = {{1, 2}, {3, 4}, {5, 6}};

    EXPECT_THROW(DiagonalMatrix<int> matrix(values), std::invalid_argument);  // Non-square matrix
}

// Test get function with out-of-bounds indices
TEST(DiagonalMatrixTest, GetOutOfRangeTest)
{
    DiagonalMatrix<int> matrix(5);
    EXPECT_THROW(matrix.get(5, 5), std::out_of_range);  // Out-of-bounds access
    EXPECT_EQ(matrix.get(0, 1), 0);                     // Non-diagonal element, should return the default value (0)
}

// Test get and set for negative values
TEST(DiagonalMatrixTest, GetSetNegativeValues)
{
    std::vector<int> values = {-1, -2, -3, -4, -5};
    DiagonalMatrix<int> matrix(values);

    // Check if diagonal elements are initialized correctly
    EXPECT_EQ(matrix.get(0, 0), -1);
    EXPECT_EQ(matrix.get(1, 1), -2);
    EXPECT_EQ(matrix.get(2, 2), -3);
    EXPECT_EQ(matrix.get(3, 3), -4);
    EXPECT_EQ(matrix.get(4, 4), -5);

    // Modify diagonal values
    matrix.set(0, 0, -10);
    matrix.set(1, 1, -20);
    matrix.set(2, 2, -30);
    matrix.set(3, 3, -40);
    matrix.set(4, 4, -50);

    // Check modified values
    EXPECT_EQ(matrix.get(0, 0), -10);
    EXPECT_EQ(matrix.get(1, 1), -20);
    EXPECT_EQ(matrix.get(2, 2), -30);
    EXPECT_EQ(matrix.get(3, 3), -40);
    EXPECT_EQ(matrix.get(4, 4), -50);
}

// Test set function with out-of-bounds indices or non-diagonal indices
TEST(DiagonalMatrixTest, SetOutOfRangeTest)
{
    DiagonalMatrix<int> matrix(5);
    EXPECT_THROW(matrix.set(5, 5, 100), std::out_of_range);  // Out-of-bounds access
    EXPECT_THROW(matrix.set(0, 1, 100), std::logic_error);   // Non-diagonal element
}

// Test for boundary conditions (size 1 matrix)
TEST(DiagonalMatrixTest, SizeOneMatrixTest)
{
    DiagonalMatrix<int> singleElementMatrix(1);
    singleElementMatrix.set(0, 0, 99);             // Set the only element in the 1x1 matrix
    EXPECT_EQ(singleElementMatrix.get(0, 0), 99);  // Check the value
}

// Test handling of a large matrix (100x100)
TEST(DiagonalMatrixTest, LargeMatrixTest)
{
    const int size = 100;
    std::vector<int> values(size);
    for (int i = 0; i < size; ++i)
    {
        values[i] = i + 1;  // Initialize values 1, 2, ..., 100
    }
    DiagonalMatrix<int> largeMatrix(values);

    // Check if all diagonal elements are correctly initialized
    for (int i = 0; i < size; ++i)
    {
        EXPECT_EQ(largeMatrix.get(i, i), i + 1);
    }
}

// Test constructor with a zero matrix
TEST(DiagonalMatrixTest, ZeroMatrixTest)
{
    std::vector<int> zeros(5, 0);  // Initialize a vector with 5 zeros
    DiagonalMatrix<int> zeroMatrix(zeros);

    // Check if all diagonal elements are 0
    for (int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(zeroMatrix.get(i, i), 0);
    }
}

// Test setting a non-diagonal element (should throw error)
TEST(DiagonalMatrixTest, SetNonDiagonalTest)
{
    DiagonalMatrix<int> matrix(5);
    EXPECT_THROW(matrix.set(0, 1, 10), std::logic_error);  // Non-diagonal element
    EXPECT_THROW(matrix.set(1, 0, 20), std::logic_error);  // Non-diagonal element
}

// Test accessing non-diagonal elements (should return default value 0)
TEST(DiagonalMatrixTest, GetNonDiagonalTest)
{
    DiagonalMatrix<int> matrix(5);
    EXPECT_EQ(matrix.get(0, 1), 0);  // Non-diagonal element, should return 0
    EXPECT_EQ(matrix.get(1, 0), 0);  // Non-diagonal element, should return 0
}

// Test out-of-bounds access for get and set
TEST(DiagonalMatrixTest, GetSetOutOfBoundsTest)
{
    DiagonalMatrix<int> matrix(5);
    EXPECT_THROW(matrix.get(5, 5), std::out_of_range);       // Out-of-bounds access for get
    EXPECT_THROW(matrix.set(5, 5, 100), std::out_of_range);  // Out-of-bounds access for set
}

// Test modifying matrix values
TEST(DiagonalMatrixTest, ModifyMatrixTest)
{
    std::vector<int> values = {1, 2, 3, 4, 5};
    DiagonalMatrix<int> matrix(values);

    // Modifying diagonal values
    matrix.set(0, 0, 9);
    matrix.set(1, 1, 8);
    matrix.set(2, 2, 7);
    matrix.set(3, 3, 6);
    matrix.set(4, 4, 5);

    // Check modified values
    EXPECT_EQ(matrix.get(0, 0), 9);
    EXPECT_EQ(matrix.get(1, 1), 8);
    EXPECT_EQ(matrix.get(2, 2), 7);
    EXPECT_EQ(matrix.get(3, 3), 6);
    EXPECT_EQ(matrix.get(4, 4), 5);
}

// Test setting values after initializing with a 2D vector
TEST(DiagonalMatrixTest, SetAfter2DVectorInitialization)
{
    std::vector<std::vector<int>> values = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
    DiagonalMatrix<int> matrix(values);

    // Modify diagonal values
    matrix.set(0, 0, 10);
    matrix.set(1, 1, 20);
    matrix.set(2, 2, 30);

    // Check modified values
    EXPECT_EQ(matrix.get(0, 0), 10);
    EXPECT_EQ(matrix.get(1, 1), 20);
    EXPECT_EQ(matrix.get(2, 2), 30);
}

// Test that the matrix constructor handles empty input gracefully
TEST(DiagonalMatrixTest, ConstructorWithEmptyVector)
{
    std::vector<int> emptyValues;
    DiagonalMatrix<int> matrix(emptyValues);

    // Ensure no crash or misbehaving with empty vector
    EXPECT_EQ(matrix.getRowsSize(), 0);
    EXPECT_EQ(matrix.getColumnsSize(), 0);
}

// Test iteration over diagonal elements
TEST(DiagonalMatrixTest, IterationTest)
{
    std::vector<int> values = {1, 2, 3, 4, 5};
    DiagonalMatrix<int> matrix(values);

    int count = 0;
    // Iterate through the matrix and verify diagonal and non-diagonal elements
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            if (i == j)
            {
                EXPECT_EQ(matrix.get(i, j), values[i]);  // Diagonal elements should match the input
            }
            else
            {
                EXPECT_EQ(matrix.get(i, j), 0);  // Non-diagonal elements should be zero
            }
            count++;
        }
    }

    // Ensure we iterate over all 5x5 matrix elements
    EXPECT_EQ(count, 25);  // Total elements for 5x5 matrix
}

// Test iteration over a 3x3 matrix
TEST(DiagonalMatrixTest, IterationTest_3x3)
{
    std::vector<int> values = {1, 2, 3};
    DiagonalMatrix<int> matrix(values);

    int count = 0;
    // Iterate through the 3x3 matrix
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (i == j)
            {
                EXPECT_EQ(matrix.get(i, j), values[i]);  // Diagonal elements should match the input
            }
            else
            {
                EXPECT_EQ(matrix.get(i, j), 0);  // Non-diagonal elements should be zero
            }
            count++;
        }
    }

    // Ensure we iterate over all 3x3 matrix elements
    EXPECT_EQ(count, 9);  // Total elements for 3x3 matrix
}

// Test iteration over a 4x4 matrix
TEST(DiagonalMatrixTest, IterationTest_4x4)
{
    std::vector<int> values = {1, 2, 3, 4};
    DiagonalMatrix<int> matrix(values);

    int count = 0;
    // Iterate through the 4x4 matrix
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            if (i == j)
            {
                EXPECT_EQ(matrix.get(i, j), values[i]);  // Diagonal elements should match the input
            }
            else
            {
                EXPECT_EQ(matrix.get(i, j), 0);  // Non-diagonal elements should be zero
            }
            count++;
        }
    }

    // Ensure we iterate over all 4x4 matrix elements
    EXPECT_EQ(count, 16);  // Total elements for 4x4 matrix
}

// Test iteration over a large matrix (100x100)
TEST(DiagonalMatrixTest, IterationTest_LargeMatrix)
{
    const int size = 100;
    std::vector<int> values(size);
    for (int i = 0; i < size; ++i)
    {
        values[i] = i + 1;  // Initialize values 1, 2, ..., 100
    }
    DiagonalMatrix<int> largeMatrix(values);

    int count = 0;
    // Iterate through the 100x100 matrix
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (i == j)
            {
                EXPECT_EQ(largeMatrix.get(i, j), values[i]);  // Diagonal elements should match the input
            }
            else
            {
                EXPECT_EQ(largeMatrix.get(i, j), 0);  // Non-diagonal elements should be zero
            }
            count++;
        }
    }

    // Ensure we iterate over all 100x100 matrix elements
    EXPECT_EQ(count, size * size);  // Total elements for 100x100 matrix
}

// Test iteration over a 1x1 matrix (edge case)
TEST(DiagonalMatrixTest, IterationTest_SizeOne)
{
    std::vector<int> values = {42};  // A 1x1 matrix with a single value
    DiagonalMatrix<int> matrix(values);

    // Iterate through the 1x1 matrix
    EXPECT_EQ(matrix.get(0, 0), 42);  // Only one element, which should be 42
}
