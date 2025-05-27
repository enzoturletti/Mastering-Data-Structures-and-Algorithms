#include <gtest/gtest.h>
#include <dynamic-array.hpp>
#include <list.hpp>
#include <shift-elements.hpp>
#include <static-array.hpp>

// Templated test fixture for both DynamicArray and List with `int`
template <typename ContainerType>
class ShiftAlgorithmsTestWithInt : public testing::Test
{
};

// Define the container types to be tested for integers
using ContainerTypesInt = ::testing::Types<DynamicArray<int>, List<int>>;

TYPED_TEST_SUITE(ShiftAlgorithmsTestWithInt, ContainerTypesInt);

TYPED_TEST(ShiftAlgorithmsTestWithInt, LeftShiftByOne)
{
    TypeParam array = {1, 2, 3, 4, 5};
    leftShiftElements(array.begin(), array.end(), 1);

    // After shifting by 1, the array should look like this: {2, 3, 4, 5, 0}
    EXPECT_EQ(array[0], 2);
    EXPECT_EQ(array[1], 3);
    EXPECT_EQ(array[2], 4);
    EXPECT_EQ(array[3], 5);
    EXPECT_EQ(array[4], 0);
}

TYPED_TEST(ShiftAlgorithmsTestWithInt, LeftShiftByTwo)
{
    TypeParam array = {1, 2, 3, 4, 5};
    leftShiftElements(array.begin(), array.end(), 2);

    // After shifting by 1, the array should look like this: {2, 3, 4, 5, 0}
    EXPECT_EQ(array[0], 3);
    EXPECT_EQ(array[1], 4);
    EXPECT_EQ(array[2], 5);
    EXPECT_EQ(array[3], 0);
    EXPECT_EQ(array[4], 0);
}

TYPED_TEST(ShiftAlgorithmsTestWithInt, LeftShiftByMoreThanLength)
{
    TypeParam array = {1, 2, 3, 4, 5};
    leftShiftElements(array.begin(), array.end(), 10);

    // After shifting by 10 (which is greater than the array size), it should shift only by the array's length
    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 0);
    EXPECT_EQ(array[2], 0);
    EXPECT_EQ(array[3], 0);
    EXPECT_EQ(array[4], 0);
}

TYPED_TEST(ShiftAlgorithmsTestWithInt, LeftShiftByZero)
{
    TypeParam array = {1, 2, 3, 4, 5};
    leftShiftElements(array.begin(), array.end(), 0);

    // The array should remain unchanged since no shift is applied
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);
    EXPECT_EQ(array[2], 3);
    EXPECT_EQ(array[3], 4);
    EXPECT_EQ(array[4], 5);
}

TYPED_TEST(ShiftAlgorithmsTestWithInt, LeftShiftEmptyArray)
{
    TypeParam emptyArray;

    leftShiftElements(emptyArray.begin(), emptyArray.end(), 1);

    // An empty array should remain unchanged
    EXPECT_EQ(emptyArray.begin(), emptyArray.end());
}

TYPED_TEST(ShiftAlgorithmsTestWithInt, LeftShiftSingleElement)
{
    TypeParam singleElementArray = {42};

    leftShiftElements(singleElementArray.begin(), singleElementArray.end(), 1);

    // The array should be {0}, as shifting by 1 removes the only element
    EXPECT_EQ(singleElementArray[0], 0);
}

TYPED_TEST(ShiftAlgorithmsTestWithInt, LeftShiftSizeTwo)
{
    TypeParam twoElementArray = {1, 2};

    leftShiftElements(twoElementArray.begin(), twoElementArray.end(), 1);

    // After shifting by 1, the array should become {2, 0}
    EXPECT_EQ(twoElementArray[0], 2);
    EXPECT_EQ(twoElementArray[1], 0);
}

// Test left shift with StaticArray

TEST(LeftShiftElementsTestStaticArray, LeftShiftByOne)
{
    StaticArray<int, 5> array = {1, 2, 3, 4, 5};
    leftShiftElements(array.begin(), array.end(), 1);

    // After shifting by 1, the array should look like this: {2, 3, 4, 5, 0}
    EXPECT_EQ(array[0], 2);
    EXPECT_EQ(array[1], 3);
    EXPECT_EQ(array[2], 4);
    EXPECT_EQ(array[3], 5);
    EXPECT_EQ(array[4], 0);
}

