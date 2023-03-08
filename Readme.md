# Cute Queues

This is a C++ header only library for code 
All queue is either std::list , or self-maintained queue_node in queue_node.hpp

## Command to run all test
```bash
ctest -C Debug -V
```
## single-thread-mutex-queue

This queue is just simply a queue + a mutex that cover the whole queue. 
So at any moment, there are only at most one thread read/write the queue

## single-thread-head-and-single-thread-tail-mutex-queue

This queue is having 2 mutex, one for head, one for tail.
For operation like size, this will lock both mutexes using scoped_lock

` Disadvantage : ` 

- if one thread do a push function , another thread do a pop function , it is not sure that the pop function return what push function did as there is no guarantee that push function happen before pop 
- the pop function will not wait until there are data when the queue is empty

## single-thread-head-and-single-thread-tail-mutex-queue-with-signal

This queue is having 2 mutex, one for head, one for tail.
For operation like size, this will lock both mutexes using scoped_lock

There is a wait 

` Disadvantage : ` 
- High chance of un-ending thread when there are multiple thread responsible to pop

## single-thread-head-and-single-thread-tail-mutex-queue

This queue is using atomic node 

`Disadvantage : ` 

-Cpu need to have an CAS api






single-thread-mutex-queue-with-conditional-variable
single-thread-mutex(atomic_flag)-with-conditional-variable