

cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the compiler to clang++
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

# # Add the source files
# add_executable(sudokugenerator main.cpp SudokuGenerator.cpp DataBase.cpp Sudoku.cpp )  

include(CTest)
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

# # Link the sqlite3 and benchmark library
# target_link_libraries(sudokugenerator sqlite3 benchmark::benchmark GTest::gtest GTest::gtest_main)
# target_link_libraries(sudokugenerator_test sqlite3 benchmark::benchmark GTest::gtest GTest::gtest_main)

add_executable(TEST_SingleThreadMutexQueue ./Test/TEST_single-thread-mutex-queue.cpp)
target_link_libraries(TEST_SingleThreadMutexQueue GTest::gtest GTest::gtest_main)
add_test(NAME AllTestsIn_TEST_SingleThreadMutexQueue COMMAND TEST_SingleThreadMutexQueue)

add_executable(TEST_SingleThreadHeadANdSingleThreadTailMutexQueue ./Test/TEST_single-thread-head-and-single-thread-tail-mutex-queue.cpp)
target_link_libraries(TEST_SingleThreadHeadANdSingleThreadTailMutexQueue GTest::gtest GTest::gtest_main)
add_test(NAME AllTestsIn_TEST_SingleThreadHeadANdSingleThreadTailMutexQueue COMMAND TEST_SingleThreadHeadANdSingleThreadTailMutexQueue)

add_executable(TEST_SingleThreadHeadANdSingleThreadTailMutexQueueWithSignal ./Test/TEST_single-thread-head-and-single-thread-tail-mutex-queue-with-signal.cpp)
target_link_libraries(TEST_SingleThreadHeadANdSingleThreadTailMutexQueueWithSignal GTest::gtest GTest::gtest_main)
add_test(NAME AllTestsIn_TEST_SingleThreadHeadANdSingleThreadTailMutexQueueWithSignal COMMAND TEST_SingleThreadHeadANdSingleThreadTailMutexQueueWithSignal)

# add_executable(TEST_AtomicQueueNode ./Test/TEST_atomic_queue_node.cpp)
# target_link_libraries(TEST_AtomicQueueNode GTest::gtest GTest::gtest_main)
# add_test(NAME AllTestsIn_TEST_AtomicQueueNode COMMAND TEST_AtomicQueueNode)