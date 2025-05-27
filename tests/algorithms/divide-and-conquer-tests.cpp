#include <gtest/gtest.h>
#include <divide-and-conquer.hpp>

TEST(BinarySearchTest, FindsElementInMiddle)
{
    std::vector<int> data = {1, 3, 5, 7, 9};
    auto result = binarySearch(data, 5);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 2);
}

TEST(BinarySearchTest, FindsElementAtBeginning)
{
    std::vector<int> data = {2, 4, 6, 8};
    auto result = binarySearch(data, 2);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 0);
}

TEST(BinarySearchTest, FindsElementAtEnd)
{
    std::vector<int> data = {10, 20, 30, 40, 50};
    auto result = binarySearch(data, 50);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 4);
}

TEST(BinarySearchTest, DoesNotFindElement)
{
    std::vector<int> data = {1, 3, 5, 7, 9};
    auto result = binarySearch(data, 6);
    EXPECT_FALSE(result.has_value());
}

TEST(BinarySearchTest, EmptyVector)
{
    std::vector<int> data;
    auto result = binarySearch(data, 10);
    EXPECT_FALSE(result.has_value());
}

TEST(BinarySearchTest, SingleElementFound)
{
    std::vector<int> data = {42};
    auto result = binarySearch(data, 42);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 0);
}

TEST(BinarySearchTest, SingleElementNotFound)
{
    std::vector<int> data = {42};
    auto result = binarySearch(data, 7);
    EXPECT_FALSE(result.has_value());
}

TEST(BinarySearchTest, LargeVectorElementExists)
{
    std::vector<int> data(1000);
    for (int i = 0; i < 1000; ++i)
    {
        data[i] = i * 2;
    }
    auto result = binarySearch(data, 198);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 99);
}

TEST(BinarySearchTest, LargeVectorElementMissing)
{
    std::vector<int> data(1000);
    for (int i = 0; i < 1000; ++i)
    {
        data[i] = i * 2;
    }
    auto result = binarySearch(data, 199);
    EXPECT_FALSE(result.has_value());
}

TEST(MergeKSortRecursiveTest, EmptyInput)
{
    std::vector<std::vector<int>> input;
    auto result = mergeKSort<true>(input);
    EXPECT_FALSE(result.has_value());
}

TEST(MergeKSortRecursiveTest, SingleVector)
{
    std::vector<std::vector<int>> input = {{1, 3, 5, 7}};
    auto result = mergeKSort<true>(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), (std::vector<int>{1, 3, 5, 7}));
}

TEST(MergeKSortRecursiveTest, TwoVectors)
{
    std::vector<std::vector<int>> input = {{1, 4, 6}, {2, 3, 5}};
    auto result = mergeKSort<true>(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), (std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(MergeKSortRecursiveTest, MultipleVectors)
{
    std::vector<std::vector<int>> input = {{1, 4, 9}, {2, 3, 5}, {0, 6, 7}, {8, 10, 11}, {12, 13, 14}};
    auto result = mergeKSort<true>(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), (std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}));
}

TEST(MergeKSortRecursiveTest, VectorsWithEmptyVectors)
{
    std::vector<std::vector<int>> input = {{}, {1, 2}, {}, {0, 3}};
    auto result = mergeKSort<true>(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), (std::vector<int>{0, 1, 2, 3}));
}

TEST(MergeKSortRecursiveTest, SingleEmptyVector)
{
    std::vector<std::vector<int>> input = {{}};
    auto result = mergeKSort<true>(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result.value().empty());
}

// Iterative mode tests
TEST(MergeKSortIterativeTest, EmptyInput)
{
    std::vector<std::vector<int>> input;
    auto result = mergeKSort<false>(input);
    EXPECT_FALSE(result.has_value());
}

TEST(MergeKSortIterativeTest, SingleVector)
{
    std::vector<std::vector<int>> input = {{1, 3, 5, 7}};
    auto result = mergeKSort<false>(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), (std::vector<int>{1, 3, 5, 7}));
}

