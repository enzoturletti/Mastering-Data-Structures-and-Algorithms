#include <gtest/gtest.h>
#include <dynamic-array.hpp>
#include <is-sorted.hpp>
#include <list.hpp>
#include <static-array.hpp>

template <typename ContainerType>
class IsSortedAlgorithmsTestWithInt : public testing::Test
{
};

// Define the container types to be tested for integers
using ContainerTypesInt = ::testing::Types<DynamicArray<int>, List<int>>;

TYPED_TEST_SUITE(IsSortedAlgorithmsTestWithInt, ContainerTypesInt);

// Test isSorted with TypeParam in Ascending Order
TYPED_TEST(IsSortedAlgorithmsTestWithInt, AscendingOrder)
{
    TypeParam sorted = {1, 2, 3, 4, 5};
    TypeParam unsorted = {1, 3, 2, 5, 4};
    TypeParam singleElement = {42};
    TypeParam empty = {};

    // Test sorted in ascending order
    EXPECT_TRUE(isSorted(sorted.begin(), sorted.end(), SortOrder::Ascending));

    // Test unsorted in ascending order
    EXPECT_FALSE(isSorted(unsorted.begin(), unsorted.end(), SortOrder::Ascending));

    // Test single element array (should be considered sorted)
    EXPECT_TRUE(isSorted(singleElement.begin(), singleElement.end(), SortOrder::Ascending));

    // Test empty array (should be considered sorted)
    EXPECT_TRUE(isSorted(empty.begin(), empty.end(), SortOrder::Ascending));
}

// Test isSorted with TypeParam in Descending Order
TYPED_TEST(IsSortedAlgorithmsTestWithInt, DescendingOrder)
{
    TypeParam sortedDescending = {5, 4, 3, 2, 1};
    TypeParam unsorted = {1, 3, 2, 5, 4};
    TypeParam singleElement = {42};
    TypeParam empty = {};

    // Test sorted in descending order
    EXPECT_TRUE(isSorted(sortedDescending.begin(), sortedDescending.end(), SortOrder::Descending));

    // Test unsorted in descending order
    EXPECT_FALSE(isSorted(unsorted.begin(), unsorted.end(), SortOrder::Descending));

    // Test single element array (should be considered sorted)
    EXPECT_TRUE(isSorted(singleElement.begin(), singleElement.end(), SortOrder::Descending));

    // Test empty array (should be considered sorted)
    EXPECT_TRUE(isSorted(empty.begin(), empty.end(), SortOrder::Descending));
}

// Test isSorted with TypeParam for Equal Values
TYPED_TEST(IsSortedAlgorithmsTestWithInt, EqualValues)
{
    TypeParam equalValues = {3, 3, 3, 3, 3};

    // Test sorted in ascending order
    EXPECT_TRUE(isSorted(equalValues.begin(), equalValues.end(), SortOrder::Ascending));

    // Test sorted in descending order
    EXPECT_TRUE(isSorted(equalValues.begin(), equalValues.end(), SortOrder::Descending));
}

// Test isSorted with TypeParam for Unordered Range
TYPED_TEST(IsSortedAlgorithmsTestWithInt, UnorderedRange)
{
    TypeParam unordered = {5, 3, 4, 2, 1};

    // Test unordered range in ascending order
    EXPECT_FALSE(isSorted(unordered.begin(), unordered.end(), SortOrder::Ascending));

    // Test unordered range in descending order
    EXPECT_FALSE(isSorted(unordered.begin(), unordered.end(), SortOrder::Descending));
}

// Test isSorted with StaticArray<int> in Ascending Order
TEST(IsSortedStaticArrayInt, AscendingOrder)
{
    StaticArray<int, 5> sorted = {1, 2, 3, 4, 5};
    StaticArray<int, 5> unsorted = {1, 3, 2, 5, 4};
    StaticArray<int, 1> singleElement = {42};
    StaticArray<int, 0> empty = {};

    // Test sorted in ascending order
    EXPECT_TRUE(isSorted(sorted.begin(), sorted.end(), SortOrder::Ascending));

    // Test unsorted in ascending order
    EXPECT_FALSE(isSorted(unsorted.begin(), unsorted.end(), SortOrder::Ascending));

    // Test single element array (should be considered sorted)
    EXPECT_TRUE(isSorted(singleElement.begin(), singleElement.end(), SortOrder::Ascending));

    // Test empty array (should be considered sorted)
    EXPECT_TRUE(isSorted(empty.begin(), empty.end(), SortOrder::Ascending));
}

