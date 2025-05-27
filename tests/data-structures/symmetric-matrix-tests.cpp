#include <gtest/gtest.h>
#include <stdexcept>
#include <symmetric-matrix.hpp>  // Assuming the SymmetricMatrix class is in this header

// Test default constructor
TEST(SymmetricMatrixTest, ConstructorTest1)
{
    SymmetricMatrix<int> matrix(3, 3);  // Create a 3x3 matrix

    // Check if all elements are initialized to the default value (0)
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
TEST(SymmetricMatrixTest, ConstructorTest2)
{
    std::vector<std::vector<int>> values = {{1, 2, 3}, {2, 4, 5}, {3, 5, 6}};

    SymmetricMatrix<int> matrix(values);

    // Verify values for the symmetric matrix elements
    EXPECT_EQ(matrix.get(0, 0), 1);
    EXPECT_EQ(matrix.get(1, 0), 2);
    EXPECT_EQ(matrix.get(1, 1), 4);
    EXPECT_EQ(matrix.get(2, 0), 3);
    EXPECT_EQ(matrix.get(2, 1), 5);
    EXPECT_EQ(matrix.get(2, 2), 6);

    // Test symmetry (i, j) and (j, i) should be the same
    EXPECT_EQ(matrix.get(0, 1), 2);
    EXPECT_EQ(matrix.get(0, 2), 3);
    EXPECT_EQ(matrix.get(1, 2), 5);

    // Non-symmetric elements are implicitly handled by the matrix implementation
    EXPECT_EQ(matrix.get(1, 0), 2);
    EXPECT_EQ(matrix.get(2, 0), 3);
    EXPECT_EQ(matrix.get(2, 1), 5);
}

// Test get function with out-of-bounds indices
TEST(SymmetricMatrixTest, GetOutOfRangeTest)
{
    SymmetricMatrix<int> matrix(3, 3);

    // Try accessing indices out of bounds
    EXPECT_THROW(matrix.get(3, 0), std::out_of_range);
    EXPECT_THROW(matrix.get(0, 3), std::out_of_range);
}

// Test set function
TEST(SymmetricMatrixTest, SetTest)
{
    SymmetricMatrix<int> matrix(3, 3);

    // Set symmetric elements
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

    // Test symmetry (i, j) and (j, i) should be the same
    EXPECT_EQ(matrix.get(0, 1), 20);
    EXPECT_EQ(matrix.get(0, 2), 40);
    EXPECT_EQ(matrix.get(1, 2), 50);
}

// Test set function with out-of-bounds indices
TEST(SymmetricMatrixTest, SetOutOfRangeTest)
{
    SymmetricMatrix<int> matrix(3, 3);

    // Try setting out-of-bounds indices
    EXPECT_THROW(matrix.set(3, 0, 100), std::out_of_range);
    EXPECT_THROW(matrix.set(0, 3, 100), std::out_of_range);
}

// Test accessing non-symmetric elements
TEST(SymmetricMatrixTest, GetNonSymmetricTest)
{
    SymmetricMatrix<int> matrix(3, 3);

    // Non-symmetric elements should return the corresponding symmetric value
    EXPECT_EQ(matrix.get(0, 1), matrix.get(1, 0));
    EXPECT_EQ(matrix.get(0, 2), matrix.get(2, 0));
    EXPECT_EQ(matrix.get(1, 2), matrix.get(2, 1));
}

// Test iteration over the symmetric matrix
TEST(SymmetricMatrixTest, IterationTest)
{
    std::vector<std::vector<int>> values = {{1, 2, 3}, {2, 4, 5}, {3, 5, 6}};

    SymmetricMatrix<int> matrix(values);

    // Verify iteration over all symmetric matrix elements and check symmetry
    int count = 0;
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (i <= j)
            {
                EXPECT_EQ(matrix.get(i, j), values[i][j]);  // Symmetric elements should match
                EXPECT_EQ(matrix.get(j, i), values[i][j]);  // Symmetric elements should match
            }
            else
            {
                EXPECT_EQ(matrix.get(i, j), matrix.get(j, i));  // Ensure symmetry is preserved
            }
            count++;
        }
    }

    // Ensure we only iterate over the total elements (3x3 matrix)
    EXPECT_EQ(count, 9);  // Total 3x3 matrix has 9 elements
}

// Test iteration over a larger matrix
TEST(SymmetricMatrixTest, IterationTest_LargerMatrix)
{
    std::vector<std::vector<int>> values = {
        {1, 2, 3, 4, 5}, {2, 6, 7, 8, 9}, {3, 7, 10, 11, 12}, {4, 8, 11, 13, 14}, {5, 9, 12, 14, 15}};

    SymmetricMatrix<int> matrix(values);

    // Verify iteration over all symmetric matrix elements and check symmetry
    int count = 0;
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            if (i <= j)
            {
                EXPECT_EQ(matrix.get(i, j), values[i][j]);  // Symmetric elements should match
                EXPECT_EQ(matrix.get(j, i), values[i][j]);  // Symmetric elements should match
            }
            else
            {
                EXPECT_EQ(matrix.get(i, j), matrix.get(j, i));  // Ensure symmetry is preserved
            }
            count++;
        }
    }

    // Ensure we only iterate over the total elements (5x5 matrix)
    EXPECT_EQ(count, 25);  // Total 5x5 matrix has 25 elements
}

// Test iterating over a 4x4 matrix
TEST(SymmetricMatrixTest, IterationTest_4x4)
{
    std::vector<std::vector<int>> values = {{1, 2, 3, 4}, {2, 5, 6, 7}, {3, 6, 8, 9}, {4, 7, 9, 10}};

    SymmetricMatrix<int> matrix(values);

    // Verify iteration over all symmetric matrix elements and check symmetry
    int count = 0;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            if (i <= j)
            {
                EXPECT_EQ(matrix.get(i, j), values[i][j]);  // Symmetric elements should match
                EXPECT_EQ(matrix.get(j, i), values[i][j]);  // Symmetric elements should match
            }
            else
            {
                EXPECT_EQ(matrix.get(i, j), matrix.get(j, i));  // Ensure symmetry is preserved
            }
            count++;
        }
    }

    // Ensure we only iterate over the total elements (4x4 matrix)
    EXPECT_EQ(count, 16);  // Total 4x4 matrix has 16 elements
}
