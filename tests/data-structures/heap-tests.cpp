#include <gtest/gtest.h>
#include <algorithm>
#include <chrono>
#include <heap.hpp>
#include <random>
#include <vector>

class HeapTests : public ::testing::Test
{
protected:
    MinHeap<int> heap;

    bool isMinHeap(const std::vector<int>& vec)
    {
        int n = vec.size();
        for (int i = 0; i < n; ++i)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n && vec[i] > vec[left])
            {
                return false;
            }

            if (right < n && vec[i] > vec[right])
            {
                return false;
            }
        }
        return true;
    }
};

TEST_F(HeapTests, HeapPropertyMaintainedAfterInsertions)
{
    std::vector<int> values = {20, 5, 15, 30, 1, 10};

    for (int v : values)
    {
        heap.insert(v);
    }

    std::vector<int> vec = heap.toVector();
    EXPECT_TRUE(isMinHeap(vec));
}

TEST_F(HeapTests, HeapPropertyAfterSortedInserts)
{
    for (int i = 1; i <= 100; ++i)
    {
        heap.insert(i);
    }
    EXPECT_TRUE(isMinHeap(heap.toVector()));
}

TEST_F(HeapTests, HeapPropertyAfterReverseSortedInserts)
{
    for (int i = 100; i >= 1; --i)
    {
        heap.insert(i);
    }
    EXPECT_TRUE(isMinHeap(heap.toVector()));
}

TEST_F(HeapTests, HeapPropertyMaintainedAfterRandomInsertions)
{
    // Seed with current time
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(1, 1000);

    const int numElements = 100;
    for (int i = 0; i < numElements; ++i)
    {
        heap.insert(dist(rng));
    }

    std::vector<int> heapData = heap.toVector();
    EXPECT_TRUE(isMinHeap(heapData));
}

TEST_F(HeapTests, PopMaintainsMinHeapProperty)
{
    std::vector<int> values = {10, 4, 5, 30, 3, 8};

    for (int v : values)
        heap.insert(v);

    heap.pop();  // Remove root

    std::vector<int> vec = heap.toVector();
    EXPECT_TRUE(isMinHeap(vec));
}

TEST_F(HeapTests, PopFromEmptyHeapDoesNotCrash)
{
    EXPECT_NO_THROW(heap.pop());
}

TEST_F(HeapTests, HeapPropertyMaintainedAfterRandomPops)
{
    // Seed with current time
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(1, 1000);

    const int numElements = 100;
    for (int i = 0; i < numElements; ++i)
    {
        heap.insert(dist(rng));
    }

    std::vector<int> heapData = heap.toVector();
    EXPECT_TRUE(isMinHeap(heapData));

    for (int i = 0; i < numElements; ++i)
    {
        heap.pop();
        EXPECT_TRUE(isMinHeap(heapData));
    }
}