// Test isSorted with StaticArray<int> in Descending Order
TEST(IsSortedStaticArrayInt, DescendingOrder)
{
    StaticArray<int, 5> sortedDescending = {5, 4, 3, 2, 1};
    StaticArray<int, 5> unsorted = {1, 3, 2, 5, 4};
    StaticArray<int, 1> singleElement = {42};
    StaticArray<int, 0> empty = {};

    // Test sorted in descending order
    EXPECT_TRUE(isSorted(sortedDescending.begin(), sortedDescending.end(), SortOrder::Descending));

    // Test unsorted in descending order
    EXPECT_FALSE(isSorted(unsorted.begin(), unsorted.end(), SortOrder::Descending));

    // Test single element array (should be considered sorted)
    EXPECT_TRUE(isSorted(singleElement.begin(), singleElement.end(), SortOrder::Descending));

    // Test empty array (should be considered sorted)
    EXPECT_TRUE(isSorted(empty.begin(), empty.end(), SortOrder::Descending));
}

// Test isSorted with StaticArray<int> for Equal Values
TEST(IsSortedStaticArrayInt, EqualValues)
{
    StaticArray<int, 5> equalValues = {3, 3, 3, 3, 3};

    // Test sorted in ascending order
    EXPECT_TRUE(isSorted(equalValues.begin(), equalValues.end(), SortOrder::Ascending));

    // Test sorted in descending order
    EXPECT_TRUE(isSorted(equalValues.begin(), equalValues.end(), SortOrder::Descending));
}

// Test isSorted with StaticArray<int> for Unordered Range
TEST(IsSortedStaticArrayInt, UnorderedRange)
{
    StaticArray<int, 5> unordered = {5, 3, 4, 2, 1};

    // Test unordered range in ascending order
    EXPECT_FALSE(isSorted(unordered.begin(), unordered.end(), SortOrder::Ascending));

    // Test unordered range in descending order
    EXPECT_FALSE(isSorted(unordered.begin(), unordered.end(), SortOrder::Descending));
}

template <typename ContainerType>
class IsSortedAlgorithmsTestWithString : public testing::Test
{
};

// Define the container types to be tested for strings
using ContainerTypesString = ::testing::Types<DynamicArray<std::string>, List<std::string>>;

TYPED_TEST_SUITE(IsSortedAlgorithmsTestWithString, ContainerTypesString);

// Test isSorted with TypeParam in Ascending Order
TYPED_TEST(IsSortedAlgorithmsTestWithString, AscendingOrder)
{
    TypeParam sorted = {"apple", "banana", "cherry", "date", "elderberry"};
    TypeParam unsorted = {"apple", "cherry", "banana", "elderberry", "date"};
    TypeParam singleElement = {"apple"};
    TypeParam empty = {};

    // Test sorted in ascending order
    EXPECT_TRUE(isSorted(sorted.begin(), sorted.end(), SortOrder::Ascending));

    // Test unsorted in ascending order
    EXPECT_FALSE(isSorted(unsorted.begin(), unsorted.end(), SortOrder::Ascending));

    // Test single element array (should be considered sorted)
    EXPECT_TRUE(isSorted(singleElement.begin(), singleElement.end(), SortOrder::Ascending));

    // Test empty array (should be considered sorted)
    EXPECT_TRUE(isSorted(empty.begin(), empty.end(), SortOrder::Ascending));
}

