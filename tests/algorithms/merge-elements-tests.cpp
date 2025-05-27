#include <gtest/gtest.h>
#include <dynamic-array.hpp>
#include <list.hpp>
#include <merge-elements.hpp>
#include <static-array.hpp>

// Templated test fixture for both DynamicArray and List with `int`
template <typename ContainerType>
class MergeAlgorithmsTestWithInt : public testing::Test
{
};

// Define the container types to be tested for integers
using ContainerTypesInt = ::testing::Types<DynamicArray<int>, List<int>>;

TYPED_TEST_SUITE(MergeAlgorithmsTestWithInt, ContainerTypesInt);

// Test mergeElements with TypeParam
TYPED_TEST(MergeAlgorithmsTestWithInt, BasicFunctionality)
{
    TypeParam array1 = {1, 3, 5};
    TypeParam array2 = {2, 4, 6};
    TypeParam expected = {1, 2, 3, 4, 5, 6};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithInt, EmptyFirstArray)
{
    TypeParam array1 = {};
    TypeParam array2 = {2, 4, 6};
    TypeParam expected = {2, 4, 6};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithInt, EmptySecondArray)
{
    TypeParam array1 = {1, 3, 5};
    TypeParam array2 = {};
    TypeParam expected = {1, 3, 5};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithInt, BothArraysEmpty)
{
    TypeParam array1 = {};
    TypeParam array2 = {};
    TypeParam expected = {};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithInt, OverlappingValues)
{
    TypeParam array1 = {1, 2, 3};
    TypeParam array2 = {2, 3, 4};
    TypeParam expected = {1, 2, 2, 3, 3, 4};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithInt, SingleElementArrays)
{
    TypeParam array1 = {1};
    TypeParam array2 = {2};
    TypeParam expected = {1, 2};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithInt, ArraysWithDuplicates)
{
    TypeParam array1 = {1, 1, 2};
    TypeParam array2 = {1, 3, 3};
    TypeParam expected = {1, 1, 1, 2, 3, 3};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithInt, LargeArrays)
{
    TypeParam array1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    TypeParam array2 = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    TypeParam expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithInt, NegativeNumbers)
{
    TypeParam array1 = {-5, -3, -1};
    TypeParam array2 = {-6, -4, -2};
    TypeParam expected = {-6, -5, -4, -3, -2, -1};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithInt, DifferentSizes)
{
    TypeParam array1 = {1, 3};
    TypeParam array2 = {2, 4, 5, 6};
    TypeParam expected = {1, 2, 3, 4, 5, 6};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

// Test mergeElements with StaticArray<int>
TEST(MergeElementsStaticArrayInt, BasicFunctionality)
{
    StaticArray<int, 3> array1 = {1, 3, 5};
    StaticArray<int, 3> array2 = {2, 4, 6};
    StaticArray<int, 6> expected = {1, 2, 3, 4, 5, 6};

    auto result = mergeElements<int, 3, 3>(array1, array2);

    EXPECT_EQ(result, expected);
}

TEST(MergeElementsStaticArrayInt, SingleElementArrays)
{
    StaticArray<int, 1> array1 = {1};
    StaticArray<int, 1> array2 = {2};
    StaticArray<int, 2> expected = {1, 2};

    auto result = mergeElements<int, 1, 1>(array1, array2);

    EXPECT_EQ(result, expected);
}

TEST(MergeElementsStaticArrayInt, DifferentSizes)
{
    StaticArray<int, 2> array1 = {1, 3};
    StaticArray<int, 4> array2 = {2, 4, 5, 6};
    StaticArray<int, 6> expected = {1, 2, 3, 4, 5, 6};

    auto result = mergeElements<int, 2, 4>(array1, array2);

    EXPECT_EQ(result, expected);
}

TEST(MergeElementsStaticArrayInt, ArraysWithDuplicates)
{
    StaticArray<int, 3> array1 = {1, 1, 2};
    StaticArray<int, 3> array2 = {1, 3, 3};
    StaticArray<int, 6> expected = {1, 1, 1, 2, 3, 3};

    auto result = mergeElements<int, 3, 3>(array1, array2);

    EXPECT_EQ(result, expected);
}

TEST(MergeElementsStaticArrayInt, LargeArrays)
{
    StaticArray<int, 10> array1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    StaticArray<int, 10> array2 = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    StaticArray<int, 20> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    auto result = mergeElements<int, 10, 10>(array1, array2);

    EXPECT_EQ(result, expected);
}

TEST(MergeElementsStaticArrayInt, NegativeNumbers)
{
    StaticArray<int, 3> array1 = {-5, -3, -1};
    StaticArray<int, 3> array2 = {-6, -4, -2};
    StaticArray<int, 6> expected = {-6, -5, -4, -3, -2, -1};

    auto result = mergeElements<int, 3, 3>(array1, array2);

    EXPECT_EQ(result, expected);
}

//////////////////////////////////////////////////////////////////////////////////

template <typename ContainerType>
class MergeAlgorithmsTestWithString : public testing::Test
{
};

// Define the container types to be tested for strings
using ContainerTypesString = ::testing::Types<DynamicArray<std::string>, List<std::string>>;

TYPED_TEST_SUITE(MergeAlgorithmsTestWithString, ContainerTypesString);

TYPED_TEST(MergeAlgorithmsTestWithString, BasicFunctionality)
{
    TypeParam array1 = {"apple", "banana", "cherry"};
    TypeParam array2 = {"date", "elderberry", "fig"};
    TypeParam expected = {"apple", "banana", "cherry", "date", "elderberry", "fig"};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithString, EmptyFirstArray)
{
    TypeParam array1 = {};
    TypeParam array2 = {"date", "elderberry", "fig"};
    TypeParam expected = {"date", "elderberry", "fig"};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithString, EmptySecondArray)
{
    TypeParam array1 = {"apple", "banana", "cherry"};
    TypeParam array2 = {};
    TypeParam expected = {"apple", "banana", "cherry"};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithString, BothArraysEmpty)
{
    TypeParam array1 = {};
    TypeParam array2 = {};
    TypeParam expected = {};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithString, OverlappingValues)
{
    TypeParam array1 = {"apple", "banana", "cherry"};
    TypeParam array2 = {"banana", "cherry", "date"};
    TypeParam expected = {"apple", "banana", "banana", "cherry", "cherry", "date"};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithString, ArraysWithDuplicates)
{
    TypeParam array1 = {"apple", "apple", "banana"};
    TypeParam array2 = {"banana", "cherry", "cherry"};
    TypeParam expected = {"apple", "apple", "banana", "banana", "cherry", "cherry"};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithString, SingleElementArrays)
{
    TypeParam array1 = {"apple"};
    TypeParam array2 = {"banana"};
    TypeParam expected = {"apple", "banana"};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

TYPED_TEST(MergeAlgorithmsTestWithString, LargeArrays)
{
    TypeParam array1 = {"apple", "banana", "cherry", "date", "elderberry"};
    TypeParam array2 = {"fig", "grape", "honeydew", "kiwi", "lemon"};
    TypeParam expected = {"apple", "banana", "cherry",   "date", "elderberry",
                          "fig",   "grape",  "honeydew", "kiwi", "lemon"};

    auto result = mergeElements(array1, array2);

    EXPECT_EQ(result, expected);
}

// StaticArray tests with string type
TEST(MergeElementsStaticArrayString, BasicFunctionality)
{
    StaticArray<std::string, 3> array1 = {"apple", "banana", "cherry"};
    StaticArray<std::string, 3> array2 = {"date", "elderberry", "fig"};
    StaticArray<std::string, 6> expected = {"apple", "banana", "cherry", "date", "elderberry", "fig"};

    auto result = mergeElements<std::string, 3, 3>(array1, array2);

    EXPECT_EQ(result, expected);
}

TEST(MergeElementsStaticArrayString, EmptyFirstArray)
{
    StaticArray<std::string, 0> array1 = {};
    StaticArray<std::string, 3> array2 = {"date", "elderberry", "fig"};
    StaticArray<std::string, 3> expected = {"date", "elderberry", "fig"};

    auto result = mergeElements<std::string, 0, 3>(array1, array2);

    EXPECT_EQ(result, expected);
}

TEST(MergeElementsStaticArrayString, EmptySecondArray)
{
    StaticArray<std::string, 3> array1 = {"apple", "banana", "cherry"};
    StaticArray<std::string, 0> array2 = {};
    StaticArray<std::string, 3> expected = {"apple", "banana", "cherry"};

    auto result = mergeElements<std::string, 3, 0>(array1, array2);

    EXPECT_EQ(result, expected);
}

TEST(MergeElementsStaticArrayString, BothArraysEmpty)
{
    StaticArray<std::string, 0> array1 = {};
    StaticArray<std::string, 0> array2 = {};
    StaticArray<std::string, 0> expected = {};

    auto result = mergeElements<std::string, 0, 0>(array1, array2);

    EXPECT_EQ(result, expected);
}

TEST(MergeElementsStaticArrayString, OverlappingValues)
{
    StaticArray<std::string, 3> array1 = {"apple", "banana", "cherry"};
    StaticArray<std::string, 3> array2 = {"banana", "cherry", "date"};
    StaticArray<std::string, 6> expected = {"apple", "banana", "banana", "cherry", "cherry", "date"};

    auto result = mergeElements<std::string, 3, 3>(array1, array2);

    EXPECT_EQ(result, expected);
}

TEST(MergeElementsStaticArrayString, ArraysWithDuplicates)
{
    StaticArray<std::string, 3> array1 = {"apple", "apple", "banana"};
    StaticArray<std::string, 3> array2 = {"banana", "cherry", "cherry"};
    StaticArray<std::string, 6> expected = {"apple", "apple", "banana", "banana", "cherry", "cherry"};

    auto result = mergeElements<std::string, 3, 3>(array1, array2);

    EXPECT_EQ(result, expected);
}

TEST(MergeElementsStaticArrayString, SingleElementArrays)
{
    StaticArray<std::string, 1> array1 = {"apple"};
    StaticArray<std::string, 1> array2 = {"banana"};
    StaticArray<std::string, 2> expected = {"apple", "banana"};

    auto result = mergeElements<std::string, 1, 1>(array1, array2);

    EXPECT_EQ(result, expected);
}

TEST(MergeElementsStaticArrayString, LargeArrays)
{
    StaticArray<std::string, 5> array1 = {"apple", "banana", "cherry", "date", "elderberry"};
    StaticArray<std::string, 5> array2 = {"fig", "grape", "honeydew", "kiwi", "lemon"};
    StaticArray<std::string, 10> expected = {"apple", "banana", "cherry",   "date", "elderberry",
                                             "fig",   "grape",  "honeydew", "kiwi", "lemon"};

    auto result = mergeElements<std::string, 5, 5>(array1, array2);

    EXPECT_EQ(result, expected);
}
