#include <gtest/gtest.h>

#include <binary-search.hpp>
#include <dynamic-array.hpp>
#include <linear-search.hpp>
#include <list.hpp>
#include <static-array.hpp>

// Templated test fixture for both DynamicArray, StaticArray and List with `int`
template <typename ContainerType>
class SearchAlgortithmsTestWithInt : public testing::Test
{
public:
    ContainerType mContainer = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};  // Use aggregate initialization
};

// Define the mContainer types to be tested for integers
using ContainerTypesInt = ::testing::Types<DynamicArray<int>, StaticArray<int, 10>, List<int>>;

TYPED_TEST_SUITE(SearchAlgortithmsTestWithInt, ContainerTypesInt);

// Test linear search with integers
TYPED_TEST(SearchAlgortithmsTestWithInt, LinearSearch)
{
    auto result = linearSearch(this->mContainer.begin(), this->mContainer.end(), 20);
    EXPECT_NE(result, this->mContainer.end());
    EXPECT_EQ(*result, 20);

    result = linearSearch(this->mContainer.begin(), this->mContainer.end(), 10);
    EXPECT_NE(result, this->mContainer.end());
    EXPECT_EQ(*result, 10);

    result = linearSearch(this->mContainer.begin(), this->mContainer.end(), 30);
    EXPECT_NE(result, this->mContainer.end());
    EXPECT_EQ(*result, 30);

    result = linearSearch(this->mContainer.begin(), this->mContainer.end(), 101);
    EXPECT_EQ(result, this->mContainer.end());
}

// Test binary search in the mContainer
TYPED_TEST(SearchAlgortithmsTestWithInt, BinarySearchElementFound)
{
    auto it = binarySearch(this->mContainer.begin(), this->mContainer.end(), 20);
    EXPECT_EQ(*it, 20);
}

// Test binary search non succesful in the mContainer
TYPED_TEST(SearchAlgortithmsTestWithInt, BinarySearchElementNotFound)
{
    // Search for an element that does not exist
    auto it = binarySearch(this->mContainer.begin(), this->mContainer.end(), 55);

    // Verify that the iterator points to end when element is not found
    EXPECT_EQ(it, this->mContainer.end());
}

TYPED_TEST(SearchAlgortithmsTestWithInt, BinarySearchFirstElement)
{
    // Search for the first element
    auto it = binarySearch(this->mContainer.begin(), this->mContainer.end(), 10);

    // Verify that the iterator points to the first element
    EXPECT_EQ(*it, 10);
}

TYPED_TEST(SearchAlgortithmsTestWithInt, BinarySearchLastElement)
{
    // Search for the last element
    auto it = binarySearch(this->mContainer.begin(), this->mContainer.end(), 100);

    // Verify that the iterator points to the last element
    EXPECT_EQ(*it, 100);
}

TYPED_TEST(SearchAlgortithmsTestWithInt, BinarySearchEmptyArray)
{
    TypeParam container;

    // Search in an empty mContainer
    auto it = binarySearch(container.begin(), container.end(), 10);

    // Verify that the iterator points to the end of the mContainer
    EXPECT_EQ(it, container.end());
}

TYPED_TEST(SearchAlgortithmsTestWithInt, BinarySearchElementNotInArray)
{
    // Search for an element that is not in the mContainer
    auto it = binarySearch(this->mContainer.begin(), this->mContainer.begin(), 25);

    // Verify that the iterator points to the end
    EXPECT_EQ(it, this->mContainer.begin());
}

TYPED_TEST(SearchAlgortithmsTestWithInt, BinarySearchDuplicateElements)
{
    TypeParam container = {10, 20, 20, 20, 30};

    // Search for the value 20, which appears multiple times
    auto it = binarySearch(container.begin(), container.end(), 20);

    // Verify that the iterator points to the first occurrence of 20
    EXPECT_EQ(*it, 20);
}

TYPED_TEST(SearchAlgortithmsTestWithInt, BinarySearchNegativeValues)
{
    TypeParam container = {-50, -40, -30, -20, -10};

    // Search for a negative value
    auto it = binarySearch(container.begin(), container.end(), -30);

    // Verify that the iterator points to the correct element
    EXPECT_EQ(*it, -30);
}

TYPED_TEST(SearchAlgortithmsTestWithInt, BinarySearchOneElementFound)
{
    TypeParam container = {10};

    // Search for the only element in the mContainer
    auto it = binarySearch(container.begin(), container.end(), 10);

    // Verify that the iterator points to the correct element
    EXPECT_EQ(*it, 10);
}

TYPED_TEST(SearchAlgortithmsTestWithInt, BinarySearchOneElementNotFound)
{
    TypeParam container = {10};

    // Search for an element that doesn't exist in the mContainer
    auto it = binarySearch(container.begin(), container.end(), 20);

    // Verify that the iterator points to end since the element is not in the mContainer
    EXPECT_EQ(it, container.end());
}

//////////////////////////////////////////////////////////////////////////////////

// Additional test cases for `int`:

