#include "data/circular_queue.hh"

#include "data/circular_queue.hh"

namespace circular {

template <typename T>
queue<T>::queue(size_t initSize) : data(initSize), head(0), tail(0), count(0) {}

template <typename T>
void
queue<T>::push(const T& value) {
    if (count == data.size()) {
#ifdef RESIZEABLE
        resize();
#else
        log_e("Queue :: Got its max capacity");
#endif  // RESIZEABLE
    }
    auto current_tail  = tail.load(std::memory_order_relaxed);
    data[current_tail] = value;
    tail.store((current_tail + 1) % data.size(), std::memory_order_release);
    ++count;
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
    --count;
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
queue<T>::resize() {
    std::vector<T> new_data(data.size() * 2);
    for (size_t i = 0; i < count; ++i) {
        new_data[i] = data[(head + i) % data.size()];
    }
    data = std::move(new_data);
    head.store(0, std::memory_order_release);
    tail.store(count, std::memory_order_release);
}

}  // namespace circular