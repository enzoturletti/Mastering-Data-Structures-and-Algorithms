#include <gtest/gtest.h>
#include <2.finding-duplicate-elements.hpp>
#include <dynamic-array.hpp>

// I used std::find because unordered_map will not ensure the order of the keys in the result

// Test findingDuplicateElementsInContainer with DynamicArray<int>
TEST(FindingDuplicateElementsInDynamicArray, MultipleDuplicates)
{
    DynamicArray<int> array = {1, 3, 1, 4, 5, 3};
    DynamicArray<int> expected = {1, 3};

    auto result = findingDuplicateElementsInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().getSize(), expected.getSize());

    // Check if the result contains the same elements as the expected set, regardless of order
    for (int value : expected)
    {
        EXPECT_TRUE(std::find(result.value().begin(), result.value().end(), value) != result.value().end());
    }
}

TEST(FindingDuplicateElementsInDynamicArray, NoDuplicates)
{
    DynamicArray<int> array = {1, 2, 3, 4, 5};
    auto result = findingDuplicateElementsInContainer<DynamicArray<int>>(array.begin(), array.end());

    EXPECT_FALSE(result.has_value());
}

TEST(FindingDuplicateElementsInDynamicArray, EmptyContainer)
{
    DynamicArray<int> array = {};
    auto result = findingDuplicateElementsInContainer<DynamicArray<int>>(array.begin(), array.end());

    EXPECT_FALSE(result.has_value());
}

TEST(FindingDuplicateElementsInDynamicArray, SingleElementContainer)
{
    DynamicArray<int> array = {5};
    auto result = findingDuplicateElementsInContainer<DynamicArray<int>>(array.begin(), array.end());

    EXPECT_FALSE(result.has_value());
}

TEST(FindingDuplicateElementsInDynamicArray, ConsecutiveDuplicates)
{
    DynamicArray<int> array = {1, 1, 2, 3};
    DynamicArray<int> expected = {1};

    auto result = findingDuplicateElementsInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().getSize(), expected.getSize());

    for (int value : expected)
    {
        EXPECT_TRUE(std::find(result.value().begin(), result.value().end(), value) != result.value().end());
    }
}

TEST(FindingDuplicateElementsInDynamicArray, DuplicatesWithDifferentCounts)
{
    DynamicArray<int> array = {1, 2, 2, 3, 3, 3};
    DynamicArray<int> expected = {2, 3};

    auto result = findingDuplicateElementsInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().getSize(), expected.getSize());

    for (int value : expected)
    {
        EXPECT_TRUE(std::find(result.value().begin(), result.value().end(), value) != result.value().end());
    }
}

TEST(FindingDuplicateElementsInDynamicArray, NegativeNumbers)
{
    DynamicArray<int> array = {-1, -2, -1, 3, 4, -2};
    DynamicArray<int> expected = {-1, -2};

    auto result = findingDuplicateElementsInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().getSize(), expected.getSize());

    for (int value : expected)
    {
        EXPECT_TRUE(std::find(result.value().begin(), result.value().end(), value) != result.value().end());
    }
}

TEST(FindingDuplicateElementsInDynamicArray, LargeRangeWithDuplicates)
{
    DynamicArray<int> array = {1, 2, 3, 1000, 1000, 2000};
    DynamicArray<int> expected = {1000};

    auto result = findingDuplicateElementsInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().getSize(), expected.getSize());

    for (int value : expected)
    {
        EXPECT_TRUE(std::find(result.value().begin(), result.value().end(), value) != result.value().end());
    }
}

TEST(FindingDuplicateElementsInDynamicArray, DuplicatesInUnorderedInput)
{
    DynamicArray<int> array = {3, 1, 2, 2, 3};
    DynamicArray<int> expected = {2, 3};

    auto result = findingDuplicateElementsInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().getSize(), expected.getSize());

    for (int value : expected)
    {
        EXPECT_TRUE(std::find(result.value().begin(), result.value().end(), value) != result.value().end());
    }
}

TEST(FindingDuplicateElementsInDynamicArray, AllElementsAreDuplicates)
{
    DynamicArray<int> array = {2, 2, 2, 2};
    DynamicArray<int> expected = {2};

    auto result = findingDuplicateElementsInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().getSize(), expected.getSize());

    for (int value : expected)
    {
        EXPECT_TRUE(std::find(result.value().begin(), result.value().end(), value) != result.value().end());
    }
}

TEST(FindingDuplicateElementsInDynamicArray, OnlyOneDuplicate)
{
    DynamicArray<int> array = {1, 1};
    DynamicArray<int> expected = {1};

    auto result = findingDuplicateElementsInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().getSize(), expected.getSize());

    for (int value : expected)
    {
        EXPECT_TRUE(std::find(result.value().begin(), result.value().end(), value) != result.value().end());
    }
}
