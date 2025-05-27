#include <gtest/gtest.h>
#include <dynamic-array.hpp>
#include <list.hpp>
#include <rotate-elements.hpp>
#include <static-array.hpp>

// Templated test fixture for both DynamicArray and List with `int`
template <typename ContainerType>
class RotateAlgorithmsTestWithInt : public testing::Test
{
};

// Define the container types to be tested for integers
using ContainerTypesInt = ::testing::Types<DynamicArray<int>, List<int>>;

TYPED_TEST_SUITE(RotateAlgorithmsTestWithInt, ContainerTypesInt);

// Helper function to run tests for different container types
template <typename Container>
void testLeftRotate(Container& container, size_t rotateBy, const std::vector<typename Container::value_type>& expected)
{
    leftRotateElements(container.begin(), container.end(), rotateBy);

    size_t index = 0;
    for (const auto& val : container)
    {
        EXPECT_EQ(val, expected[index++]);
    }
}

// Test leftRotateElements with DynamicArray<int>
TYPED_TEST(RotateAlgorithmsTestWithInt, RotateArray)
{
    TypeParam container = {1, 2, 3, 4, 5};
    testLeftRotate(container, 2, {3, 4, 5, 1, 2});
}

TYPED_TEST(RotateAlgorithmsTestWithInt, RotateEmptyArray)
{
    TypeParam container = {};
    leftRotateElements(container.begin(), container.end(), 2);
    EXPECT_EQ(container.getSize(), 0);
}

TYPED_TEST(RotateAlgorithmsTestWithInt, RotateSingleElement)
{
    TypeParam container = {42};
    leftRotateElements(container.begin(), container.end(), 1);
    EXPECT_EQ(container[0], 42);
}

TYPED_TEST(RotateAlgorithmsTestWithInt, RotateMoreThanSize)
{
    TypeParam container = {1, 2, 3, 4, 5};
    leftRotateElements(container.begin(), container.end(), 12);
    EXPECT_EQ(container[0], 3);
    EXPECT_EQ(container[1], 4);
    EXPECT_EQ(container[2], 5);
    EXPECT_EQ(container[3], 1);
    EXPECT_EQ(container[4], 2);
}

//////////////////////////////////////////////////////////////////////////////////

template <typename ContainerType>
class RotateAlgorithmsTestWithString : public testing::Test
{
};

// Define the container types to be tested for strings
using ContainerTypesString = ::testing::Types<DynamicArray<std::string>, List<std::string>>;

TYPED_TEST_SUITE(RotateAlgorithmsTestWithString, ContainerTypesString);

TYPED_TEST(RotateAlgorithmsTestWithString, RotateArray)
{
    TypeParam container = {"apple", "banana", "cherry", "date", "elderberry"};
    testLeftRotate(container, 2, {"cherry", "date", "elderberry", "apple", "banana"});
}

TYPED_TEST(RotateAlgorithmsTestWithString, RotateEmptyArray)
{
    TypeParam container = {};
    leftRotateElements(container.begin(), container.end(), 2);
    EXPECT_EQ(container.getSize(), 0);
}

TYPED_TEST(RotateAlgorithmsTestWithString, RotateSingleElement)
{
    TypeParam container = {"apple"};
    leftRotateElements(container.begin(), container.end(), 1);
    EXPECT_EQ(container[0], "apple");
}

TYPED_TEST(RotateAlgorithmsTestWithString, RotateMoreThanSize)
{
    TypeParam container = {"apple", "banana", "cherry", "date", "elderberry"};
    leftRotateElements(container.begin(), container.end(), 7);
    EXPECT_EQ(container[0], "cherry");
    EXPECT_EQ(container[1], "date");
    EXPECT_EQ(container[2], "elderberry");
    EXPECT_EQ(container[3], "apple");
    EXPECT_EQ(container[4], "banana");
}