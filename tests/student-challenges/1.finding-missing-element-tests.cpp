#include <gtest/gtest.h>
#include <1.finding-missing-element.hpp>
#include <dynamic-array.hpp>

// Test findingSimpleMissingIntInSortedContainer with DynamicArray<int>
TEST(FindingMissingElementInSortedDynamicArray, BasicFunctionality)
{
    DynamicArray<int> array = {2, 4, 5};
    auto result = findingSimpleMissingIntInSortedContainer<DynamicArray<int>>(array.begin(), array.end());
    EXPECT_EQ(result, 3);
}

TEST(FindingMissingElementInSortedDynamicArray, NoMissingElement)
{
    DynamicArray<int> array = {3, 4, 5};
    auto result = findingSimpleMissingIntInSortedContainer<DynamicArray<int>>(array.begin(), array.end());
    EXPECT_EQ(result, std::nullopt);
}

TEST(FindingMissingElementInSortedDynamicArray, EmptyArray)
{
    DynamicArray<int> array = {};
    auto result = findingSimpleMissingIntInSortedContainer<DynamicArray<int>>(array.begin(), array.end());
    EXPECT_EQ(result, std::nullopt);
}

TEST(FindingMissingElementInSortedDynamicArray, SingleElementArray)
{
    DynamicArray<int> array = {1};
    auto result = findingSimpleMissingIntInSortedContainer<DynamicArray<int>>(array.begin(), array.end());
    EXPECT_EQ(result, std::nullopt);
}

TEST(FindingMissingElementInSortedDynamicArray, DuplicatesInContainer)
{
    DynamicArray<int> array = {1, 1, 3};
    int expected = 2;

    auto result = findingSimpleMissingIntInSortedContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expected);
}

// Test findingMultipleMissingIntsInSortedContainer with DynamicArray<int>
TEST(FindingMultipleMissingElementInSortedDynamicArray, MultipleMissingElements)
{
    DynamicArray<int> array = {1, 3, 6};
    DynamicArray<int> expected = {2, 4, 5};

    auto result = findingMultipleMissingIntsInSortedContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expected);
}

TEST(FindingMultipleMissingElementInSortedDynamicArray, NoMissingElements)
{
    DynamicArray<int> array = {1, 2, 3, 4, 5};
    auto result = findingMultipleMissingIntsInSortedContainer<DynamicArray<int>>(array.begin(), array.end());

    EXPECT_FALSE(result.has_value());
}

TEST(FindingMultipleMissingElementInSortedDynamicArray, EmptyContainer)
{
    DynamicArray<int> array = {};
    auto result = findingMultipleMissingIntsInSortedContainer<DynamicArray<int>>(array.begin(), array.end());

    EXPECT_FALSE(result.has_value());
}

TEST(FindingMultipleMissingElementInSortedDynamicArray, SingleElementContainer)
{
    DynamicArray<int> array = {5};
    auto result = findingMultipleMissingIntsInSortedContainer<DynamicArray<int>>(array.begin(), array.end());

    EXPECT_FALSE(result.has_value());
}

TEST(FindingMultipleMissingElementInSortedDynamicArray, ConsecutiveMissingElements)
{
    DynamicArray<int> array = {1, 5};
    DynamicArray<int> expected = {2, 3, 4};

    auto result = findingMultipleMissingIntsInSortedContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expected);
}

TEST(FindingMultipleMissingElementInSortedDynamicArray, NegativeNumbers)
{
    DynamicArray<int> array = {-3, -1, 1};
    DynamicArray<int> expected = {-2, 0};

    auto result = findingMultipleMissingIntsInSortedContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expected);
}

TEST(FindingMultipleMissingElementInSortedDynamicArray, LargeRange)
{
    DynamicArray<int> array = {1, 10};
    DynamicArray<int> expected = {2, 3, 4, 5, 6, 7, 8, 9};

    auto result = findingMultipleMissingIntsInSortedContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expected);
}

TEST(FindingMultipleMissingElementInSortedDynamicArray, DuplicatesInContainer)
{
    DynamicArray<int> array = {1, 1, 1, 3, 4, 4, 5, 7};
    DynamicArray<int> expected = {2, 6};

    auto result = findingMultipleMissingIntsInSortedContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expected);
}

TEST(FindingMultipleMissingElementInSortedDynamicArray, LargerContainer)
{
    DynamicArray<int> array = {10, 12, 15, 18, 20};
    DynamicArray<int> expected = {11, 13, 14, 16, 17, 19};

    auto result = findingMultipleMissingIntsInSortedContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expected);
}

// Test findingMultipleMissingIntInContainer with DynamicArray<int>
TEST(FindingMultipleMissingElementInDynamicArray, MultipleMissingElements)
{
    DynamicArray<int> array = {1, 3, 6};
    DynamicArray<int> expected = {2, 4, 5};

    auto result = findingMultipleMissingIntInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expected);
}

TEST(FindingMultipleMissingElementInDynamicArray, NoMissingElements)
{
    DynamicArray<int> array = {1, 2, 3, 4, 5};
    auto result = findingMultipleMissingIntInContainer<DynamicArray<int>>(array.begin(), array.end());

    EXPECT_FALSE(result.has_value());
}

TEST(FindingMultipleMissingElementInDynamicArray, EmptyContainer)
{
    DynamicArray<int> array = {};
    auto result = findingMultipleMissingIntInContainer<DynamicArray<int>>(array.begin(), array.end());

    EXPECT_FALSE(result.has_value());
}

TEST(FindingMultipleMissingElementInDynamicArray, SingleElementContainer)
{
    DynamicArray<int> array = {5};
    auto result = findingMultipleMissingIntInContainer<DynamicArray<int>>(array.begin(), array.end());

    EXPECT_FALSE(result.has_value());
}

TEST(FindingMultipleMissingElementInDynamicArray, ConsecutiveMissingElements)
{
    DynamicArray<int> array = {1, 5};
    DynamicArray<int> expected = {2, 3, 4};

    auto result = findingMultipleMissingIntInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expected);
}

TEST(FindingMultipleMissingElementInDynamicArray, NegativeNumbers)
{
    DynamicArray<int> array = {-3, -1, 1};
    DynamicArray<int> expected = {-2, 0};

    auto result = findingMultipleMissingIntInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expected);
}

TEST(FindingMultipleMissingElementInDynamicArray, LargeRange)
{
    DynamicArray<int> array = {1, 10};
    DynamicArray<int> expected = {2, 3, 4, 5, 6, 7, 8, 9};

    auto result = findingMultipleMissingIntInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expected);
}

TEST(FindingMultipleMissingElementInDynamicArray, DuplicatesInContainer)
{
    DynamicArray<int> array = {1, 1, 1, 3, 4, 4, 5, 7};
    DynamicArray<int> expected = {2, 6};

    auto result = findingMultipleMissingIntInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expected);
}

TEST(FindingMultipleMissingElementInDynamicArray, LargerContainer)
{
    DynamicArray<int> array = {10, 12, 15, 18, 20};
    DynamicArray<int> expected = {11, 13, 14, 16, 17, 19};

    auto result = findingMultipleMissingIntInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expected);
}

TEST(FindingMultipleMissingElementInDynamicArray, UnorderedInput)
{
    DynamicArray<int> array = {6, 1, 5, 3};
    DynamicArray<int> expected = {2, 4};

    auto result = findingMultipleMissingIntInContainer<DynamicArray<int>>(array.begin(), array.end());

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), expected);
}