TEST(MergeKSortIterativeTest, TwoVectors)
{
    std::vector<std::vector<int>> input = {{1, 4, 6}, {2, 3, 5}};
    auto result = mergeKSort<false>(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), (std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(MergeKSortIterativeTest, MultipleVectors)
{
    std::vector<std::vector<int>> input = {{1, 4, 9}, {2, 3, 5}, {0, 6, 7}, {8, 10, 11}, {12, 13, 14}};
    auto result = mergeKSort<false>(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), (std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}));
}

TEST(MergeKSortIterativeTest, VectorsWithEmptyVectors)
{
    std::vector<std::vector<int>> input = {{}, {1, 2}, {}, {0, 3}};
    auto result = mergeKSort<false>(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), (std::vector<int>{0, 1, 2, 3}));
}

TEST(MergeKSortIterativeTest, SingleEmptyVector)
{
    std::vector<std::vector<int>> input = {{}};
    auto result = mergeKSort<false>(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result.value().empty());
}

// ------------------------
// Matrix multiplication Tests
// ------------------------

bool areEqual(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B)
{
    if (A.size() != B.size())
        return false;
    for (size_t i = 0; i < A.size(); ++i)
    {
        if (A[i] != B[i])
            return false;
    }
    return true;
}

TEST(MatrixMultiplicationTest, IdentityMatrix2x2)
{
    std::vector<std::vector<int>> A = {{1, 0}, {0, 1}};
    std::vector<std::vector<int>> B = {{5, 7}, {9, 11}};
    auto expected = B;
    auto result = matrixMultiplication(A, B);
    EXPECT_TRUE(areEqual(result, expected));
}

TEST(MatrixMultiplicationTest, ZeroMatrix2x2)
{
    std::vector<std::vector<int>> A = {{0, 0}, {0, 0}};
    std::vector<std::vector<int>> B = {{3, 4}, {5, 6}};
    std::vector<std::vector<int>> expected = {{0, 0}, {0, 0}};
    auto result = matrixMultiplication(A, B);
    EXPECT_TRUE(areEqual(result, expected));
}

TEST(MatrixMultiplicationTest, SimpleMatrix2x2)
{
    std::vector<std::vector<int>> A = {{1, 2}, {3, 4}};
    std::vector<std::vector<int>> B = {{5, 6}, {7, 8}};
    std::vector<std::vector<int>> expected = {{1 * 5 + 2 * 7, 1 * 6 + 2 * 8}, {3 * 5 + 4 * 7, 3 * 6 + 4 * 8}};
    auto result = matrixMultiplication(A, B);
    EXPECT_TRUE(areEqual(result, expected));
}

TEST(MatrixMultiplicationTest, Matrix4x4)
{
    std::vector<std::vector<int>> A = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    std::vector<std::vector<int>> B = {{17, 18, 19, 20}, {21, 22, 23, 24}, {25, 26, 27, 28}, {29, 30, 31, 32}};
    std::vector<std::vector<int>> expected = {
        {250, 260, 270, 280}, {618, 644, 670, 696}, {986, 1028, 1070, 1112}, {1354, 1412, 1470, 1528}};
    auto result = matrixMultiplication(A, B);
    EXPECT_TRUE(areEqual(result, expected));
}

TEST(MatrixMultiplicationTest, ThrowsOnEmptyMatrix)
{
    std::vector<std::vector<int>> A = {};
    std::vector<std::vector<int>> B = {{1, 2}, {3, 4}};
    EXPECT_THROW(matrixMultiplication(A, B), std::invalid_argument);
}

TEST(MatrixMultiplicationTest, ThrowsOnNonSquareMatrix)
{
    std::vector<std::vector<int>> A = {{1, 2}};
    std::vector<std::vector<int>> B = {{3, 4}, {5, 6}};
    EXPECT_THROW(matrixMultiplication(A, B), std::invalid_argument);
}

TEST(MatrixMultiplicationTest, ThrowsOnMismatchedSizes)
{
    std::vector<std::vector<int>> A = {{1, 2}, {3, 4}};
    std::vector<std::vector<int>> B = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_THROW(matrixMultiplication(A, B), std::invalid_argument);
}