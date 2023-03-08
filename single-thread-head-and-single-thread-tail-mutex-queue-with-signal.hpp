#include <queue>
#include <optional>
#include <condition_variable>
#include <mutex>

template <class T>
class single_thread_head_and_single_thread_tail_mutex_queue_with_singal {
    public:
        // Constructor
        single_thread_head_and_single_thread_tail_mutex_queue_with_singal() = default;

        // Copy constructor
        single_thread_head_and_single_thread_tail_mutex_queue_with_singal(const single_thread_head_and_single_thread_tail_mutex_queue_with_singal& other) { 
            std::scoped_lock lock{other.head_m, other.tail_m}; 
            q = other.q;
        }

        // Copy assignment operator
        single_thread_head_and_single_thread_tail_mutex_queue_with_singal& operator=(const single_thread_head_and_single_thread_tail_mutex_queue_with_singal& other) {
            if (this != &other) {
                std::scoped_lock lock{head_m, tail_m}; 
                std::scoped_lock other_lock{other.head_m, other.tail_m}; 
                q = other.q;
            }
            return *this;
        }

        // Move constructor
        single_thread_head_and_single_thread_tail_mutex_queue_with_singal(single_thread_head_and_single_thread_tail_mutex_queue_with_singal&& other) {
            std::scoped_lock lock{other.head_m, other.tail_m}; 
            q = std::move(other.q);
        }

        // Move assignment operator
        single_thread_head_and_single_thread_tail_mutex_queue_with_singal& operator=(single_thread_head_and_single_thread_tail_mutex_queue_with_singal&& other) {
            if (this != &other) {
                std::scoped_lock lock{head_m, tail_m}; 
                std::scoped_lock other_lock{other.head_m, other.tail_m}; 
                q = std::move(other.q);
            }
            return *this;
        }

        void push(const T& val) {
            std::unique_lock<std::mutex> lock(tail_m);
            q.push(val);
            has_data.notify_one();
        };

        T pop() {
            std::unique_lock<std::mutex> lock(head_m);
            // has_data.wait(
            //     head_m,
            //     [this](){ return !q.empty(); }
            // );
            has_data.wait(lock, [this](){ return !q.empty(); });
            T val = q.front();
            q.pop();
            return val;
        };

        T front() {
            std::unique_lock<std::mutex> lock(head_m);
            return q.front();
        }; 

        T back() {
            std::unique_lock<std::mutex> lock(tail_m);
            return q.back();
        };

        bool empty() {
            std::scoped_lock lock{head_m, tail_m};
            return q.empty();
        };

        size_t size() {
            std::scoped_lock lock{head_m, tail_m};
            return q.size();
        };

    private:
        std::queue<T> q;
        mutable std::mutex head_m;
        mutable std::mutex tail_m;
        mutable std::condition_variable has_data;
};
