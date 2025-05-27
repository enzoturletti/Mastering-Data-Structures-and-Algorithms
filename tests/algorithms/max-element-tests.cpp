#include <gtest/gtest.h>

#include <dynamic-array.hpp>
#include <list.hpp>
#include <max-element.hpp>
#include <static-array.hpp>

// Templated test fixture for both DynamicArray and List with `int`
template <typename ContainerType>
class MaxElementAlgorithmsTestWithInt : public testing::Test
{
};

// Define the container types to be tested for integers
using ContainerTypesInt = ::testing::Types<DynamicArray<int>, List<int>>;

TYPED_TEST_SUITE(MaxElementAlgorithmsTestWithInt, ContainerTypesInt);

TYPED_TEST(MaxElementAlgorithmsTestWithInt, MaxElementFound)
{
    TypeParam array = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    auto result = maxElement(array.begin(), array.end());
    EXPECT_NE(result, array.end());
    EXPECT_EQ(*result, 100);
}

TYPED_TEST(MaxElementAlgorithmsTestWithInt, MaxElementEmptyArray)
{
    TypeParam emptyArray;
    auto result = maxElement(emptyArray.begin(), emptyArray.end());
    EXPECT_EQ(result, emptyArray.end());
}

TYPED_TEST(MaxElementAlgorithmsTestWithInt, MaxElementSingleElement)
{
    TypeParam array = {42};
    auto result = maxElement(array.begin(), array.end());
    EXPECT_NE(result, array.end());
    EXPECT_EQ(*result, 42);
}

TYPED_TEST(MaxElementAlgorithmsTestWithInt, MaxElementDuplicateMax)
{
    TypeParam array = {10, 20, 30, 100, 100, 40};
    auto result = maxElement(array.begin(), array.end());
    EXPECT_NE(result, array.end());
    EXPECT_EQ(*result, 100);
}

TYPED_TEST(MaxElementAlgorithmsTestWithInt, MaxElementNegativeValues)
{
    TypeParam array = {-50, -40, -30, -10, -20};
    auto result = maxElement(array.begin(), array.end());
    EXPECT_NE(result, array.end());
    EXPECT_EQ(*result, -10);
}

// Tests for StaticArray<int>
TEST(MaxElementStaticArrayInt, MaxElementFound)
{
    StaticArray<int, 10> array = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    auto result = maxElement(array.begin(), array.end());
    EXPECT_NE(result, array.end());
    EXPECT_EQ(*result, 100);
}

TEST(MaxElementStaticArrayInt, MaxElementEmptyArray)
{
    StaticArray<int, 0> emptyArray;
    auto result = maxElement(emptyArray.begin(), emptyArray.end());
    EXPECT_EQ(result, emptyArray.end());
}

TEST(MaxElementStaticArrayInt, MaxElementSingleElement)
{
    StaticArray<int, 1> array = {42};
    auto result = maxElement(array.begin(), array.end());
    EXPECT_NE(result, array.end());
    EXPECT_EQ(*result, 42);
}

TEST(MaxElementStaticArrayInt, MaxElementDuplicateMax)
{
    StaticArray<int, 6> array = {10, 20, 30, 100, 100, 40};
    auto result = maxElement(array.begin(), array.end());
    EXPECT_NE(result, array.end());
    EXPECT_EQ(*result, 100);
}

TEST(MaxElementStaticArrayInt, MaxElementNegativeValues)
{
    StaticArray<int, 5> array = {-50, -40, -30, -10, -20};
    auto result = maxElement(array.begin(), array.end());
    EXPECT_NE(result, array.end());
    EXPECT_EQ(*result, -10);
}

//////////////////////////////////////////////////////////////////////////////////

template <typename ContainerType>
class MaxElementAlgorithmsTestWithString : public testing::Test
{
};

// Define the container types to be tested for strings
using ContainerTypesString = ::testing::Types<DynamicArray<std::string>, List<std::string>>;

TYPED_TEST_SUITE(MaxElementAlgorithmsTestWithString, ContainerTypesString);

TYPED_TEST(MaxElementAlgorithmsTestWithString, MaxElementStrings)
{
    TypeParam array = {"apple", "banana", "cherry", "date", "elderberry"};
    auto result = maxElement(array.begin(), array.end());
    EXPECT_NE(result, array.end());
    EXPECT_EQ(*result, "elderberry");
}

TYPED_TEST(MaxElementAlgorithmsTestWithString, MaxElementEmptyArray)
{
    TypeParam emptyArray;
    auto result = maxElement(emptyArray.begin(), emptyArray.end());
    EXPECT_EQ(result, emptyArray.end());
}

TYPED_TEST(MaxElementAlgorithmsTestWithString, MaxElementSingleString)
{
    TypeParam array = {"apple"};
    auto result = maxElement(array.begin(), array.end());
    EXPECT_NE(result, array.end());
    EXPECT_EQ(*result, "apple");
}

// Tests for StaticArray<std::string>
TEST(MaxElementStaticArrayString, MaxElementStrings)
{
    StaticArray<std::string, 5> array = {"apple", "banana", "cherry", "date", "elderberry"};
    auto result = maxElement(array.begin(), array.end());
    EXPECT_NE(result, array.end());
    EXPECT_EQ(*result, "elderberry");
}

TEST(MaxElementStaticArrayString, MaxElementEmptyArray)
{
    StaticArray<std::string, 0> emptyArray;
    auto result = maxElement(emptyArray.begin(), emptyArray.end());
    EXPECT_EQ(result, emptyArray.end());
}

TEST(MaxElementStaticArrayString, MaxElementSingleString)
{
    StaticArray<std::string, 1> array = {"apple"};
    auto result = maxElement(array.begin(), array.end());
    EXPECT_NE(result, array.end());
    EXPECT_EQ(*result, "apple");
}
