#include <gtest/gtest.h>
#include "LRUCache.h"
#include <string>

// Test Instantiation & Empty Cache ---
TEST(LRUCacheTest, EmptyCacheReturnsNullopt)
{
    LRUCache<int, std::string> cache(2);

    // Using structured bindings or auto for cleaner C++17 code
    auto result = cache.get(1);

    EXPECT_FALSE(result.has_value());
}

// Test Basic Put and Get ---
TEST(LRUCacheTest, PutAndGetSingleElement)
{
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");

    auto result = cache.get(1);

    // Use ASSERT_TRUE because if it's false, calling .value() will crash the test
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "one");
}

// Test LRU Eviction Policy ---
TEST(LRUCacheTest, EvictsLeastRecentlyUsed)
{
    LRUCache<int, int> cache(2); // Capacity of 2

    cache.put(1, 10); // Cache: [1]
    cache.put(2, 20); // Cache: [2, 1]
    cache.put(3, 30); // Cache over capacity! Evicts 1. Cache: [3, 2]

    EXPECT_FALSE(cache.get(1).has_value());
    EXPECT_TRUE(cache.get(2).has_value());
    EXPECT_TRUE(cache.get(3).has_value());
}

// Test Updating an Existing Key ---
TEST(LRUCacheTest, UpdateExistingKeyUpdatesValueAndMovesToFront)
{
    LRUCache<int, int> cache(2);

    cache.put(1, 10);
    cache.put(2, 20); // Cache: [2, 1]

    // Update key 1. This should change its value AND make it Most Recently Used
    cache.put(1, 15); // Cache: [1, 2]

    // Add a 3rd key. Because 1 was recently updated, 2 should be evicted!
    cache.put(3, 30); // Cache: [3, 1]

    auto result = cache.get(1);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 15); // Verify value was updated

    EXPECT_FALSE(cache.get(2).has_value()); // Verify 2 was the one evicted
}