#include <gtest/gtest.h>
#include <binary-search.hpp>
#include <dynamic-array.hpp>
#include <linear-search.hpp>

// Test default constructor and initial size and capacity
TEST(DynamicArrayTest, DefaultConstructor)
{
    DynamicArray<int> arr;
    EXPECT_EQ(arr.getSize(), 0);                                            // Size should be 0 initially
    EXPECT_EQ(arr.getCapacity(), DynamicArray<int>::getDefaultCapacity());  // Default capacity should be 5
    EXPECT_TRUE(arr.isEmpty());                                             // Array should be empty
}

// Test constructor with custom initial capacity
TEST(DynamicArrayTest, CustomCapacityConstructor)
{
    DynamicArray<int> arr(10);
    EXPECT_EQ(arr.getSize(), 0);       // Size should be 0 initially
    EXPECT_EQ(arr.getCapacity(), 10);  // Capacity should match the custom value
}

// Test the destructor and memory management
TEST(DynamicArrayTest, Destructor)
{
    {
        DynamicArray<int> arr(10);
        arr.append(1);
        arr.append(2);
        // When arr goes out of scope, destructor should be called
        // If there is no memory leak, the test passes.
    }  // arr is destructed here
    // Nothing to check directly, we are just testing if the destructor works without causing memory leaks.
}

// Test copy constructor
TEST(DynamicArrayTest, CopyConstructor)
{
    DynamicArray<int> arr1 = {10, 20};

    // Using copy constructor to create a new array
    DynamicArray<int> arr2 = arr1;

    EXPECT_EQ(arr2.getSize(), arr1.getSize());          // Size should be the same
    EXPECT_EQ(arr2.getCapacity(), arr1.getCapacity());  // Capacity should be the same
    EXPECT_EQ(arr2[0], 10);                             // First element should be 10
    EXPECT_EQ(arr2[1], 20);                             // Second element should be 20
}

// Test copy assignment operator
TEST(DynamicArrayTest, CopyAssignmentOperator)
{
    DynamicArray<int> arr1 = {10, 20};

    // Using copy assignment operator to assign arr1 to arr2
    DynamicArray<int> arr2(1);  // Initially smaller array
    arr2 = arr1;

    EXPECT_EQ(arr2.getSize(), arr1.getSize());          // Size should be the same
    EXPECT_EQ(arr2.getCapacity(), arr1.getCapacity());  // Capacity should be the same
    EXPECT_EQ(arr2[0], 10);                             // First element should be 10
    EXPECT_EQ(arr2[1], 20);                             // Second element should be 20
}

// Test move constructor
TEST(DynamicArrayTest, MoveConstructor)
{
    DynamicArray<int> arr1 = {10, 20};

    // Move constructor transfers ownership of the resources
    DynamicArray<int> arr2 = std::move(arr1);

    EXPECT_EQ(arr2.getSize(), 2);      // arr2 should now own the resources
    EXPECT_EQ(arr2[0], 10);            // First element should be 10
    EXPECT_EQ(arr2[1], 20);            // Second element should be 20
    EXPECT_EQ(arr1.getSize(), 0);      // arr1 should be empty after move
    EXPECT_EQ(arr1.getCapacity(), 0);  // arr1 should be in a valid state but empty
}

// Test move assignment operator
TEST(DynamicArrayTest, MoveAssignmentOperator)
{
    DynamicArray<int> arr1 = {10, 20};

    DynamicArray<int> arr2(1);  // Initially smaller array
    arr2 = std::move(arr1);     // Move assignment transfers ownership of resources

    EXPECT_EQ(arr2.getSize(), 2);      // arr2 should now own the resources
    EXPECT_EQ(arr2[0], 10);            // First element should be 10
    EXPECT_EQ(arr2[1], 20);            // Second element should be 20
    EXPECT_EQ(arr1.getSize(), 0);      // arr1 should be empty after move
    EXPECT_EQ(arr1.getCapacity(), 0);  // arr1 should be in a valid state but empty
}

// Test self-assignment with copy assignment operator
TEST(DynamicArrayTest, CopyAssignmentSelfAssignment)
{
    DynamicArray<int> arr = {10, 20};
    arr = arr;  // Self-assignment, should not change the array or cause any issues

    EXPECT_EQ(arr.getSize(), 2);  // Size should remain the same
    EXPECT_EQ(arr[0], 10);        // First element should be 10
    EXPECT_EQ(arr[1], 20);        // Second element should be 20
}

// Test self-assignment with move assignment operator
TEST(DynamicArrayTest, MoveAssignmentSelfAssignment)
{
    DynamicArray<int> arr = {10, 20};
    arr = std::move(arr);  // Self-move-assignment, should not cause issues

    EXPECT_EQ(arr.getSize(), 2);  // Size should remain the same
    EXPECT_EQ(arr[0], 10);        // First element should be 10
    EXPECT_EQ(arr[1], 20);        // Second element should be 20
}

