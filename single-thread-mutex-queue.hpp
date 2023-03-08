#include <queue>
#include <optional>
#include <mutex>

template <class T>
class single_thread_mutex_queue {
    public:
        // Constructor
        single_thread_mutex_queue() = default;

        // Copy constructor
        single_thread_mutex_queue(const single_thread_mutex_queue& other) {
            std::unique_lock<std::mutex> lock(other.m);
            q = other.q;
        }

        // Copy assignment operator
        single_thread_mutex_queue& operator=(const single_thread_mutex_queue& other) {
            if (this != &other) {
                std::unique_lock<std::mutex> lock(m);
                std::unique_lock<std::mutex> lock_other(other.m);
                q = other.q;
            }
            return *this;
        }

        // Move constructor
        single_thread_mutex_queue(single_thread_mutex_queue&& other) {
            std::unique_lock<std::mutex> lock(other.m);
            q = std::move(other.q);
        }

        // Move assignment operator
        single_thread_mutex_queue& operator=(single_thread_mutex_queue&& other) {
            if (this != &other) {
                std::unique_lock<std::mutex> lock(m);
                std::unique_lock<std::mutex> lock_other(other.m);
                q = std::move(other.q);
            }
            return *this;
        }

        void push(const T& val) {
            std::unique_lock<std::mutex> lock(m);
            q.push(val);
        };

        std::optional<T> pop() {
            std::unique_lock<std::mutex> lock(m);
            if (q.empty()){
                return std::nullopt;
            }
            T val = q.front();
            q.pop();
            return val;
        };

        T front() {
            std::unique_lock<std::mutex> lock(m);
            return q.front();
        };

        T back() {
            std::unique_lock<std::mutex> lock(m);
            return q.back();
        };

        bool empty() {
            std::unique_lock<std::mutex> lock(m);
            return q.empty();
        };

        size_t size() {
            std::unique_lock<std::mutex> lock(m);
            return q.size();
        };

    private:
        std::queue<T> q;
        mutable std::mutex m;
};
