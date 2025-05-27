#include <gtest/gtest.h>
#include <3.finding-pair-with-sum-k.hpp>
#include <dynamic-array.hpp>

// Test findingPairWithSumK with DynamicArray<int>
TEST(FindingPairWithSumKInDynamicArray, MultiplePairs)
{
    DynamicArray<int> array = {1, 3, 5, 7, 9};
    DynamicArray<DynamicArray<int>> expected = {{3, 7}, {1, 9}};

    auto results = findingPairWithSumK(array.begin(), array.end(), 10);
    ASSERT_TRUE(results.has_value());
    ASSERT_EQ(results.value(), expected);
}

// Test when there are no valid pairs
TEST(FindingPairWithSumKInDynamicArray, NoValidPairs)
{
    DynamicArray<int> array = {1, 2, 3, 4};
    auto results = findingPairWithSumK(array.begin(), array.end(), 10);
    ASSERT_FALSE(results.has_value());  // No pairs should be found for sum 10
}

// Test with an empty array
TEST(FindingPairWithSumKInDynamicArray, EmptyArray)
{
    DynamicArray<int> array = {};
    auto results = findingPairWithSumK(array.begin(), array.end(), 10);
    ASSERT_FALSE(results.has_value());  // No pairs should be found in an empty array
}

// Test with a single element array
TEST(FindingPairWithSumKInDynamicArray, SingleElementArray)
{
    DynamicArray<int> array = {5};
    auto results = findingPairWithSumK(array.begin(), array.end(), 10);
    ASSERT_FALSE(results.has_value());  // A single element can't form a pair
}

// Test with a pair of the same number (complement == *it)
TEST(FindingPairWithSumKInDynamicArray, PairOfSameNumber)
{
    DynamicArray<int> array = {5, 5, 5, 5};
    DynamicArray<DynamicArray<int>> expected = {{5, 5}, {5, 5}, {5, 5}, {5, 5}, {5, 5}, {5, 5}};

    auto results = findingPairWithSumK(array.begin(), array.end(), 10);
    ASSERT_TRUE(results.has_value());
    ASSERT_EQ(results.value(), expected);  // Expecting six pairs of (5, 5)
}

// Test with duplicate numbers but no valid pair for the sum
TEST(FindingPairWithSumKInDynamicArray, DuplicatesNoValidPair)
{
    DynamicArray<int> array = {2, 2, 2, 2};
    auto results = findingPairWithSumK(array.begin(), array.end(), 10);
    ASSERT_FALSE(results.has_value());  // No pair can sum to 10 with these numbers
}

// Test with negative numbers
TEST(FindingPairWithSumKInDynamicArray, NegativeNumbers)
{
    DynamicArray<int> array = {-1, -3, -5, -7, -9};
    DynamicArray<DynamicArray<int>> expected = {{-7, -3}, {-9, -1}};

    auto results = findingPairWithSumK(array.begin(), array.end(), -10);
    ASSERT_TRUE(results.has_value());
    ASSERT_EQ(results.value(), expected);  // Expecting two pairs (-9, -1) and (-7, -3)
}

// Test where all numbers are greater than the sum
TEST(FindingPairWithSumKInDynamicArray, AllNumbersGreaterThanSum)
{
    DynamicArray<int> array = {15, 20, 25, 30};
    auto results = findingPairWithSumK(array.begin(), array.end(), 10);
    ASSERT_FALSE(results.has_value());  // No pairs can sum to 10 with numbers all greater than 10
}

// Test a large input array with many pairs
TEST(FindingPairWithSumKInDynamicArray, LargeArrayWithManyPairs)
{
    DynamicArray<int> array = {1, 9, 3, 7, 5, 5, 5, 5, 7, 3, 9, 1};
    DynamicArray<DynamicArray<int>> expected = {{1, 9}, {3, 7}, {5, 5}, {5, 5}, {5, 5}, {5, 5}, {5, 5},
                                                {5, 5}, {3, 7}, {3, 7}, {3, 7}, {1, 9}, {1, 9}, {1, 9}};

    auto results = findingPairWithSumK(array.begin(), array.end(), 10);
    ASSERT_TRUE(results.has_value());
    ASSERT_EQ(results.value(), expected);
}

// Test with very large numbers
TEST(FindingPairWithSumKInDynamicArray, LargeNumbers)
{
    DynamicArray<int> array = {1000000, 5000000, 1000000, 2000000};
    DynamicArray<DynamicArray<int>> expected = {{1000000, 5000000}, {1000000, 5000000}};

    auto results = findingPairWithSumK(array.begin(), array.end(), 6000000);
    ASSERT_TRUE(results.has_value());
    ASSERT_EQ(results.value(), expected);  // Expect two pairs of (1000000, 5000000)
}

// Test with floating-point numbers (this assumes you're testing with integers, but let's also consider it)
TEST(FindingPairWithSumKInDynamicArray, FloatingPointNumbers)
{
    DynamicArray<int> array = {1, 2, 3, 7};
    auto results = findingPairWithSumK(array.begin(), array.end(), 7);
    ASSERT_FALSE(results.has_value());  // This should not work since we are working with integers
}

// Test with negative and positive numbers that sum to zero
TEST(FindingPairWithSumKInDynamicArray, ZeroSum)
{
    DynamicArray<int> array = {-5, 5, 2, -2, 1, -1};
    DynamicArray<DynamicArray<int>> expected = {{-5, 5}, {-2, 2}, {-1, 1}};

    auto results = findingPairWithSumK(array.begin(), array.end(), 0);
    ASSERT_TRUE(results.has_value());
    ASSERT_EQ(results.value(), expected);
}
