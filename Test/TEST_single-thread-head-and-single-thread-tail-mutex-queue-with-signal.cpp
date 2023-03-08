#include <gtest/gtest.h>
#include "../single-thread-head-and-single-thread-tail-mutex-queue-with-signal.hpp"

#include <atomic>
#include <thread>
#include <vector> 

TEST(SingleThreadHeadANdSingleThreadTailMutexQueueWithSignalTest, ConstructorTest) {
  single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(0, q.size());
}

TEST(SingleThreadHeadANdSingleThreadTailMutexQueueWithSignalTest, CopyConstructorTest) {
  single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q1;
  q1.push(1);
  q1.push(2);
  q1.push(3);
  single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q2(q1);
  EXPECT_FALSE(q1.empty());
  EXPECT_EQ(3, q1.size());
  EXPECT_FALSE(q2.empty());
  EXPECT_EQ(3, q2.size());
  EXPECT_EQ(q1.front(), q2.front());
}

TEST(SingleThreadHeadANdSingleThreadTailMutexQueueWithSignalTest, CopyAssignmentOperatorTest) {
  single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q1;
  q1.push(1);
  q1.push(2);
  q1.push(3);
  single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q2;
  q2 = q1;
  EXPECT_FALSE(q1.empty());
  EXPECT_EQ(3, q1.size());
  EXPECT_FALSE(q2.empty());
  EXPECT_EQ(3, q2.size());
  EXPECT_EQ(q1.front(), q2.front());
}

TEST(SingleThreadHeadANdSingleThreadTailMutexQueueWithSignalTest, MoveConstructorTest) {
  single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q1;
  q1.push(1);
  q1.push(2);
  q1.push(3);
  single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q2(std::move(q1));
  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(0, q1.size());
  EXPECT_FALSE(q2.empty());
  EXPECT_EQ(3, q2.size());
}

TEST(SingleThreadHeadANdSingleThreadTailMutexQueueWithSignalTest, MoveAssignmentOperatorTest) {
  single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q1;
  q1.push(1);
  q1.push(2);
  q1.push(3);
  single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q2;
  q2 = std::move(q1);
  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(0, q1.size());
  EXPECT_FALSE(q2.empty());
  EXPECT_EQ(3, q2.size());
}


// Test the push function
TEST(SingleThreadHeadANdSingleThreadTailMutexQueueWithSignalTest, Push) {
    single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q;
    q.push(1);
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 1);
    q.push(2);
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 2);
}

// Test the pop function
TEST(SingleThreadHeadANdSingleThreadTailMutexQueueWithSignalTest, Pop) {
    single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q;
    q.push(1);
    q.push(2);
    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 2);
    EXPECT_EQ(q.back(), 2);
    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.size(), 0); 
}

// Test the front function
TEST(SingleThreadHeadANdSingleThreadTailMutexQueueWithSignalTest, Front) {
    single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q;
    q.push(1);
    EXPECT_EQ(q.front(), 1);
    q.push(2);
    EXPECT_EQ(q.front(), 1);
    q.pop();
    EXPECT_EQ(q.front(), 2);
}

// Test the back function
TEST(SingleThreadHeadANdSingleThreadTailMutexQueueWithSignalTest, Back) {
    single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q;
    q.push(1);
    EXPECT_EQ(q.back(), 1);
    q.push(2);
    EXPECT_EQ(q.back(), 2);
    q.pop();
    EXPECT_EQ(q.back(), 2);
}

// Test the empty function
TEST(SingleThreadHeadANdSingleThreadTailMutexQueueWithSignalTest, Empty) {
    single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q;
    EXPECT_TRUE(q.empty());
    q.push(1);
    EXPECT_FALSE(q.empty());
    q.pop();
    EXPECT_TRUE(q.empty());
}

// Test the size function
TEST(SingleThreadHeadANdSingleThreadTailMutexQueueWithSignalTest, Size) {
    single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q;
    EXPECT_EQ(q.size(), 0);
    q.push(1);
    EXPECT_EQ(q.size(), 1);
    q.push(2);
    EXPECT_EQ(q.size(), 2);
    q.pop();
    EXPECT_EQ(q.size(), 1);
    q.pop();
    EXPECT_EQ(q.size(), 0);
}


// Test the push and pop functions with multiple threads
TEST(SingleThreadHeadANdSingleThreadTailMutexQueueWithSignalTest, ConcurrentPushPop) {
    single_thread_head_and_single_thread_tail_mutex_queue_with_singal<int> q;
    const int num_threads = 10;
    const int num_elements = 1000;
    std::atomic<int> sum{0};

    auto producer = [&q, num_elements]() {
        for (int i = 0; i < num_elements; ++i) {
            q.push(i);
        }
    };

    auto consumer = [&q, num_elements, &sum]() {
        for (int i = 0; i < num_elements; ++i) {
            int val = q.pop(); 
            sum += val; 
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(producer);
    }
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(consumer);
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}