TEST(LeftShiftElementsTestStaticArray, LeftShiftByTwo)
{
    StaticArray<int, 5> array = {1, 2, 3, 4, 5};
    leftShiftElements(array.begin(), array.end(), 2);

    // After shifting by 1, the array should look like this: {2, 3, 4, 5, 0}
    EXPECT_EQ(array[0], 3);
    EXPECT_EQ(array[1], 4);
    EXPECT_EQ(array[2], 5);
    EXPECT_EQ(array[3], 0);
    EXPECT_EQ(array[4], 0);
}

TEST(LeftShiftElementsTestStaticArray, LeftShiftByMoreThanLength)
{
    StaticArray<int, 5> array = {1, 2, 3, 4, 5};
    leftShiftElements(array.begin(), array.end(), 10);

    // After shifting by 10 (which is greater than the array size), it should shift only by the array's length
    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 0);
    EXPECT_EQ(array[2], 0);
    EXPECT_EQ(array[3], 0);
    EXPECT_EQ(array[4], 0);
}

TEST(LeftShiftElementsTestStaticArray, LeftShiftByZero)
{
    StaticArray<int, 5> array = {1, 2, 3, 4, 5};
    leftShiftElements(array.begin(), array.end(), 0);

    // The array should remain unchanged since no shift is applied
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);
    EXPECT_EQ(array[2], 3);
    EXPECT_EQ(array[3], 4);
    EXPECT_EQ(array[4], 5);
}

TEST(LeftShiftElementsTestStaticArray, LeftShiftEmptyArray)
{
    StaticArray<int, 0> emptyArray;

    leftShiftElements(emptyArray.begin(), emptyArray.end(), 1);

    // An empty array should remain unchanged
    EXPECT_EQ(emptyArray.begin(), emptyArray.end());
}

TEST(LeftShiftElementsTestStaticArray, LeftShiftSingleElement)
{
    StaticArray<int, 1> singleElementArray = {42};

    leftShiftElements(singleElementArray.begin(), singleElementArray.end(), 1);

    // The array should be {0}, as shifting by 1 removes the only element
    EXPECT_EQ(singleElementArray[0], 0);
}

TEST(LeftShiftElementsTestStaticArray, LeftShiftSizeTwo)
{
    StaticArray<int, 2> twoElementArray = {1, 2};

    leftShiftElements(twoElementArray.begin(), twoElementArray.end(), 1);

    // After shifting by 1, the array should become {2, 0}
    EXPECT_EQ(twoElementArray[0], 2);
    EXPECT_EQ(twoElementArray[1], 0);
}

// Test right shift with DynamicArray

TYPED_TEST(ShiftAlgorithmsTestWithInt, RightShiftByOne)
{
    TypeParam array = {1, 2, 3, 4, 5};
    rightShiftElements(array.begin(), array.end(), 1);

    // After shifting by 1, the array should look like this: {0, 1, 2, 3, 4}
    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 1);
    EXPECT_EQ(array[2], 2);
    EXPECT_EQ(array[3], 3);
    EXPECT_EQ(array[4], 4);
}

TYPED_TEST(ShiftAlgorithmsTestWithInt, RightShiftByTwo)
{
    TypeParam array = {1, 2, 3, 4, 5};
    rightShiftElements(array.begin(), array.end(), 2);

    // After shifting by 2, the array should look like this: {0, 0, 1, 2, 3}
    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 0);
    EXPECT_EQ(array[2], 1);
    EXPECT_EQ(array[3], 2);
    EXPECT_EQ(array[4], 3);
}

TYPED_TEST(ShiftAlgorithmsTestWithInt, RightShiftByMoreThanLength)
{
    TypeParam array = {1, 2, 3, 4, 5};
    rightShiftElements(array.begin(), array.end(), 10);

    // After shifting by 10 (which is greater than the array size), it should shift only by the array's length
    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 0);
    EXPECT_EQ(array[2], 0);
    EXPECT_EQ(array[3], 0);
    EXPECT_EQ(array[4], 0);
}

