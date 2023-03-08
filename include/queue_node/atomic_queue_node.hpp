#include <memory>
#include <atomic>

template <class T>
class atomic_queue_node {
public:
    atomic_queue_node(T const& data) : val(std::make_shared<T>(data)), next(nullptr) {};

    // Copy constructor
    atomic_queue_node(const atomic_queue_node& other) : val(other.val), next(other.next) {};

    // Move constructor
    atomic_queue_node(atomic_queue_node&& other) : val(std::move(other.val)), next(std::move(other.next)) {
        other.val = nullptr;
        other.next = nullptr;
    };

    // Copy assignment operator
    atomic_queue_node& operator=(const atomic_queue_node& other) {
        if (this != &other) {
            val = other.val;
            next = other.next;
        }
        return *this;
    };

    // Move assignment operator
    atomic_queue_node& operator=(atomic_queue_node&& other) {
        if (this != &other) {
            val = std::move(other.val);
            next = std::move(other.next);
            other.val = nullptr;
            other.next = nullptr;
        }
        return *this;
    };

    // Destructor
    ~atomic_queue_node() {
        val.reset();
    };

    std::atomic<atomic_queue_node*> next; // Pointer to the next node
    std::shared_ptr<T> val;
};
