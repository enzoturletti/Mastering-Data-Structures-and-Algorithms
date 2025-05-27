#include <gtest/gtest.h>
#include <dynamic-array.hpp>
#include <list.hpp>
#include <queue.hpp>

template <typename ContainerType>
class QueueTestsWithArrayAndList : public ::testing::Test
{
};

using QueueContainerTypes = ::testing::Types<DynamicArray<int>, List<int>>;

TYPED_TEST_SUITE(QueueTestsWithArrayAndList, QueueContainerTypes);

// Initial state test
TYPED_TEST(QueueTestsWithArrayAndList, InitialState)
{
    Queue<int, TypeParam> queue;
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_EQ(queue.getSize(), 0);
}

// Push test
TYPED_TEST(QueueTestsWithArrayAndList, PushElements)
{
    Queue<int, TypeParam> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_FALSE(queue.isEmpty());
    EXPECT_EQ(queue.getSize(), 3);
}

// Front/back tests
TYPED_TEST(QueueTestsWithArrayAndList, FrontBackElements)
{
    Queue<int, TypeParam> queue;
    queue.push(10);
    queue.push(20);
    queue.push(30);

    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 30);
}

// Pop test
TYPED_TEST(QueueTestsWithArrayAndList, PopElements)
{
    Queue<int, TypeParam> queue;
    queue.push(100);
    queue.push(200);

    queue.pop();
    EXPECT_EQ(queue.front(), 200);
    EXPECT_EQ(queue.getSize(), 1);
}

// Empty queue pop
TYPED_TEST(QueueTestsWithArrayAndList, PopOnEmptyThrows)
{
    Queue<int, TypeParam> queue;
    EXPECT_THROW(queue.pop(), std::out_of_range);
}

// Empty queue front/back
TYPED_TEST(QueueTestsWithArrayAndList, FrontBackOnEmptyThrows)
{
    Queue<int, TypeParam> queue;
    EXPECT_THROW((void)queue.front(), std::out_of_range);
    EXPECT_THROW((void)queue.back(), std::out_of_range);
}

// Modify via non-const front/back
TYPED_TEST(QueueTestsWithArrayAndList, NonConstAccessModifiesFrontBack)
{
    Queue<int, TypeParam> queue;
    queue.push(1);
    queue.push(2);

    queue.front() = 10;
    queue.back() = 20;

    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 20);
}

// Multiple operations
TYPED_TEST(QueueTestsWithArrayAndList, PushPopMix)
{
    Queue<int, TypeParam> queue;
    queue.push(5);
    queue.push(6);
    queue.pop();
    queue.push(7);

    EXPECT_EQ(queue.front(), 6);
    EXPECT_EQ(queue.back(), 7);
    EXPECT_EQ(queue.getSize(), 2);
}

// Single element
TYPED_TEST(QueueTestsWithArrayAndList, SingleElementQueue)
{
    Queue<int, TypeParam> queue;
    queue.push(42);

    EXPECT_EQ(queue.front(), 42);
    EXPECT_EQ(queue.back(), 42);

    queue.pop();
    EXPECT_TRUE(queue.isEmpty());
}

// Stress test
TYPED_TEST(QueueTestsWithArrayAndList, LargeNumberOfElements)
{
    Queue<int, TypeParam> queue;
    const int n = 1000;

    for (int i = 0; i < n; ++i)
    {
        queue.push(i);
    }

    EXPECT_EQ(queue.getSize(), n);
    EXPECT_EQ(queue.front(), 0);
    EXPECT_EQ(queue.back(), n - 1);

    for (int i = 0; i < n; ++i)
    {
        EXPECT_EQ(queue.front(), i);
        queue.pop();
    }

    EXPECT_TRUE(queue.isEmpty());
}
