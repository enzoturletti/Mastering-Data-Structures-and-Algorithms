#include <gtest/gtest.h>
#include <dynamic-array.hpp>
#include <list.hpp>
#include <union-elements.hpp>

// Templated test fixture for both DynamicArray and List with `int`
template <typename ContainerType>
class UnionAlgorithmsTestWithInt : public testing::Test
{
};

// Define the container types to be tested for integers
using ContainerTypesInt = ::testing::Types<DynamicArray<int>, List<int>>;

TYPED_TEST_SUITE(UnionAlgorithmsTestWithInt, ContainerTypesInt);

// Test unionElements with TypeParam
TYPED_TEST(UnionAlgorithmsTestWithInt, BasicFunctionality)
{
    TypeParam array1 = {1, 3, 5};
    TypeParam array2 = {2, 4, 6};
    TypeParam expected = {1, 3, 5, 2, 4, 6};

    auto result = unionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(UnionAlgorithmsTestWithInt, EmptyFirstArray)
{
    TypeParam array1 = {};
    TypeParam array2 = {2, 4, 6};
    TypeParam expected = {2, 4, 6};

    auto result = unionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(UnionAlgorithmsTestWithInt, EmptySecondArray)
{
    TypeParam array1 = {1, 3, 5};
    TypeParam array2 = {};
    TypeParam expected = {1, 3, 5};

    auto result = unionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(UnionAlgorithmsTestWithInt, BothArraysEmpty)
{
    TypeParam array1 = {};
    TypeParam array2 = {};
    TypeParam expected = {};

    auto result = unionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(UnionAlgorithmsTestWithInt, OverlappingValues)
{
    TypeParam array1 = {1, 2, 3};
    TypeParam array2 = {2, 3, 4};
    TypeParam expected = {1, 2, 3, 4};

    auto result = unionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(UnionAlgorithmsTestWithInt, ArraysWithDuplicates)
{
    TypeParam array1 = {1, 1, 2};
    TypeParam array2 = {2, 3, 3};
    TypeParam expected = {1, 2, 3};

    auto result = unionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(UnionAlgorithmsTestWithInt, SingleElementArrays)
{
    TypeParam array1 = {1};
    TypeParam array2 = {2};
    TypeParam expected = {1, 2};

    auto result = unionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(UnionAlgorithmsTestWithInt, DifferentSizes)
{
    TypeParam array1 = {1, 3};
    TypeParam array2 = {2, 4, 5, 6};
    TypeParam expected = {1, 3, 2, 4, 5, 6};

    auto result = unionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(UnionAlgorithmsTestWithInt, LargeArrays)
{
    TypeParam array1 = {1, 2, 3, 4, 5};
    TypeParam array2 = {6, 7, 8, 9, 10};
    TypeParam expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto result = unionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(UnionAlgorithmsTestWithInt, NegativeNumbers)
{
    TypeParam array1 = {-5, -3, -1};
    TypeParam array2 = {-6, -4, -2};
    TypeParam expected = {-5, -3, -1, -6, -4, -2};

    auto result = unionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

//////////////////////////////////////////////////////////////////////////////////

template <typename ContainerType>
class UnionAlgorithmsTestWithString : public testing::Test
{
};

// Define the container types to be tested for strings
using ContainerTypesString = ::testing::Types<DynamicArray<std::string>, List<std::string>>;

TYPED_TEST_SUITE(UnionAlgorithmsTestWithString, ContainerTypesString);

// Test unionElements with string type
TYPED_TEST(UnionAlgorithmsTestWithString, BasicFunctionality)
{
    TypeParam array1 = {"apple", "banana", "cherry"};
    TypeParam array2 = {"date", "elderberry", "fig"};
    TypeParam expected = {"apple", "banana", "cherry", "date", "elderberry", "fig"};

    auto result = unionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(UnionAlgorithmsTestWithString, OverlappingValues)
{
    TypeParam array1 = {"apple", "banana", "cherry"};
    TypeParam array2 = {"banana", "cherry", "date"};
    TypeParam expected = {"apple", "banana", "cherry", "date"};

    auto result = unionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(UnionAlgorithmsTestWithString, ArraysWithDuplicates)
{
    TypeParam array1 = {"apple", "apple", "banana"};
    TypeParam array2 = {"banana", "cherry", "cherry"};
    TypeParam expected = {"apple", "banana", "cherry"};

    auto result = unionElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(UnionAlgorithmsTestWithString, LargeArrays)
{
    TypeParam array1 = {"apple", "banana", "cherry", "date", "elderberry"};
    TypeParam array2 = {"fig", "grape", "honeydew", "kiwi", "lemon"};
    TypeParam expected = {"apple", "banana", "cherry",   "date", "elderberry",
                          "fig",   "grape",  "honeydew", "kiwi", "lemon"};

    auto result = unionElements(array1, array2);

    EXPECT_EQ(result, expected);
}
