#include <gtest/gtest.h>
#include "../include/queue_node/atomic_queue_node.hpp"

TEST(AtomicQueueNodeTest, ConstructorTest) {
  int data = 42;
  atomic_queue_node<int> node(data); 
}

TEST(AtomicQueueNodeTest, CopyConstructorTest) {
  int data = 42;
  atomic_queue_node<int> node1(data);
  atomic_queue_node<int> node2(node1); 
}

TEST(AtomicQueueNodeTest, MoveConstructorTest) {
  int data = 42;
  atomic_queue_node<int> node1(data);
  atomic_queue_node<int> node2(std::move(node1)); 
}

TEST(AtomicQueueNodeTest, CopyAssignmentOperatorTest) {
  int data1 = 42;
  int data2 = 23;
  atomic_queue_node<int> node1(data1);
  atomic_queue_node<int> node2(data2);
  node1 = node2; 
}

TEST(AtomicQueueNodeTest, MoveAssignmentOperatorTest) {
  int data1 = 42;
  int data2 = 23;
  atomic_queue_node<int> node1(data1);
  atomic_queue_node<int> node2(data2);
  node1 = std::move(node2); 
}

TEST(AtomicQueueNodeTest, DestructorTest) {
  int data = 42;
  {
    atomic_queue_node<int> node(data); 
  } 
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}