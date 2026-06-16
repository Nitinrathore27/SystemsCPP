#include <gtest/gtest.h>
#include "ConnectionPool.h"

// Test 1: Pool initializes with correct number of connections ---
TEST(ConnectionPoolTest, PoolInitializesWithCorrectSize)
{
    ConnectionPool pool(3);

    auto c1 = pool.acquireConnection();
    auto c2 = pool.acquireConnection();
    auto c3 = pool.acquireConnection();

    EXPECT_NE(c1, nullptr);
    EXPECT_NE(c2, nullptr);
    EXPECT_NE(c3, nullptr);
}

// Test 2: Acquiring from empty pool returns empty unique_ptr ---
TEST(ConnectionPoolTest, AcquireFromEmptyPoolReturnsNull)
{
    ConnectionPool pool(1);

    auto c1 = pool.acquireConnection(); // drains the pool
    auto c2 = pool.acquireConnection(); // pool is empty

    EXPECT_EQ(c2, nullptr);
}

// Test 3: Released connection can be re-acquired ---
TEST(ConnectionPoolTest, ReleasedConnectionIsReusable)
{
    ConnectionPool pool(1);

    auto conn = pool.acquireConnection();
    ASSERT_NE(conn, nullptr);

    pool.releaseConnection(std::move(conn)); // ownership back to pool
    EXPECT_EQ(conn, nullptr);                // conn is now empty after move

    auto conn2 = pool.acquireConnection(); // should succeed again
    EXPECT_NE(conn2, nullptr);
}

// Test 4: Pool size is respected (can't acquire more than poolSize) ---
TEST(ConnectionPoolTest, CannotAcquireMoreThanPoolSize)
{
    ConnectionPool pool(2);

    auto c1 = pool.acquireConnection();
    auto c2 = pool.acquireConnection();
    auto c3 = pool.acquireConnection(); // should fail

    EXPECT_NE(c1, nullptr);
    EXPECT_NE(c2, nullptr);
    EXPECT_EQ(c3, nullptr);
}

// Test 5: executeQuery runs without crashing ---
TEST(ConnectionPoolTest, ExecuteQueryDoesNotCrash)
{
    ConnectionPool pool(1);

    auto conn = pool.acquireConnection();
    ASSERT_NE(conn, nullptr);

    EXPECT_NO_THROW(conn->executeQuery("SELECT 1;"));
}

// Test 6: Full acquire → release → re-acquire cycle ---
TEST(ConnectionPoolTest, FullCycleWorksCorrectly)
{
    ConnectionPool pool(2);

    auto c1 = pool.acquireConnection();
    auto c2 = pool.acquireConnection();
    EXPECT_EQ(pool.acquireConnection(), nullptr); // pool empty

    pool.releaseConnection(std::move(c1));
    pool.releaseConnection(std::move(c2));

    // Both slots available again
    auto c3 = pool.acquireConnection();
    auto c4 = pool.acquireConnection();
    EXPECT_NE(c3, nullptr);
    EXPECT_NE(c4, nullptr);
}