// Test begin() and end() functionality
TEST(DynamicArrayTest, BeginEndTest)
{
    DynamicArray<int> arr = {1, 2, 3};
    auto it = arr.begin();

    // Ensure begin() points to the first element
    EXPECT_EQ(*it, 1);

    ++it;
    // Ensure it points to the second element
    EXPECT_EQ(*it, 2);

    ++it;
    // Ensure it points to the third element
    EXPECT_EQ(*it, 3);

    ++it;
    // Ensure end() points past the last element
    EXPECT_EQ(it, arr.end());
}

// Test appending elements and resizing
TEST(DynamicArrayTest, AppendAndResize)
{
    DynamicArray<int> arr = {10, 20};

    EXPECT_EQ(arr.getSize(), 2);      // Size should increase
    EXPECT_EQ(arr.getCapacity(), 2);  // Initial capacity is 2
    EXPECT_EQ(arr[0], 10);            // Validate first element
    EXPECT_EQ(arr[1], 20);            // Validate second element

    // Append beyond the initial capacity
    arr.append(30);

    EXPECT_EQ(arr.getSize(), 3);      // Size should increase
    EXPECT_EQ(arr.getCapacity(), 4);  // Capacity should double
    EXPECT_EQ(arr[2], 30);            // Validate new element
}

// Test operator[] access
TEST(DynamicArrayTest, ElementAccess)
{
    DynamicArray<int> arr = {1, 2, 3};

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);

    // Test out-of-bounds access
    EXPECT_THROW(arr[-1], std::out_of_range);  // Negative index
    EXPECT_THROW(arr[3], std::out_of_range);   // Index equal to size
}

// Test isEmpty method
TEST(DynamicArrayTest, IsEmpty)
{
    DynamicArray<int> arr;
    EXPECT_TRUE(arr.isEmpty());  // Should be empty initially

    arr.append(1);
    EXPECT_FALSE(arr.isEmpty());  // Should not be empty after appending an element
}

// Test resizing functionality
TEST(DynamicArrayTest, Resize)
{
    DynamicArray<int> arr = {1, 2};

    EXPECT_EQ(arr.getCapacity(), 2);  // Capacity before resize

    arr.append(3);                    // Triggers resize
    EXPECT_EQ(arr.getCapacity(), 4);  // Capacity should double
    EXPECT_EQ(arr[0], 1);             // Verify existing elements
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

// Test size and capacity updates
TEST(DynamicArrayTest, SizeAndCapacity)
{
    DynamicArray<int> arr(2);

    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_EQ(arr.getCapacity(), 2);

    arr.append(1);
    EXPECT_EQ(arr.getSize(), 1);
    EXPECT_EQ(arr.getCapacity(), 2);

    arr.append(2);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr.getCapacity(), 2);

    arr.append(3);  // Triggers resize
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr.getCapacity(), 4);
}

// Test appending multiple elements
TEST(DynamicArrayTest, AppendMultipleElements)
{
    DynamicArray<int> arr;
    for (int i = 1; i <= 10; ++i)
    {
        arr.append(i);
    }

    EXPECT_EQ(arr.getSize(), 10);      // Ensure size is updated
    EXPECT_GE(arr.getCapacity(), 10);  // Capacity should be >= size
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(arr[i], i + 1);  // Validate all elements
    }
}

// Test capacity growth pattern
TEST(DynamicArrayTest, CapacityGrowth)
{
    DynamicArray<int> arr(2);
    EXPECT_EQ(arr.getCapacity(), 2);

    arr.append(1);
    arr.append(2);
    EXPECT_EQ(arr.getCapacity(), 2);  // No resize yet

    arr.append(3);                    // Triggers resize
    EXPECT_EQ(arr.getCapacity(), 4);  // Capacity doubles
}

// Test for inserting an element at a specific position
TEST(DynamicArrayTest, Insert)
{
    DynamicArray<int> arr = {1, 2, 3};

    // Insert an element at position 1
    arr.insert(10, 1);

    EXPECT_EQ(arr.getSize(), 4);  // Size should increase
    EXPECT_EQ(arr[0], 1);         // First element should remain the same
    EXPECT_EQ(arr[1], 10);        // Inserted element should be at position 1
    EXPECT_EQ(arr[2], 2);         // Element at position 1 (2) should shift to position 2
    EXPECT_EQ(arr[3], 3);         // Last element should remain the same

    // Test inserting at the beginning
    arr.insert(5, 0);
    EXPECT_EQ(arr[0], 5);  // New element should be at the beginning
    EXPECT_EQ(arr[1], 1);  // The other elements should shift right
    EXPECT_EQ(arr[2], 10);
    EXPECT_EQ(arr[3], 2);
    EXPECT_EQ(arr[4], 3);

    // Test inserting at the last position (size-1)
    arr.insert(20, 5);
    EXPECT_EQ(arr[5], 20);        // The inserted element should be at the end
    EXPECT_EQ(arr.getSize(), 6);  // Size should be 6
    EXPECT_EQ(arr[4], 3);         // Last element should be the one before the inserted one

    // Test inserting at an invalid position
    EXPECT_THROW(arr.insert(30, -1), std::out_of_range);  // Negative position
    EXPECT_THROW(arr.insert(30, 10), std::out_of_range);  // Position greater than current size
}