TYPED_TEST(ShiftAlgorithmsTestWithInt, RightShiftByZero)
{
    TypeParam array = {1, 2, 3, 4, 5};
    rightShiftElements(array.begin(), array.end(), 0);

    // The array should remain unchanged since no shift is applied
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);
    EXPECT_EQ(array[2], 3);
    EXPECT_EQ(array[3], 4);
    EXPECT_EQ(array[4], 5);
}

TYPED_TEST(ShiftAlgorithmsTestWithInt, RightShiftEmptyArray)
{
    TypeParam emptyArray;

    rightShiftElements(emptyArray.begin(), emptyArray.end(), 1);

    // An empty array should remain unchanged
    EXPECT_EQ(emptyArray.begin(), emptyArray.end());
}

TYPED_TEST(ShiftAlgorithmsTestWithInt, RightShiftSingleElement)
{
    TypeParam singleElementArray = {42};

    rightShiftElements(singleElementArray.begin(), singleElementArray.end(), 1);

    // The array should be {0}, as shifting by 1 removes the only element
    EXPECT_EQ(singleElementArray[0], 0);
}

TYPED_TEST(ShiftAlgorithmsTestWithInt, RightShiftSizeTwo)
{
    TypeParam twoElementArray = {1, 2};

    rightShiftElements(twoElementArray.begin(), twoElementArray.end(), 1);

    // After shifting by 1, the array should become {0, 1}
    EXPECT_EQ(twoElementArray[0], 0);
    EXPECT_EQ(twoElementArray[1], 1);
}

// Test right shift with StaticArray

TEST(RightShiftElementsTestStaticArray, RightShiftByOne)
{
    StaticArray<int, 5> array = {1, 2, 3, 4, 5};
    rightShiftElements(array.begin(), array.end(), 1);

    // After shifting by 1, the array should look like this: {0, 1, 2, 3, 4}
    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 1);
    EXPECT_EQ(array[2], 2);
    EXPECT_EQ(array[3], 3);
    EXPECT_EQ(array[4], 4);
}

TEST(RightShiftElementsTestStaticArray, RightShiftByTwo)
{
    StaticArray<int, 5> array = {1, 2, 3, 4, 5};
    rightShiftElements(array.begin(), array.end(), 2);

    // After shifting by 2, the array should look like this: {0, 0, 1, 2, 3}
    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 0);
    EXPECT_EQ(array[2], 1);
    EXPECT_EQ(array[3], 2);
    EXPECT_EQ(array[4], 3);
}

TEST(RightShiftElementsTestStaticArray, RightShiftByMoreThanLength)
{
    StaticArray<int, 5> array = {1, 2, 3, 4, 5};
    rightShiftElements(array.begin(), array.end(), 10);

    // After shifting by 10 (which is greater than the array size), it should shift only by the array's length
    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 0);
    EXPECT_EQ(array[2], 0);
    EXPECT_EQ(array[3], 0);
    EXPECT_EQ(array[4], 0);
}

TEST(RightShiftElementsTestStaticArray, RightShiftByZero)
{
    StaticArray<int, 5> array = {1, 2, 3, 4, 5};
    rightShiftElements(array.begin(), array.end(), 0);

    // The array should remain unchanged since no shift is applied
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);
    EXPECT_EQ(array[2], 3);
    EXPECT_EQ(array[3], 4);
    EXPECT_EQ(array[4], 5);
}

TEST(RightShiftElementsTestStaticArray, RightShiftEmptyArray)
{
    StaticArray<int, 0> emptyArray;

    rightShiftElements(emptyArray.begin(), emptyArray.end(), 1);

    // An empty array should remain unchanged
    EXPECT_EQ(emptyArray.begin(), emptyArray.end());
}

TEST(RightShiftElementsTestStaticArray, RightShiftSingleElement)
{
    StaticArray<int, 1> singleElementArray = {42};

    rightShiftElements(singleElementArray.begin(), singleElementArray.end(), 1);

    // The array should be {0}, as shifting by 1 removes the only element
    EXPECT_EQ(singleElementArray[0], 0);
}

TEST(RightShiftElementsTestStaticArray, RightShiftSizeTwo)
{
    StaticArray<int, 2> twoElementArray = {1, 2};

    rightShiftElements(twoElementArray.begin(), twoElementArray.end(), 1);

    // After shifting by 1, the array should become {0, 1}
    EXPECT_EQ(twoElementArray[0], 0);
    EXPECT_EQ(twoElementArray[1], 1);
}
