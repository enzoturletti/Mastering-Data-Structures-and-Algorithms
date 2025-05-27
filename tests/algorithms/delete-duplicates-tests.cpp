#include <gtest/gtest.h>
#include <delete-duplicates.hpp>
#include <dynamic-array.hpp>
#include <list.hpp>
#include <string>

template <typename ContainerType>
class DeleteDuplicatesTestWithInt : public testing::Test
{
};

// Define the container types to be tested for integers
using ContainerTypesInt = ::testing::Types<DynamicArray<int>, List<int>>;

TYPED_TEST_SUITE(DeleteDuplicatesTestWithInt, ContainerTypesInt);

TYPED_TEST(DeleteDuplicatesTestWithInt, NoDuplicates)
{
    TypeParam container = {1, 2, 3, 4, 5};
    TypeParam expected = {1, 2, 3, 4, 5};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

TYPED_TEST(DeleteDuplicatesTestWithInt, AllDuplicates)
{
    TypeParam container = {1, 1, 1, 1, 1};
    TypeParam expected = {1};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

TYPED_TEST(DeleteDuplicatesTestWithInt, SomeDuplicates)
{
    TypeParam container = {1, 2, 2, 3, 4, 5, 5};
    TypeParam expected = {1, 2, 3, 4, 5};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

TYPED_TEST(DeleteDuplicatesTestWithInt, EmptyContainer)
{
    TypeParam container = {};
    TypeParam expected = {};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

TYPED_TEST(DeleteDuplicatesTestWithInt, SingleElement)
{
    TypeParam container = {42};
    TypeParam expected = {42};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

TYPED_TEST(DeleteDuplicatesTestWithInt, MultipleDuplicatePairs)
{
    TypeParam container = {1, 2, 2, 3, 1, 4, 5, 3, 6};
    TypeParam expected = {1, 2, 3, 4, 5, 6};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

TYPED_TEST(DeleteDuplicatesTestWithInt, ContainerWithDifferentTypes)
{
    TypeParam container = {10, 20, 30, 10, 40, 50, 40};
    TypeParam expected = {10, 20, 30, 40, 50};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

TYPED_TEST(DeleteDuplicatesTestWithInt, LargeContainer)
{
    TypeParam container;
    for (int i = 0; i < 1000; ++i)
    {
        container.append(i % 100);  // Introduce duplicates in a pattern
    }

    TypeParam expected;
    for (int i = 0; i < 100; ++i)
    {
        expected.append(i);  // Expected unique values from 0 to 99
    }

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

//////////////////////////////////////////////////////////////////////////////////

template <typename ContainerType>
class DeleteDuplicatesTestWithString : public testing::Test
{
};

// Define the container types to be tested for strings
using ContainerTypesString = ::testing::Types<DynamicArray<std::string>, List<std::string>>;

TYPED_TEST_SUITE(DeleteDuplicatesTestWithString, ContainerTypesString);

TYPED_TEST(DeleteDuplicatesTestWithString, NoDuplicates)
{
    TypeParam container = {"apple", "banana", "cherry", "date", "elderberry"};
    TypeParam expected = {"apple", "banana", "cherry", "date", "elderberry"};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

TYPED_TEST(DeleteDuplicatesTestWithString, AllDuplicates)
{
    TypeParam container = {"apple", "apple", "apple", "apple"};
    TypeParam expected = {"apple"};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

TYPED_TEST(DeleteDuplicatesTestWithString, SomeDuplicates)
{
    TypeParam container = {"apple", "banana", "banana", "cherry", "apple", "date"};
    TypeParam expected = {"apple", "banana", "cherry", "date"};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

TYPED_TEST(DeleteDuplicatesTestWithString, EmptyContainer)
{
    TypeParam container = {};
    TypeParam expected = {};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

TYPED_TEST(DeleteDuplicatesTestWithString, SingleElement)
{
    TypeParam container = {"apple"};
    TypeParam expected = {"apple"};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

TYPED_TEST(DeleteDuplicatesTestWithString, MultipleDuplicatePairs)
{
    TypeParam container = {"apple", "banana", "banana", "cherry", "apple", "date", "cherry"};
    TypeParam expected = {"apple", "banana", "cherry", "date"};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

TYPED_TEST(DeleteDuplicatesTestWithString, ContainerWithDifferentStrings)
{
    TypeParam container = {"dog", "cat", "bird", "dog", "fish", "cat"};
    TypeParam expected = {"dog", "cat", "bird", "fish"};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}

TYPED_TEST(DeleteDuplicatesTestWithString, LargeContainer)
{
    TypeParam container = {"apple", "banana", "cherry", "apple", "banana", "date", "elderberry"};
    TypeParam expected = {"apple", "banana", "cherry", "date", "elderberry"};

    deleteDuplicates(container);

    EXPECT_EQ(container, expected);
}