// Test for inserting at the beginning
TEST(DynamicArrayTest, InsertAtBeginning)
{
    DynamicArray<int> arr = {10, 20, 30};

    arr.insert(5, 0);  // Insert 5 at position 0

    EXPECT_EQ(arr.getSize(), 4);  // Size should be 4
    EXPECT_EQ(arr[0], 5);         // First element should be 5
    EXPECT_EQ(arr[1], 10);        // Second element should be 10
}

// Test for inserting in the middle
TEST(DynamicArrayTest, InsertInMiddle)
{
    DynamicArray<int> arr = {10, 20, 30};

    arr.insert(15, 1);  // Insert 15 at position 1

    EXPECT_EQ(arr.getSize(), 4);  // Size should be 4
    EXPECT_EQ(arr[0], 10);        // First element should be 10
    EXPECT_EQ(arr[1], 15);        // Second element should be 15
    EXPECT_EQ(arr[2], 20);        // Third element should be 20
}

// Test for inserting at the end
TEST(DynamicArrayTest, InsertAtEnd)
{
    DynamicArray<int> arr = {10, 20, 30};

    arr.insert(40, 3);  // Insert 40 at position 3 (end)

    EXPECT_EQ(arr.getSize(), 4);  // Size should be 4
    EXPECT_EQ(arr[3], 40);        // Last element should be 40
}

// Test for inserting when resizing is required
TEST(DynamicArrayTest, InsertAndResize)
{
    DynamicArray<int> arr = {10, 20, 30};

    // Insert at position 3 (the array will be resized as it's full)
    arr.insert(40, 3);

    EXPECT_EQ(arr.getSize(), 4);      // Size should be 4
    EXPECT_EQ(arr.getCapacity(), 6);  // Capacity should be increased after resize
    EXPECT_EQ(arr[3], 40);            // Last element should be 40
}

// Test for inserting at invalid index (negative index)
TEST(DynamicArrayTest, InsertInvalidNegativeIndex)
{
    DynamicArray<int> arr = {10, 20, 30};

    EXPECT_THROW(arr.insert(5, -1), std::out_of_range);  // Should throw out_of_range
}

// Test for inserting at an index greater than current size
TEST(DynamicArrayTest, InsertInvalidIndexGreaterThanSize)
{
    DynamicArray<int> arr = {10, 20, 30};

    EXPECT_THROW(arr.insert(5, 5), std::out_of_range);  // Should throw out_of_range
}

// Test for erasing an element from a non-empty array (middle)
TEST(DynamicArrayTest, EraseMiddleElement)
{
    DynamicArray<int> arr = {10, 20, 30, 40};

    arr.erase(2);  // Erase element at index 2 (value 30)

    EXPECT_EQ(arr.getSize(), 3);  // Size should be 3
    EXPECT_EQ(arr[0], 10);        // First element should be 10
    EXPECT_EQ(arr[1], 20);        // Second element should be 20
    EXPECT_EQ(arr[2], 40);        // Third element should be 40
}

// Test for erasing the first element (index 0)
TEST(DynamicArrayTest, EraseFirstElement)
{
    DynamicArray<int> arr = {10, 20, 30};

    auto it = arr.erase(0);  // Erase element at index 0 (value 10)

    EXPECT_EQ(arr.getSize(), 2);  // Size should be 2
    EXPECT_EQ(arr[0], 20);        // First element should be 20
    EXPECT_EQ(arr[1], 30);        // Second element should be 30
    EXPECT_EQ(*it, 20);
}

// Test for erasing the last element (index mSize - 1)
TEST(DynamicArrayTest, EraseLastElement)
{
    DynamicArray<int> arr = {10, 20, 30};

    auto it = arr.erase(2);  // Erase element at index 2 (value 30)

    EXPECT_EQ(arr.getSize(), 2);  // Size should be 2
    EXPECT_EQ(arr[0], 10);        // First element should be 10
    EXPECT_EQ(arr[1], 20);        // Second element should be 20
    EXPECT_EQ(it, arr.end());
}

// Test for erasing when the array is empty
TEST(DynamicArrayTest, EraseEmptyArray)
{
    DynamicArray<int> arr;
    EXPECT_THROW(arr.erase(0), std::out_of_range);  // Should throw out_of_range
}

// Test for erasing at an invalid index (negative index)
TEST(DynamicArrayTest, EraseInvalidNegativeIndex)
{
    DynamicArray<int> arr = {10, 20, 30};

    EXPECT_THROW(arr.erase(-1), std::out_of_range);  // Should throw out_of_range
}

// Test for erasing at an index greater than the current size
TEST(DynamicArrayTest, EraseInvalidIndexGreaterThanSize)
{
    DynamicArray<int> arr = {10, 20, 30};

    EXPECT_THROW(arr.erase(5), std::out_of_range);  // Should throw out_of_range
}

// Test for erasing when only one element is in the array
TEST(DynamicArrayTest, EraseLastElementInSingleElementArray)
{
    DynamicArray<int> arr;
    arr.append(10);

    auto it = arr.erase(0);  // Erase the only element

    EXPECT_EQ(it, arr.end());
    EXPECT_EQ(arr.getSize(), 0);  // Array should be empty
}
