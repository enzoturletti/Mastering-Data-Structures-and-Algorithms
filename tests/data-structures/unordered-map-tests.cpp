#include <gtest/gtest.h>
#include <unordered-map.hpp>

TEST(UnorderedMapTest, InsertAndFind)
{
    UnorderedMap<std::string> map;
    map.insert(42, "Hello");
    map.insert(100, "World");

    EXPECT_EQ(map.find(42).value(), "Hello");
    EXPECT_EQ(map.find(100).value(), "World");
    EXPECT_FALSE(map.find(200).has_value());
}

TEST(UnorderedMapTest, DuplicateInsertUpdatesValue)
{
    UnorderedMap<int> map;
    map.insert(10, 1);
    map.insert(10, 999);  // Should update

    auto result = map.find(10);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 999);
}

TEST(UnorderedMapTest, EraseWorks)
{
    UnorderedMap<int> map;
    map.insert(5, 50);
    map.insert(6, 60);
    map.erase(5);

    EXPECT_FALSE(map.find(5).has_value());
    EXPECT_TRUE(map.find(6).has_value());
}

TEST(UnorderedMapTest, LoadFactor)
{
    UnorderedMap<int, 4> map;
    map.insert(1, 10);
    map.insert(2, 20);
    EXPECT_FLOAT_EQ(map.loadFactor(), 0.5f);
}
