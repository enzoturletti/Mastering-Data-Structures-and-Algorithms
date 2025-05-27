#include <gtest/gtest.h>
#include <dynamic-array.hpp>
#include <intersection-elements.hpp>
#include <list.hpp>

template <typename ContainerType>
class IntersectionAlgorithmsTestWithInt : public testing::Test
{
};

// Define the container types to be tested for integers
using ContainerTypesInt = ::testing::Types<DynamicArray<int>, List<int>>;

TYPED_TEST_SUITE(IntersectionAlgorithmsTestWithInt, ContainerTypesInt);

// Test intersectionElements with TypeParam
TYPED_TEST(IntersectionAlgorithmsTestWithInt, BasicFunctionality)
{
    TypeParam array1 = {1, 3, 5};
    TypeParam array2 = {3, 5, 7};
    TypeParam expected = {3, 5};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithInt, EmptyFirstArray)
{
    TypeParam array1 = {};
    TypeParam array2 = {2, 4, 6};
    TypeParam expected = {};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithInt, EmptySecondArray)
{
    TypeParam array1 = {1, 3, 5};
    TypeParam array2 = {};
    TypeParam expected = {};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithInt, BothArraysEmpty)
{
    TypeParam array1 = {};
    TypeParam array2 = {};
    TypeParam expected = {};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithInt, OverlappingValues)
{
    TypeParam array1 = {1, 2, 3};
    TypeParam array2 = {2, 3, 4};
    TypeParam expected = {2, 3};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithInt, SingleElementArrays)
{
    TypeParam array1 = {1};
    TypeParam array2 = {1};
    TypeParam expected = {1};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithInt, DifferentSizes)
{
    TypeParam array1 = {1, 3};
    TypeParam array2 = {3, 4, 5};
    TypeParam expected = {3};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithInt, ArraysWithDuplicates)
{
    TypeParam array1 = {1, 1, 2};
    TypeParam array2 = {1, 3, 3};
    TypeParam expected = {1, 1};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithInt, LargeArrays)
{
    TypeParam array1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    TypeParam array2 = {5, 6, 7, 8, 9, 10};
    TypeParam expected = {5, 6, 7, 8, 9, 10};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithInt, NegativeNumbers)
{
    TypeParam array1 = {-5, -3, -1};
    TypeParam array2 = {-6, -4, -2};
    TypeParam expected = {};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

//////////////////////////////////////////////////////////////////////////////////

template <typename ContainerType>
class IntersectionAlgorithmsTestWithString : public testing::Test
{
};

// Define the container types to be tested for integers
using ContainerTypesString = ::testing::Types<DynamicArray<std::string>, List<std::string>>;

TYPED_TEST_SUITE(IntersectionAlgorithmsTestWithString, ContainerTypesString);

TYPED_TEST(IntersectionAlgorithmsTestWithString, BasicFunctionality)
{
    TypeParam array1 = {"apple", "banana", "cherry"};
    TypeParam array2 = {"banana", "cherry", "date"};
    TypeParam expected = {"banana", "cherry"};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithString, EmptyFirstArray)
{
    TypeParam array1 = {};
    TypeParam array2 = {"banana", "cherry", "date"};
    TypeParam expected = {};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithString, EmptySecondArray)
{
    TypeParam array1 = {"apple", "banana", "cherry"};
    TypeParam array2 = {};
    TypeParam expected = {};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithString, BothArraysEmpty)
{
    TypeParam array1 = {};
    TypeParam array2 = {};
    TypeParam expected = {};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithString, OverlappingValues)
{
    TypeParam array1 = {"apple", "banana", "cherry"};
    TypeParam array2 = {"banana", "cherry", "date"};
    TypeParam expected = {"banana", "cherry"};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithString, ArraysWithDuplicates)
{
    TypeParam array1 = {"apple", "apple", "banana"};
    TypeParam array2 = {"banana", "cherry", "cherry"};
    TypeParam expected = {"banana"};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithString, SingleElementArrays)
{
    TypeParam array1 = {"apple"};
    TypeParam array2 = {"banana"};
    TypeParam expected = {};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(IntersectionAlgorithmsTestWithString, LargeArrays)
{
    TypeParam array1 = {"apple", "banana", "cherry", "date", "elderberry"};
    TypeParam array2 = {"banana", "cherry", "date", "elderberry", "fig"};
    TypeParam expected = {"banana", "cherry", "date", "elderberry"};

    auto result = intersectionElements(array1, array2);

    EXPECT_EQ(result, expected);
}