// Test isSorted with TypeParam in Descending Order
TYPED_TEST(IsSortedAlgorithmsTestWithString, DescendingOrder)
{
    TypeParam sortedDescending = {"elderberry", "date", "cherry", "banana", "apple"};
    TypeParam unsorted = {"apple", "cherry", "banana", "elderberry", "date"};
    TypeParam singleElement = {"apple"};
    TypeParam empty = {};

    // Test sorted in descending order
    EXPECT_TRUE(isSorted(sortedDescending.begin(), sortedDescending.end(), SortOrder::Descending));

    // Test unsorted in descending order
    EXPECT_FALSE(isSorted(unsorted.begin(), unsorted.end(), SortOrder::Descending));

    // Test single element array (should be considered sorted)
    EXPECT_TRUE(isSorted(singleElement.begin(), singleElement.end(), SortOrder::Descending));

    // Test empty array (should be considered sorted)
    EXPECT_TRUE(isSorted(empty.begin(), empty.end(), SortOrder::Descending));
}

// Test isSorted with TypeParam for Equal Values
TYPED_TEST(IsSortedAlgorithmsTestWithString, EqualValues)
{
    TypeParam equalValues = {"apple", "apple", "apple", "apple", "apple"};

    // Test sorted in ascending order
    EXPECT_TRUE(isSorted(equalValues.begin(), equalValues.end(), SortOrder::Ascending));

    // Test sorted in descending order
    EXPECT_TRUE(isSorted(equalValues.begin(), equalValues.end(), SortOrder::Descending));
}

// Test isSorted with TypeParam for Unordered Range
TYPED_TEST(IsSortedAlgorithmsTestWithString, UnorderedRange)
{
    TypeParam unordered = {"banana", "apple", "cherry", "date", "elderberry"};

    // Test unordered range in ascending order
    EXPECT_FALSE(isSorted(unordered.begin(), unordered.end(), SortOrder::Ascending));

    // Test unordered range in descending order
    EXPECT_FALSE(isSorted(unordered.begin(), unordered.end(), SortOrder::Descending));
}

// Test isSorted with StaticArray<std::string> in Ascending Order
TEST(IsSortedStaticArrayString, AscendingOrder)
{
    StaticArray<std::string, 5> sorted = {"apple", "banana", "cherry", "date", "elderberry"};
    StaticArray<std::string, 5> unsorted = {"apple", "cherry", "banana", "elderberry", "date"};
    StaticArray<std::string, 1> singleElement = {"apple"};
    StaticArray<std::string, 0> empty = {};

    // Test sorted in ascending order
    EXPECT_TRUE(isSorted(sorted.begin(), sorted.end(), SortOrder::Ascending));

    // Test unsorted in ascending order
    EXPECT_FALSE(isSorted(unsorted.begin(), unsorted.end(), SortOrder::Ascending));

    // Test single element array (should be considered sorted)
    EXPECT_TRUE(isSorted(singleElement.begin(), singleElement.end(), SortOrder::Ascending));

    // Test empty array (should be considered sorted)
    EXPECT_TRUE(isSorted(empty.begin(), empty.end(), SortOrder::Ascending));
}

// Test isSorted with StaticArray<std::string> in Descending Order
TEST(IsSortedStaticArrayString, DescendingOrder)
{
    StaticArray<std::string, 5> sortedDescending = {"elderberry", "date", "cherry", "banana", "apple"};
    StaticArray<std::string, 5> unsorted = {"apple", "cherry", "banana", "elderberry", "date"};
    StaticArray<std::string, 1> singleElement = {"apple"};
    StaticArray<std::string, 0> empty = {};

    // Test sorted in descending order
    EXPECT_TRUE(isSorted(sortedDescending.begin(), sortedDescending.end(), SortOrder::Descending));

    // Test unsorted in descending order
    EXPECT_FALSE(isSorted(unsorted.begin(), unsorted.end(), SortOrder::Descending));

    // Test single element array (should be considered sorted)
    EXPECT_TRUE(isSorted(singleElement.begin(), singleElement.end(), SortOrder::Descending));

    // Test empty array (should be considered sorted)
    EXPECT_TRUE(isSorted(empty.begin(), empty.end(), SortOrder::Descending));
}
