#include <gtest/gtest.h>
#include <difference-elements.hpp>
#include <dynamic-array.hpp>
#include <list.hpp>

// Templated test fixture for both DynamicArray and List with `int`
template <typename ContainerType>
class DifferenceAlgorithmsTestWithInt : public testing::Test
{
};

// Define the container types to be tested for integers
using ContainerTypesInt = ::testing::Types<DynamicArray<int>, List<int>>;

TYPED_TEST_SUITE(DifferenceAlgorithmsTestWithInt, ContainerTypesInt);

TYPED_TEST(DifferenceAlgorithmsTestWithInt, BasicFunctionality)
{
    TypeParam container1 = {1, 3, 5};
    TypeParam container2 = {3, 5, 7};
    TypeParam expected = {1};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithInt, EmptyFirstArray)
{
    TypeParam container1 = {};
    TypeParam container2 = {2, 4, 6};
    TypeParam expected = {};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithInt, EmptySecondArray)
{
    TypeParam container1 = {1, 3, 5};
    TypeParam container2 = {};
    TypeParam expected = {1, 3, 5};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithInt, BothArraysEmpty)
{
    TypeParam container1 = {};
    TypeParam container2 = {};
    TypeParam expected = {};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithInt, OverlappingValues)
{
    TypeParam container1 = {1, 2, 3};
    TypeParam container2 = {2, 3, 4};
    TypeParam expected = {1};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithInt, SingleElementArrays)
{
    TypeParam container1 = {1};
    TypeParam container2 = {1};
    TypeParam expected = {};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithInt, DifferentSizes)
{
    TypeParam container1 = {1, 3};
    TypeParam container2 = {3, 4, 5};
    TypeParam expected = {1};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithInt, ArraysWithDuplicates)
{
    TypeParam container1 = {1, 1, 2};
    TypeParam container2 = {1, 3, 3};
    TypeParam expected = {2};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithInt, LargeArrays)
{
    TypeParam container1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    TypeParam container2 = {5, 6, 7, 8, 9, 10};
    TypeParam expected = {1, 2, 3, 4};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithInt, NegativeNumbers)
{
    TypeParam container1 = {-5, -3, -1};
    TypeParam container2 = {-6, -4, -2};
    TypeParam expected = {-5, -3, -1};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

//////////////////////////////////////////////////////////////////////////////////

template <typename ContainerType>
class DifferenceAlgorithmsTestWithString : public testing::Test
{
};

// Define the container types to be tested for strings
using ContainerTypesString = ::testing::Types<DynamicArray<std::string>, List<std::string>>;

TYPED_TEST_SUITE(DifferenceAlgorithmsTestWithString, ContainerTypesString);

TYPED_TEST(DifferenceAlgorithmsTestWithString, BasicFunctionality)
{
    TypeParam container1 = {"apple", "banana", "cherry"};
    TypeParam container2 = {"banana", "cherry", "date"};
    TypeParam expected = {"apple"};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithString, EmptyFirstArray)
{
    TypeParam container1 = {};
    TypeParam container2 = {"banana", "cherry", "date"};
    TypeParam expected = {};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithString, EmptySecondArray)
{
    TypeParam container1 = {"apple", "banana", "cherry"};
    TypeParam container2 = {};
    TypeParam expected = {"apple", "banana", "cherry"};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithString, BothArraysEmpty)
{
    TypeParam container1 = {};
    TypeParam container2 = {};
    TypeParam expected = {};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithString, OverlappingValues)
{
    TypeParam container1 = {"apple", "banana", "cherry"};
    TypeParam container2 = {"banana", "cherry", "date"};
    TypeParam expected = {"apple"};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithString, ArraysWithDuplicates)
{
    TypeParam container1 = {"apple", "apple", "banana"};
    TypeParam container2 = {"banana", "cherry", "cherry"};
    TypeParam expected = {"apple", "apple"};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithString, SingleElementArrays)
{
    TypeParam container1 = {"apple"};
    TypeParam container2 = {"banana"};
    TypeParam expected = {"apple"};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(DifferenceAlgorithmsTestWithString, LargeArrays)
{
    TypeParam container1 = {"apple", "banana", "cherry", "date", "elderberry"};
    TypeParam container2 = {"banana", "cherry", "date", "elderberry", "fig"};
    TypeParam expected = {"apple"};

    auto result = differenceElements(container1, container2);

    EXPECT_EQ(result, expected);
}
