#include <gtest/gtest.h>
#include <vector>

#include <bin-sort.hpp>
#include <bubble-sort.hpp>
#include <count-sort.hpp>
#include <dynamic-array.hpp>
#include <insert-sort.hpp>
#include <list.hpp>
#include <quick-sort.hpp>
#include <radix-sort.hpp>
#include <selection-sort.hpp>

/////////////////////////////////////////////////////////////////////////

template <typename ContainerType>
class SortingElementsTests : public testing::Test
{
};

// Define the container types to be tested for integers
using ContainerTypesInt = ::testing::Types<DynamicArray<int>, List<int>>;

TYPED_TEST_SUITE(SortingElementsTests, ContainerTypesInt);

TYPED_TEST(SortingElementsTests, BubbleSortsContainerOfInts)
{
    TypeParam data{5, 3, 8, 1, 2};
    TypeParam expected{1, 2, 3, 5, 8};

    bubbleSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, BubbleSortsWorksOnEmptyContainer)
{
    TypeParam data;
    TypeParam expected;

    bubbleSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, BubbleSortsWorksOnSingleElement)
{
    TypeParam data{42};
    TypeParam expected{42};

    bubbleSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, BubbleSortsAlreadySorted)
{
    TypeParam data{1, 2, 3, 4, 5, 0};
    TypeParam expected{0, 1, 2, 3, 4, 5};

    bubbleSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, BubbleSortsDescendingInput)
{
    TypeParam data{5, 4, 3, 2, 1};
    TypeParam expected{1, 2, 3, 4, 5};

    bubbleSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

/////////////////////////////////////////////////////////////////////////

TYPED_TEST(SortingElementsTests, InsertionSortsContainerOfInts)
{
    TypeParam data{5, 3, 8, 1, 2};
    TypeParam expected{1, 2, 3, 5, 8};

    insertSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, InsertionSortsWorksOnEmptyContainer)
{
    TypeParam data;
    TypeParam expected;

    insertSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, InsertionSortsWorksOnSingleElement)
{
    TypeParam data{42};
    TypeParam expected{42};

    insertSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, InsertionSortsAlreadySorted)
{
    TypeParam data{0, 1, 2, 3, 4, 5};
    TypeParam expected{0, 1, 2, 3, 4, 5};

    insertSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, InsertionSortsDescendingInput)
{
    TypeParam data{5, 4, 3, 2, 1};
    TypeParam expected{1, 2, 3, 4, 5};

    insertSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

/////////////////////////////////////////////////////////////////////////

TYPED_TEST(SortingElementsTests, SelectionSortsContainerOfInts)
{
    TypeParam data{5, 3, 8, 1, 2};
    TypeParam expected{1, 2, 3, 5, 8};

    selectionSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, SelectionSortsWorksOnEmptyContainer)
{
    TypeParam data;
    TypeParam expected;

    selectionSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, SelectionSortsWorksOnSingleElement)
{
    TypeParam data{42};
    TypeParam expected{42};

    selectionSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, SelectionSortsAlreadySorted)
{
    TypeParam data{0, 1, 2, 3, 4, 5};
    TypeParam expected{0, 1, 2, 3, 4, 5};

    selectionSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, SelectionSortsDescendingInput)
{
    TypeParam data{9, 7, 5, 3, 1};
    TypeParam expected{1, 3, 5, 7, 9};

    selectionSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

/////////////////////////////////////////////////////////////////////////

TYPED_TEST(SortingElementsTests, QuickSortsUnorderedContainer)
{
    TypeParam data{5, 3, 8, 1, 2};
    TypeParam expected{1, 2, 3, 5, 8};

    quickSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, QuickSortsEmptyContainer)
{
    TypeParam data;
    TypeParam expected;

    quickSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, QuickSortsSingleElement)
{
    TypeParam data{42};
    TypeParam expected{42};

    quickSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, QuickSortsAlreadySortedContainer)
{
    TypeParam data{1, 2, 3, 4, 5};
    TypeParam expected{1, 2, 3, 4, 5};

    quickSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, QuickSortsReverseSortedContainer)
{
    TypeParam data{5, 4, 3, 2, 1};
    TypeParam expected{1, 2, 3, 4, 5};

    quickSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, QuickSortsWithDuplicates)
{
    TypeParam data{4, 2, 4, 1, 3, 2};
    TypeParam expected{1, 2, 2, 3, 4, 4};

    quickSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

/////////////////////////////////////////////////////////////////////////

TYPED_TEST(SortingElementsTests, CountSortsUnorderedContainer)
{
    TypeParam data{4, 2, 4, 1, 3, 2};
    TypeParam expected{1, 2, 2, 3, 4, 4};

    countSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, CountSortsEmptyContainer)
{
    TypeParam data;
    TypeParam expected;

    countSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, CountSortsSingleElement)
{
    TypeParam data{7};
    TypeParam expected{7};

    countSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, CountSortsSortedInput)
{
    TypeParam data{1, 2, 3, 4, 5};
    TypeParam expected{1, 2, 3, 4, 5};

    countSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, CountSortsDescendingInput)
{
    TypeParam data{5, 4, 3, 2, 1};
    TypeParam expected{1, 2, 3, 4, 5};

    countSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, CountSortThrowsOnNegativeInput)
{
    TypeParam data{3, -1, 2};

    EXPECT_THROW(countSort(data.begin(), data.end()), std::invalid_argument);
}
/////////////////////////////////////////////////////////////////////////

TYPED_TEST(SortingElementsTests, BinSortsUnorderedContainer)
{
    TypeParam data{5, 3, 8, 1, 2};
    TypeParam expected{1, 2, 3, 5, 8};

    binSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, BinSortsEmptyContainer)
{
    TypeParam data;
    TypeParam expected;

    binSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, BinSortsSingleElement)
{
    TypeParam data{42};
    TypeParam expected{42};

    binSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, BinSortsAlreadySortedContainer)
{
    TypeParam data{1, 2, 3, 4, 5};
    TypeParam expected{1, 2, 3, 4, 5};

    binSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, BinSortsReverseSortedContainer)
{
    TypeParam data{5, 4, 3, 2, 1};
    TypeParam expected{1, 2, 3, 4, 5};

    binSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, BinSortsWithDuplicates)
{
    TypeParam data{4, 2, 4, 1, 3, 2};
    TypeParam expected{1, 2, 2, 3, 4, 4};

    binSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, BinSortThrowsOnNegativeValues)
{
    TypeParam data{1, -1, 2, 3};
    EXPECT_THROW(binSort(data.begin(), data.end()), std::invalid_argument);
}

TYPED_TEST(SortingElementsTests, RadixSortsContainerOfInts)
{
    TypeParam data{170, 45, 75, 90, 802, 24, 2, 66};
    TypeParam expected{2, 24, 45, 66, 75, 90, 170, 802};

    radixSort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TYPED_TEST(SortingElementsTests, RadixSortsThrowsOnNegative)
{
    TypeParam data{3, -2, 1};

    EXPECT_THROW(radixSort(data.begin(), data.end()), std::invalid_argument);
}

/////////////////////////////////////////////////////////////////////////
