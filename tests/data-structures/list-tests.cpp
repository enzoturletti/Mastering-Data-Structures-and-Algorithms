#include <gtest/gtest.h>
#include <list.hpp>

// Test default constructor and initial size
TEST(ListTest, DefaultConstructor)
{
    List<int> list;
    EXPECT_EQ(list.getSize(), 0);  // Size should be 0 initially
    EXPECT_TRUE(list.isEmpty());   // List should be empty
}

// Test append method
TEST(ListTest, Append)
{
    List<int> list;

    list.append(10);
    list.append(20);

    EXPECT_EQ(list.getSize(), 2);  // Size should be 2 after appending two elements
    EXPECT_EQ(list[0], 10);        // First element should be 10
    EXPECT_EQ(list[1], 20);        // Second element should be 20
}

// Test operator[] for element access
TEST(ListTest, ElementAccess)
{
    List<int> list = {10, 20, 30};

    EXPECT_EQ(list[0], 10);  // First element should be 10
    EXPECT_EQ(list[1], 20);  // Second element should be 20
    EXPECT_EQ(list[2], 30);  // Third element should be 30

    EXPECT_THROW(list[-1], std::out_of_range);  // Negative index should throw exception
    EXPECT_THROW(list[3], std::out_of_range);   // Index equal to size should throw exception
}

// Test getSize method
TEST(ListTest, GetSize)
{
    List<int> list;

    EXPECT_EQ(list.getSize(), 0);  // List should be empty initially

    list.append(10);
    list.append(20);

    EXPECT_EQ(list.getSize(), 2);  // Size should be 2 after adding two elements
}

// Test isEmpty method
TEST(ListTest, IsEmpty)
{
    List<int> list;

    EXPECT_TRUE(list.isEmpty());  // List should be empty initially

    list.append(10);
    EXPECT_FALSE(list.isEmpty());  // List should not be empty after adding an element
}

// Test iterators (begin and end)
TEST(ListTest, Iterators)
{
    List<int> list = {10, 20, 30};

    auto it = list.begin();
    EXPECT_EQ(*it, 10);  // First element should be 10

    ++it;
    EXPECT_EQ(*it, 20);  // Second element should be 20

    ++it;
    EXPECT_EQ(*it, 30);  // Third element should be 30

    ++it;
    EXPECT_EQ(it, list.end());  // Should be at the end of the list now

    --it;
    EXPECT_EQ(*it, 30);  // Third element should be 30
    EXPECT_EQ(it, list.end() - 1);
}

// Test appending and resizing (e.g., maintaining correct size)
TEST(ListTest, AppendAndResize)
{
    List<int> list;
    list.append(10);
    list.append(20);

    EXPECT_EQ(list.getSize(), 2);  // Size should be 2 after appending two elements
    EXPECT_EQ(list[0], 10);        // Validate first element
    EXPECT_EQ(list[1], 20);        // Validate second element

    list.append(30);  // Adding another element

    EXPECT_EQ(list.getSize(), 3);  // Size should now be 3
    EXPECT_EQ(list[2], 30);        // Validate third element
}

// Test append method with large number of elements
TEST(ListTest, AppendMultipleElements)
{
    List<int> list;
    for (int i = 0; i < 100; ++i)
    {
        list.append(i);
    }

    EXPECT_EQ(list.getSize(), 100);  // Size should be 100
    EXPECT_EQ(list[0], 0);           // Validate first element
    EXPECT_EQ(list[99], 99);         // Validate last element
}

// Test for copy constructor
TEST(ListTest, CopyConstructor)
{
    List<int> lst1 = {10, 20, 30};

    // Using copy constructor to create a new list
    List<int> lst2 = lst1;

    EXPECT_EQ(lst2.getSize(), lst1.getSize());  // Size should be the same
    EXPECT_EQ(lst2[0], lst1[0]);                // First element should be same
    EXPECT_EQ(lst2[1], lst1[1]);                // Second element should be same
    EXPECT_EQ(lst2[2], lst1[2]);                // Third element should be same
}

// Test for copy assignment operator
TEST(ListTest, CopyAssignmentOperator)
{
    List<int> lst1 = {10, 20, 30};

    List<int> lst2;
    lst2 = lst1;  // Using copy assignment operator

    EXPECT_EQ(lst2.getSize(), lst1.getSize());  // Size should be the same
    EXPECT_EQ(lst2[0], lst1[0]);                // First element should be same
    EXPECT_EQ(lst2[1], lst1[1]);                // Second element should be same
    EXPECT_EQ(lst2[2], lst1[2]);                // Third element should be same
}

