#include <gtest/gtest.h>
#include <static-array.hpp>

// Test for getSize
TEST(StaticArrayTest, GetSize)
{
    StaticArray<int, 5> arr;
    EXPECT_EQ(arr.getSize(), 5);  // Ensure size is 5
}

// Test for an array with zero size.
TEST(StaticArrayTest, IsEmpty)
{
    StaticArray<int, 5> arr;
    EXPECT_TRUE(arr.isEmpty() == 0);  // Newly created array should be empty
}

// Test for accessing elements using operator[]
TEST(StaticArrayTest, ElementAccess)
{
    StaticArray<int, 5> arr;

    // Init array with less than 5 elements
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    // Access elements using operator[]
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);

    // Modify elements using operator[]
    arr[0] = 100;
    arr[1] = 200;
    arr[2] = 300;

    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_EQ(arr[2], 300);
}

// Test for out-of-bounds access with operator[]
TEST(StaticArrayTest, OutOfBoundsAccess)
{
    StaticArray<int, 5> arr;

    // Append elements
    arr[0] = 10;
    arr[1] = 20;

    // Accessing out-of-bounds indices should throw an exception
    EXPECT_THROW(arr[-1], std::out_of_range);
    EXPECT_THROW(arr[5], std::out_of_range);
    EXPECT_THROW(arr[10], std::out_of_range);
}

// Test for initialization with initializer list
TEST(StaticArrayTest, InitializationWithInitializerList)
{
    StaticArray<int, 5> arr = {1, 2, 3, 4, 5};

    // Check if the elements are initialized correctly
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
    EXPECT_EQ(arr[4], 5);
}

// Test for begin and end iteration
TEST(StaticArrayTest, BeginEndIteration)
{
    StaticArray<int, 5> arr = {10, 20, 30, 40, 50};

    // Test iteration using begin() and end()
    int expected[] = {10, 20, 30, 40, 50};
    int index = 0;

    for (auto it = arr.begin(); it != arr.end(); ++it)
    {
        EXPECT_EQ(*it, expected[index]);
        index++;
    }
}

// Test for isEmpty with a non-empty array
TEST(StaticArrayTest, IsNotEmpty)
{
    StaticArray<int, 5> arr;
    arr[0] = 1;  // Array is no longer empty
    EXPECT_FALSE(arr.isEmpty());
}

// Test for an empty StaticArray
TEST(StaticArrayTest, IsEmptyEmptyArray)
{
    StaticArray<int, 0> arr;
    EXPECT_TRUE(arr.isEmpty());
    EXPECT_TRUE(arr.begin() == arr.end());
}

// Test for modifying elements
TEST(StaticArrayTest, ModifyElements)
{
    StaticArray<int, 5> arr = {1, 2, 3, 4, 5};

    // Modify array elements
    arr[0] = 10;
    arr[4] = 50;

    // Verify changes
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[4], 50);
}

// Test for default initialization (values should be default-initialized to 0 for integers)
TEST(StaticArrayTest, DefaultInitialization)
{
    StaticArray<int, 5> arr;

    // Ensure default-initialized elements are zero
    for (int i = 0; i < arr.getSize(); ++i)
    {
        EXPECT_EQ(arr[i], 0);
    }
}
