#include <gtest/gtest.h>
#include "single-thread-mutex-queue.hpp"

TEST(SingleThreadMutexQueueTest, PushAndPop) {
    single_thread_mutex_queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_EQ(q.size(), 3);

    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.pop(), 3);

    EXPECT_TRUE(q.empty());
}

TEST(SingleThreadMutexQueueTest, FrontAndBack) {
    single_thread_mutex_queue<std::string> q;

    q.push("first");
    q.push("second");
    q.push("third");

    EXPECT_EQ(q.front(), "first");
    EXPECT_EQ(q.back(), "third");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}