// Test for move constructor
TEST(ListTest, MoveConstructor)
{
    List<int> lst1 = {10, 20, 30};

    // Using move constructor
    List<int> lst2 = std::move(lst1);

    EXPECT_EQ(lst2.getSize(), 3);  // lst2 should now have the elements
    EXPECT_EQ(lst2[0], 10);        // First element should be 10
    EXPECT_EQ(lst2[1], 20);        // Second element should be 20
    EXPECT_EQ(lst2[2], 30);        // Third element should be 30

    // lst1 should be in a valid but empty state
    EXPECT_EQ(lst1.getSize(), 0);
}

// Test for move assignment operator
TEST(ListTest, MoveAssignmentOperator)
{
    List<int> lst1 = {10, 20, 30};

    List<int> lst2;
    lst2 = std::move(lst1);  // Using move assignment operator

    EXPECT_EQ(lst2.getSize(), 3);  // lst2 should now have the elements
    EXPECT_EQ(lst2[0], 10);        // First element should be 10
    EXPECT_EQ(lst2[1], 20);        // Second element should be 20
    EXPECT_EQ(lst2[2], 30);        // Third element should be 30

    // lst1 should be in a valid but empty state
    EXPECT_EQ(lst1.getSize(), 0);
}

// Test for self-assignment (copy assignment)
TEST(ListTest, CopyAssignmentSelfAssignment)
{
    List<int> list = {10, 20, 30};

    list = list;  // Self-assignment should not change the list

    EXPECT_EQ(list.getSize(), 3);  // Size should remain the same
    EXPECT_EQ(list[0], 10);        // First element should be 10
    EXPECT_EQ(list[1], 20);        // Second element should be 20
    EXPECT_EQ(list[2], 30);        // Third element should be 30
}

// Test for self-assignment (move assignment)
TEST(ListTest, MoveAssignmentSelfAssignment)
{
    List<int> list = {10, 20, 30};

    list = std::move(list);  // Self-move-assignment should not cause issues

    EXPECT_EQ(list.getSize(), 3);  // Size should remain the same
    EXPECT_EQ(list[0], 10);        // First element should be 10
    EXPECT_EQ(list[1], 20);        // Second element should be 20
    EXPECT_EQ(list[2], 30);        // Third element should be 30
}

// Test for inserting an element at a specific position
TEST(ListTest, Insert)
{
    List<int> list = {10, 20, 30};

    auto it = list.insert(15, 1);  // Insert 15 at position 1

    EXPECT_EQ(*it, 15);
    EXPECT_EQ(list.getSize(), 4);  // Size should increase to 4
    EXPECT_EQ(list[0], 10);        // First element should be 10
    EXPECT_EQ(list[1], 15);        // Inserted element should be 15 at position 1
    EXPECT_EQ(list[2], 20);        // Element 20 should shift to position 2
    EXPECT_EQ(list[3], 30);        // Last element should be 30
}

TEST(ListTest, InsertAtEnd)
{
    List<int> list = {1, 2, 3};
    auto it = list.insert(4, list.getSize());
    EXPECT_EQ(list.getSize(), 4);  // Size should increase to 4
    EXPECT_EQ(*(list.end() - 1), 4);
    EXPECT_EQ(*it, 4);
}

TEST(ListTest, InsertInMiddle)
{
    List<int> list = {1, 3};
    auto it = list.insert(2, 1);
    EXPECT_EQ(list.getSize(), 3);  // Size should increase to 3
    EXPECT_EQ(*(list.end() - 1), 3);
    EXPECT_EQ(*it, 2);
}

TEST(ListTest, AppendElements)
{
    List<int> list = {1, 2};
    list.append(3);
    EXPECT_EQ(list.getSize(), 3);  // Size should increase to 3
    EXPECT_EQ(*(list.end() - 1), 3);
}

TEST(ListTest, AppendAfterEraseAll)
{
    List<int> list = {1, 2, 3};
    list.clear();
    list.append(4);
    EXPECT_EQ(*(list.end() - 1), 4);
}

TEST(ListTest, SingleElement)
{
    List<int> list = {1};
    EXPECT_EQ(*(list.end() - 1), 1);
}

TEST(ListTest, EmptyContainerEndMinusOne)
{
    List<int> list = {};
    list.clear();
    EXPECT_TRUE(list.isEmpty());  // List should be empty initially
    EXPECT_THROW(list.end() - 1, std::runtime_error);
}

