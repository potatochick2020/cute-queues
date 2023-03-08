#include <atomic>
#include <queue>
#include <optional>
#include <condition_variable>
#include "./include/queue_node/queue_node.hpp"
template <class T>
class single_thread_head_and_single_thread_tail_mutex_queue_with_singal {
    public:
        // Constructor
        single_thread_head_and_single_thread_tail_mutex_queue_with_singal() = default;

        // Copy constructor
        single_thread_head_and_single_thread_tail_mutex_queue_with_singal(const single_thread_head_and_single_thread_tail_mutex_queue_with_singal& other) {  
        }

        // Copy assignment operator
        single_thread_head_and_single_thread_tail_mutex_queue_with_singal& operator=(const single_thread_head_and_single_thread_tail_mutex_queue_with_singal& other) { 
        }

        // Move constructor
        single_thread_head_and_single_thread_tail_mutex_queue_with_singal(single_thread_head_and_single_thread_tail_mutex_queue_with_singal&& other) { 
        }

        // Move assignment operator
        single_thread_head_and_single_thread_tail_mutex_queue_with_singal& operator=(single_thread_head_and_single_thread_tail_mutex_queue_with_singal&& other) { 
        }

        void push(const T& val) {
            std::atomic_queue_node* const new_node = new node(data);
            do (
                atomic_queue_node* old_tail = tail.load();
                flag putted = oid_tail->next.compare_exchange_weak(nullptr, new_node);
            ) while (!putted) 
        };

        std::shared_ptr<T> pop() { 
            atomic_queue_node* old_head;
            do (
                old_head = head.load();
                flag popped = old_head.compare_exchange_weak(head, old_head->next);
            ) while (!popped) 
            return old_head? old_head->data : nullptr;
        };

        std::shared_ptr<T> front() {  
            atomic_queue_node* old_head;
            do (
                old_head = head.load();
                flag is_front = old_head.compare_exchange_weak(head, head);
            ) while (!is_front) 
            return old_head? old_head->data : nullptr;
        };

        std::shared_ptr<T> back() { 
            atomic_queue_node* old_tail;
            do (
                old_tail = tail.load();
                flag is_back = old_tail.compare_exchange_weak(tail, tail);
            ) while (!is_back) 
            return old_tail? old_tail->data : nullptr;

        };

        bool empty() { 
            if (head.load() == tail.load()) {
                return true;
            } else {
                return false;
            }
        };

    private:
        std::atomic<atomic_queue_node*> head;
        std::atomic<atomic_queue_node*> tail; 
};
