#include <gtest/gtest.h>
#include <dynamic-array.hpp>
#include <list.hpp>
#include <stack.hpp>

template <typename ContainerType>
class StackTestsWithArrayAndList : public testing::Test
{
};

// Define the container types to be tested for integers
using ContainerTypes = ::testing::Types<DynamicArray<int>, List<int>>;

TYPED_TEST_SUITE(StackTestsWithArrayAndList, ContainerTypes);

// Test: Check if stack is initially empty
TYPED_TEST(StackTestsWithArrayAndList, InitialState)
{
    Stack<int, TypeParam> stack;

    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.getSize(), 0);
}

// Test: Pushing elements into the stack
TYPED_TEST(StackTestsWithArrayAndList, PushElements)
{
    Stack<int, TypeParam> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.getSize(), 3);
}

// Test: Popping elements from the stack
TYPED_TEST(StackTestsWithArrayAndList, PopElements)
{
    Stack<int, TypeParam> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.pop();

    EXPECT_EQ(stack.getSize(), 2);
    EXPECT_EQ(stack.top(), 2);
}

// Test: Getting elements from the stack
TYPED_TEST(StackTestsWithArrayAndList, GetElement)
{
    Stack<int, TypeParam> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    EXPECT_EQ(stack.get(0), 10);
    EXPECT_EQ(stack.get(1), 20);
    EXPECT_EQ(stack.get(2), 30);
}

// Test: Top element retrieval
TYPED_TEST(StackTestsWithArrayAndList, TopElement)
{
    Stack<int, TypeParam> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(stack.top(), 3);
}

// Test: Edge case - Pop until empty
TYPED_TEST(StackTestsWithArrayAndList, PopUntilEmpty)
{
    Stack<int, TypeParam> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.pop();
    stack.pop();

    EXPECT_EQ(stack.getSize(), 1);
    EXPECT_EQ(stack.top(), 1);

    stack.pop();
    EXPECT_TRUE(stack.isEmpty());
}

// Test: Handling out-of-bounds access in `get()`
TYPED_TEST(StackTestsWithArrayAndList, GetOutOfBounds)
{
    Stack<int, TypeParam> stack;
    stack.push(1);
    stack.push(2);

    EXPECT_THROW((void)stack.get(3), std::out_of_range);   // Invalid index
    EXPECT_THROW((void)stack.get(-1), std::out_of_range);  // Invalid negative index
}

// Test: Handling top() when stack is empty
TYPED_TEST(StackTestsWithArrayAndList, TopEmptyStack)
{
    Stack<int, TypeParam> stack;

    EXPECT_THROW(auto result = stack.top(), std::out_of_range);  // Empty stack
}

// Test: Pushing and popping from an empty stack
TYPED_TEST(StackTestsWithArrayAndList, PushPopEmptyStack)
{
    Stack<int, TypeParam> stack;

    stack.push(5);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.getSize(), 1);

    stack.pop();
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.getSize(), 0);
}

// Test: Checking size consistency after multiple pushes and pops
TYPED_TEST(StackTestsWithArrayAndList, SizeConsistency)
{
    Stack<int, TypeParam> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);
    EXPECT_EQ(stack.getSize(), 3);

    stack.pop();
    EXPECT_EQ(stack.getSize(), 2);

    stack.push(4);
    EXPECT_EQ(stack.getSize(), 3);

    stack.pop();
    stack.pop();
    EXPECT_EQ(stack.getSize(), 1);
}

// Test: Stack with a single element
TYPED_TEST(StackTestsWithArrayAndList, SingleElement)
{
    Stack<int, TypeParam> stack;
    stack.push(42);

    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.getSize(), 1);
    EXPECT_EQ(stack.top(), 42);
}

// Test: Large number of elements (stress test)
TYPED_TEST(StackTestsWithArrayAndList, LargeNumberOfElements)
{
    Stack<int, TypeParam> stack;
    const int n = 1000;

    for (int i = 0; i < n; ++i)
    {
        stack.push(i);
    }

    EXPECT_EQ(stack.getSize(), n);

    for (int i = n - 1; i >= 0; --i)
    {
        EXPECT_EQ(stack.top(), i);
        stack.pop();
    }

    EXPECT_TRUE(stack.isEmpty());
}

// Test: Stack with negative numbers
TYPED_TEST(StackTestsWithArrayAndList, NegativeNumbers)
{
    Stack<int, TypeParam> stack;
    stack.push(-1);
    stack.push(-2);
    stack.push(-3);

    EXPECT_EQ(stack.top(), -3);
    stack.pop();
    EXPECT_EQ(stack.top(), -2);
    stack.pop();
    EXPECT_EQ(stack.top(), -1);
}

TYPED_TEST(StackTestsWithArrayAndList, GetNonConstReturnsAllowModification)
{
    Stack<int, TypeParam> stack;
    stack.push(1);

    stack.get(0) = 2;  // Modify via non-const get()
    EXPECT_EQ(stack.top(), 2);
}

TYPED_TEST(StackTestsWithArrayAndList, TopNonConstAllowsModification)
{
    Stack<int, TypeParam> stack;
    stack.push(1);
    stack.top() = 2;  // Modify via non-const top()

    EXPECT_EQ(stack.top(), 2);
}