// Test for inserting at an invalid position (out of range)
TEST(ListTest, InsertInvalidIndex)
{
    List<int> list = {10, 20, 30};

    EXPECT_THROW(list.insert(25, -1), std::out_of_range);  // Negative index should throw exception
    EXPECT_THROW(list.insert(25, 10), std::out_of_range);  // Index greater than current size should throw exception
}

// Test for removing an element at a specific position
TEST(ListTest, Erase)
{
    List<int> list = {10, 20, 30};

    auto it = list.erase(1);  // Erase element at position 1 (value 20)

    EXPECT_EQ(list.getSize(), 2);  // Size should decrease to 2
    EXPECT_EQ(list[0], 10);        // First element should remain 10
    EXPECT_EQ(list[1], 30);        // Second element should be 30
    EXPECT_EQ(*it, 30);
}

// Test for removing from an empty list
TEST(ListTest, EraseEmptyList)
{
    List<int> list;
    EXPECT_EQ(list.getSize(), 0);                    // Size should decrease to 0
    EXPECT_THROW(list.erase(0), std::out_of_range);  // Erasing from empty list should throw exception
}

TEST(ListTest, EraseLastElement)
{
    List<int> list = {1, 2, 3};

    auto it = list.erase(list.getSize() - 1);

    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(*(list.end() - 1), 2);
    EXPECT_EQ(it, list.end());
}

TEST(ListTest, EraseMiddleElement)
{
    List<int> list = {1, 2, 3};
    auto it = list.erase(1);

    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 3);
    EXPECT_EQ(*(list.end() - 1), 3);
    EXPECT_EQ(*it, 3);
}

TEST(ListTest, IteratorIncrementDecrement)
{
    List<int> list = {10, 20, 30};
    auto it = list.begin();

    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    --it;
    EXPECT_EQ(*it, 10);

    auto it2 = list.end();
    --it2;
    EXPECT_EQ(*it2, 30);
}

TEST(ListTest, IteratorArithmetic)
{
    List<int> list = {10, 20, 30, 40};
    auto it = list.begin();
    EXPECT_EQ(*it, 10);
    EXPECT_EQ(*(it + 1), 20);
    EXPECT_EQ(*(it + 2), 30);
    EXPECT_EQ(*(it + 3), 40);

    auto it2 = list.begin() + 3;
    EXPECT_EQ(*it2, 40);
    EXPECT_TRUE(it <= it2);
    EXPECT_TRUE(it2 >= it);

    // Check the distance between iterators
    EXPECT_EQ(it2 - it, 3);   // Should be positive, distance from beginning to last
    EXPECT_EQ(it - it2, -3);  // Should be negative, reverse distance from last to first
}

TEST(ListTest, IteratorArithmeticOneElement)
{
    List<int> list = {10};
    auto low = list.begin();
    auto high = list.end() - 1;

    // Check the distance between iterators
    EXPECT_EQ(low - high, 0);
    EXPECT_EQ(high - low, 0);
    EXPECT_EQ(low, high);
}

TEST(ListTest, IteratorOneElement)
{
    List<int> list = {10};
    auto begin = list.begin();
    auto end = list.end();

    EXPECT_EQ(begin, end - 1);
    EXPECT_TRUE(begin == end - 1);
    EXPECT_TRUE(begin <= end - 1);
    EXPECT_TRUE(begin >= end - 1);
}

TEST(ListTest, ConstIterator)
{
    const List<int> list = {10, 20, 30};
    auto it = list.begin();

    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
}

TEST(ListTest, Clear)
{
    List<int> list = {10, 20, 30};
    list.clear();

    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 0);
}

TEST(ListTest, InsertEmptyList)
{
    List<int> list;
    auto it = list.insert(10, 0);

    EXPECT_EQ(list.getSize(), 1);
    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(*it, 10);
}

TEST(ListTest, EraseSingleElement)
{
    List<int> list = {10};
    auto it = list.erase(0);

    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_EQ(it, list.end());
}

TEST(ListTest, InitializerListConstructor)
{
    List<std::string> list = {"apple", "banana", "cherry"};

    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list[0], "apple");
    EXPECT_EQ(list[1], "banana");
    EXPECT_EQ(list[2], "cherry");
}

TEST(ListTest, EraseFirstElement)
{
    List<int> list = {1, 2, 3};
    auto it = list.erase(0);

    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list[0], 2);
    EXPECT_EQ(*it, 2);
}

TEST(ListTest, InsertAtBeginning)
{
    List<int> list = {1, 2, 3};
    auto it = list.insert(0, 0);
    EXPECT_EQ(list[0], 0);
    EXPECT_EQ(*it, 0);
}
