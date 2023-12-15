#ifndef CIRCULAR_QUEUE_HH
#define CIRCULAR_QUEUE_HH

#include <atomic>
#include <string>
#include <vector>

#include "helpers/config.hh"

namespace circular {
template <typename T>
class queue {
   public:
    queue(size_t initSize = Config::Package::QUEUE_INIT_CAPACITY);
    queue(const queue& other);
    queue& operator=(const queue& other);

    void push(const T& value);
    void pop();
    T& front();
    T& back();
    bool empty() const;

    void print() const;

   private:
    std::vector<T> data;
    std::atomic<size_t> head;
    std::atomic<size_t> tail;
    std::atomic<size_t> count;

    void resize();
};

// *** Template class functions implementaion ***

template <typename T>
queue<T>::queue(size_t initSize) {
    data.resize(initSize);
    tail  = std::atomic_int(0);
    head  = std::atomic_int(0);
    count = std::atomic_int(0);
}

template <typename T>
queue<T>::queue(const queue& other)
    : data(other.data),
      head(other.head.load()),
      tail(other.tail.load()),
      count(other.count.load()) {}

template <typename T>
queue<T>&
queue<T>::operator=(const queue& other) {
    if (this != &other) {
        data = other.data;
        head.store(other.head.load());
        tail.store(other.tail.load());
        count.store(other.count.load());
    }
    return *this;
}

template <typename T>
void
queue<T>::push(const T& value) {
    if (data.size() != 0 && count == data.size()) {
#ifdef RESIZEABLE
        resize();
#else
        log_e("Queue :: Got its max capacity");
#endif  // RESIZEABLE
    }
    auto current_tail  = tail.load(std::memory_order_relaxed);
    data[current_tail] = value;
    tail.store((current_tail + 1) % data.size(), std::memory_order_release);
    count.store(count.load() + 1);
}

template <typename T>
void
queue<T>::pop() {
    if (empty()) {
        log_e("Queue :: Empty");
    }
    auto current_head = head.load(std::memory_order_relaxed);
    T value           = data[current_head];
    head.store((current_head + 1) % data.size(), std::memory_order_release);
    count.store(count.load() - 1);
}

template <typename T>
T&
queue<T>::front() {
    if (empty()) {
        log_e("Queue :: Empty");
    }
    return data[head];
}

template <typename T>
T&
queue<T>::back() {
    if (empty()) {
        log_e("Queue :: Empty");
    }
    return data[(head + count - 1) % data.size()];
}

template <typename T>
bool
queue<T>::empty() const {
    return count == 0;
}

template <typename T>
void
queue<T>::print() const {
    std::string output = "Queue :: ";
    for (size_t i = 0; i < count.load(); ++i) {
        size_t index = (head.load() + i) % data.size();
        output += "[";
        for (size_t j = 0; j < data[index].size(); ++j) {
            output += std::to_string(data[index][j]);
            if (j < data[index].size() - 1) {
                output += ", ";
            }
        }
        output += "]";
        if (i < count.load() - 1) {
            output += ", ";
        }
    }
    log_i("%s", output.c_str());
}

template <typename T>
void
queue<T>::resize() {
    std::vector<T> new_data(data.size() * 2);
    for (size_t i = 0; i < count.load(); ++i) {
        new_data[i] = data[(head + i) % data.size()];
    }
    data = std::move(new_data);
    head.store(0, std::memory_order_release);
    tail.store(count, std::memory_order_release);
}
}  // namespace circular

#endif  // CIRCULAR_QUEUE_HH
