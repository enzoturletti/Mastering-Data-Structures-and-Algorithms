#include <gtest/gtest.h>
#include <lower-triangular-matrix.hpp>
#include <stdexcept>

// Test default constructor
TEST(LowerTriangularMatrix, ConstructorTest1)
{
    LowerTriangularMatrix<int> matrix(3, 3);  // Create a 3x3 matrix

    // Check if all lower triangular elements are initialized to the default value (0)
    EXPECT_EQ(matrix.get(0, 0), 0);
    EXPECT_EQ(matrix.get(0, 1), 0);
    EXPECT_EQ(matrix.get(0, 2), 0);

    EXPECT_EQ(matrix.get(1, 0), 0);
    EXPECT_EQ(matrix.get(1, 1), 0);
    EXPECT_EQ(matrix.get(1, 2), 0);

    EXPECT_EQ(matrix.get(2, 0), 0);
    EXPECT_EQ(matrix.get(2, 1), 0);
    EXPECT_EQ(matrix.get(2, 2), 0);
}

// Test constructor with a 2D vector
TEST(LowerTriangularMatrix, ConstructorTest2)
{
    std::vector<std::vector<int>> values = {{1, 0, 0}, {2, 3, 0}, {4, 5, 6}};

    LowerTriangularMatrix<int> matrix(values);

    EXPECT_EQ(matrix.get(0, 0), 1);
    EXPECT_EQ(matrix.get(0, 1), 0);
    EXPECT_EQ(matrix.get(0, 2), 0);

    EXPECT_EQ(matrix.get(1, 0), 2);
    EXPECT_EQ(matrix.get(1, 1), 3);
    EXPECT_EQ(matrix.get(1, 2), 0);

    EXPECT_EQ(matrix.get(2, 0), 4);
    EXPECT_EQ(matrix.get(2, 1), 5);
    EXPECT_EQ(matrix.get(2, 2), 6);
}

// Test get function with out-of-bounds indices
TEST(LowerTriangularMatrix, GetOutOfRangeTest)
{
    LowerTriangularMatrix<int> matrix(3, 3);

    // Try accessing indices out of bounds
    EXPECT_THROW(matrix.get(3, 0), std::out_of_range);
    EXPECT_THROW(matrix.get(0, 3), std::out_of_range);
}

// Test set function
TEST(LowerTriangularMatrix, SetTest)
{
    LowerTriangularMatrix<int> matrix(3, 3);

    // Set lower triangular elements
    matrix.set(0, 0, 10);
    matrix.set(1, 0, 20);
    matrix.set(1, 1, 30);
    matrix.set(2, 0, 40);
    matrix.set(2, 1, 50);
    matrix.set(2, 2, 60);

    // Verify the values set
    EXPECT_EQ(matrix.get(0, 0), 10);
    EXPECT_EQ(matrix.get(1, 0), 20);
    EXPECT_EQ(matrix.get(1, 1), 30);
    EXPECT_EQ(matrix.get(2, 0), 40);
    EXPECT_EQ(matrix.get(2, 1), 50);
    EXPECT_EQ(matrix.get(2, 2), 60);
}

// Test set function with out-of-bounds indices
TEST(LowerTriangularMatrix, SetOutOfRangeTest)
{
    LowerTriangularMatrix<int> matrix(3, 3);

    // Try setting out-of-bounds indices
    EXPECT_THROW(matrix.set(3, 0, 100), std::out_of_range);
    EXPECT_THROW(matrix.set(0, 3, 100), std::out_of_range);
}

// Test setting non-lower triangular elements
TEST(LowerTriangularMatrix, SetNonLowerTriangularTest)
{
    LowerTriangularMatrix<int> matrix(3, 3);

    // Try setting non-lower triangular elements, should throw a logic error
    EXPECT_THROW(matrix.set(0, 1, 10), std::logic_error);
    EXPECT_THROW(matrix.set(0, 2, 20), std::logic_error);
    EXPECT_THROW(matrix.set(1, 2, 30), std::logic_error);
}

// Test accessing non-lower triangular elements
TEST(LowerTriangularMatrix, GetNonLowerTriangularTest)
{
    LowerTriangularMatrix<int> matrix(3, 3);

    // Non-lower triangular elements should return default value (0)
    EXPECT_EQ(matrix.get(0, 1), 0);
    EXPECT_EQ(matrix.get(0, 2), 0);
    EXPECT_EQ(matrix.get(1, 2), 0);
}

// Test iteration over the lower triangular matrix
TEST(LowerTriangularMatrix, IterationTest)
{
    std::vector<std::vector<int>> values = {{1, 0, 0}, {2, 3, 0}, {4, 5, 6}};

    LowerTriangularMatrix<int> matrix(values);

    // Verify iteration over all lower triangular elements and check outside lower triangular elements are zero
    int count = 0;
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (i >= j)
            {
                EXPECT_EQ(matrix.get(i, j), values[i][j]);  // Lower triangular elements should match
            }
            else
            {
                EXPECT_EQ(matrix.get(i, j), 0);  // Non-lower triangular elements should be zero
            }
            count++;
        }
    }

    // Ensure we only iterate over the lower triangular elements
    EXPECT_EQ(count, 9);  // Total 3x3 matrix has 9 elements, including non-lower triangular elements
}

// Test iteration over a larger matrix
TEST(LowerTriangularMatrix, IterationTest_LargerMatrix)
{
    std::vector<std::vector<int>> values = {
        {1, 0, 0, 0, 0}, {2, 3, 0, 0, 0}, {4, 5, 6, 0, 0}, {7, 8, 9, 10, 0}, {11, 12, 13, 14, 15}};

    LowerTriangularMatrix<int> matrix(values);

    // Verify iteration over all lower triangular elements and check outside lower triangular elements are zero
    int count = 0;
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            if (i >= j)
            {
                EXPECT_EQ(matrix.get(i, j), values[i][j]);  // Lower triangular elements should match
            }
            else
            {
                EXPECT_EQ(matrix.get(i, j), 0);  // Non-lower triangular elements should be zero
            }
            count++;
        }
    }

    // Ensure we only iterate over the total elements (5x5 matrix)
    EXPECT_EQ(count, 25);  // Total 5x5 matrix has 25 elements
}

// Test iterating over a 4x4 matrix
TEST(LowerTriangularMatrix, IterationTest_4x4)
{
    std::vector<std::vector<int>> values = {{1, 0, 0, 0}, {2, 3, 0, 0}, {4, 5, 6, 0}, {7, 8, 9, 10}};

    LowerTriangularMatrix<int> matrix(values);

    // Verify iteration over all lower triangular elements and check outside lower triangular elements are zero
    int count = 0;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            if (i >= j)
            {
                EXPECT_EQ(matrix.get(i, j), values[i][j]);  // Lower triangular elements should match
            }
            else
            {
                EXPECT_EQ(matrix.get(i, j), 0);  // Non-lower triangular elements should be zero
            }
            count++;
        }
    }

    // Ensure we only iterate over the total elements (4x4 matrix)
    EXPECT_EQ(count, 16);  // Total 4x4 matrix has 16 elements
}