TYPED_TEST(SearchAlgortithmsTestWithInt, LinearSearchSingleElement)
{
    TypeParam container = {10};  // Single element in the list

    // Test linear search for the only element
    auto result = linearSearch(container.begin(), container.end(), 10);
    EXPECT_NE(result, container.end());
    EXPECT_EQ(*result, 10);

    // Test linear search for an element that does not exist
    result = linearSearch(container.begin(), container.end(), 20);
    EXPECT_EQ(result, container.end());
}

TYPED_TEST(SearchAlgortithmsTestWithInt, LinearSearchEmptyList)
{
    TypeParam container;

    // Test linear search on an empty list
    auto result = linearSearch(container.begin(), container.end(), 20);
    EXPECT_EQ(result, container.end());  // Should be equal to end since the list is empty
}

TYPED_TEST(SearchAlgortithmsTestWithInt, BinarySearchNegativeNumbers)
{
    TypeParam container = {-50, -40, -30, -20, -10};

    // Test binary search for a negative number
    auto it = binarySearch(container.begin(), container.end(), -30);
    EXPECT_EQ(*it, -30);

    // Test binary search for a number not in the list
    it = binarySearch(container.begin(), container.end(), -25);
    EXPECT_EQ(it, container.end());  // Should return end since -25 is not in the list
}

TYPED_TEST(SearchAlgortithmsTestWithInt, BinarySearchWithDuplicates)
{
    TypeParam container = {10, 20, 20, 20, 30};

    // Test binary search with duplicates
    auto it = binarySearch(container.begin(), container.end(), 20);
    EXPECT_EQ(*it, 20);  // Ensure it returns the first occurrence of 20
}

TYPED_TEST(SearchAlgortithmsTestWithInt, LinearSearchWithDuplicates)
{
    TypeParam container = {10, 20, 20, 20, 30};

    // Test linear search with duplicates
    auto result = linearSearch(container.begin(), container.end(), 20);
    EXPECT_NE(result, container.end());
    EXPECT_EQ(*result, 20);  // It should return the first occurrence of 20
}

//////////////////////////////////////////////////////////////////////////////////

// Templated test fixture for both DynamicArray, StaticArray and List with `std::string`
template <typename ContainerType>
class SearchAlgortithmsTestWithString : public testing::Test
{
public:
    ContainerType mContainer = {"apple", "banana", "cherry"};  // Use aggregate initialization
};

// Define the mContainer types to be tested for strings
using ContainerTypesString =
    ::testing::Types<DynamicArray<std::string>, StaticArray<std::string, 5>, List<std::string>>;

TYPED_TEST_SUITE(SearchAlgortithmsTestWithString, ContainerTypesString);

// Test linear search with strings
TYPED_TEST(SearchAlgortithmsTestWithString, LinearSearch)
{
    auto result = linearSearch(this->mContainer.begin(), this->mContainer.end(), std::string("banana"));
    EXPECT_NE(result, this->mContainer.end());
    EXPECT_EQ(*result, "banana");

    result = linearSearch(this->mContainer.begin(), this->mContainer.end(), std::string("grape"));
    EXPECT_EQ(result, this->mContainer.end());
}

TYPED_TEST(SearchAlgortithmsTestWithString, LinearSearchSingleElement)
{
    TypeParam container = {"apple"};  // Single element in the list

    // Test linear search for the only element
    auto result = linearSearch(container.begin(), container.end(), "apple");
    EXPECT_NE(result, container.end());
    EXPECT_EQ(*result, "apple");

    // Test linear search for an element that does not exist
    result = linearSearch(container.begin(), container.end(), "banana");
    EXPECT_EQ(result, container.end());
}

TYPED_TEST(SearchAlgortithmsTestWithString, LinearSearchEmptyList)
{
    TypeParam container;

    // Test linear search on an empty list
    auto result = linearSearch(container.begin(), container.end(), "banana");
    EXPECT_EQ(result, container.end());  // Should be equal to end since the list is empty
}

TYPED_TEST(SearchAlgortithmsTestWithString, BinarySearchNegativeValues)
{
    TypeParam container = {"apple", "banana", "cherry"};

    // Test binary search for a value that is not in the list
    auto it = binarySearch(container.begin(), container.end(), "grape");
    EXPECT_EQ(it, container.end());  // Should return end since "grape" is not in the list
}

TYPED_TEST(SearchAlgortithmsTestWithString, BinarySearchWithDuplicates)
{
    TypeParam container = {"apple", "banana", "banana", "cherry"};

    // Test binary search with duplicate elements
    auto it = binarySearch(container.begin(), container.end(), "banana");
    EXPECT_EQ(*it, "banana");  // Should return the first occurrence of "banana"
}

TYPED_TEST(SearchAlgortithmsTestWithString, BinarySearchEmptyArray)
{
    TypeParam container;

    // Test binary search on an empty mContainer
    auto it = binarySearch(container.begin(), container.end(), "banana");
    EXPECT_EQ(it, container.end());  // Should return end since the mContainer is empty
}
