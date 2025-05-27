#include <gtest/gtest.h>
#include <dynamic-array.hpp>
#include <list.hpp>
#include <reverse-elements.hpp>
#include <static-array.hpp>

// Templated test fixture for both DynamicArray and List with `int`
template <typename ContainerType>
class ReverseAlgorithmsTestWithInt : public testing::Test
{
};

// Define the container types to be tested for integers
using ContainerTypesInt = ::testing::Types<DynamicArray<int>, List<int>>;

TYPED_TEST_SUITE(ReverseAlgorithmsTestWithInt, ContainerTypesInt);

// Test reverseElements with TypeParam
TYPED_TEST(ReverseAlgorithmsTestWithInt, ReverseArray)
{
    TypeParam array = {1, 2, 3, 4, 5};
    reverseElements(array.begin(), array.end());

    // Check if the array is reversed
    EXPECT_EQ(array[0], 5);
    EXPECT_EQ(array[1], 4);
    EXPECT_EQ(array[2], 3);
    EXPECT_EQ(array[3], 2);
    EXPECT_EQ(array[4], 1);
}

TYPED_TEST(ReverseAlgorithmsTestWithInt, ReverseEmptyArray)
{
    TypeParam array = {};
    reverseElements(array.begin(), array.end());

    // An empty array should remain empty
    EXPECT_EQ(array.getSize(), 0);
}

TYPED_TEST(ReverseAlgorithmsTestWithInt, ReverseSingleElement)
{
    TypeParam array = {42};
    reverseElements(array.begin(), array.end());

    // A single element array should remain unchanged
    EXPECT_EQ(array[0], 42);
}

// Test reverseElements with StaticArray<int>
TEST(ReverseStaticArrayInt, ReverseArray)
{
    StaticArray<int, 5> array = {1, 2, 3, 4, 5};
    reverseElements(array.begin(), array.end());

    // Check if the array is reversed
    EXPECT_EQ(array[0], 5);
    EXPECT_EQ(array[1], 4);
    EXPECT_EQ(array[2], 3);
    EXPECT_EQ(array[3], 2);
    EXPECT_EQ(array[4], 1);
}

TEST(ReverseStaticArrayInt, ReverseEmptyArray)
{
    StaticArray<int, 0> array = {};
    reverseElements(array.begin(), array.end());

    // An empty array should remain empty
    EXPECT_EQ(array.getSize(), 0);
}

TEST(ReverseStaticArrayInt, ReverseSingleElement)
{
    StaticArray<int, 1> array = {42};
    reverseElements(array.begin(), array.end());

    // A single element array should remain unchanged
    EXPECT_EQ(array[0], 42);
}

//////////////////////////////////////////////////////////////////////////////////

template <typename ContainerType>
class ReverseAlgorithmsTestWithString : public testing::Test
{
};

// Define the container types to be tested for strings
using ContainerTypesString = ::testing::Types<DynamicArray<std::string>, List<std::string>>;

TYPED_TEST_SUITE(ReverseAlgorithmsTestWithString, ContainerTypesString);

// Test reverseElements with TypeParam
TYPED_TEST(ReverseAlgorithmsTestWithString, ReverseArray)
{
    TypeParam array = {"apple", "banana", "cherry", "date", "elderberry"};
    reverseElements(array.begin(), array.end());

    // Check if the array is reversed
    EXPECT_EQ(array[0], "elderberry");
    EXPECT_EQ(array[1], "date");
    EXPECT_EQ(array[2], "cherry");
    EXPECT_EQ(array[3], "banana");
    EXPECT_EQ(array[4], "apple");
}

TYPED_TEST(ReverseAlgorithmsTestWithString, ReverseEmptyArray)
{
    TypeParam array = {};
    reverseElements(array.begin(), array.end());

    // An empty array should remain empty
    EXPECT_EQ(array.getSize(), 0);
}

TYPED_TEST(ReverseAlgorithmsTestWithString, ReverseSingleElement)
{
    TypeParam array = {"apple"};
    reverseElements(array.begin(), array.end());

    // A single element array should remain unchanged
    EXPECT_EQ(array[0], "apple");
}

// Test reverseElements with StaticArray<std::string>
TEST(ReverseStaticArrayString, ReverseArray)
{
    StaticArray<std::string, 5> array = {"apple", "banana", "cherry", "date", "elderberry"};
    reverseElements(array.begin(), array.end());

    // Check if the array is reversed
    EXPECT_EQ(array[0], "elderberry");
    EXPECT_EQ(array[1], "date");
    EXPECT_EQ(array[2], "cherry");
    EXPECT_EQ(array[3], "banana");
    EXPECT_EQ(array[4], "apple");
}

TEST(ReverseStaticArrayString, ReverseEmptyArray)
{
    StaticArray<std::string, 0> array = {};
    reverseElements(array.begin(), array.end());

    // An empty array should remain empty
    EXPECT_EQ(array.getSize(), 0);
}

TEST(ReverseStaticArrayString, ReverseSingleElement)
{
    StaticArray<std::string, 1> array = {"apple"};
    reverseElements(array.begin(), array.end());

    // A single element array should remain unchanged
    EXPECT_EQ(array[0], "apple");
}
