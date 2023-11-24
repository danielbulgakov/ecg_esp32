#ifndef CIRCULAR_QUEUE_HH
#define CIRCULAR_QUEUE_HH

#include <vector>
#include <atomic>

#include "helpers/config.hh"

namespace circular {
template <typename T>
class queue {
   public:
    queue(size_t initSize = Config::Package::QUEUE_INIT_CAPACITY);

    void push(const T& value);
    void pop();
    T& front();
    T& back();
    bool empty() const;

   private:
    std::vector<T> data;
    std::atomic<size_t> head;
    std::atomic<size_t> tail;
    size_t count;

    void resize();
};
}  // namespace circular

#endif  // CIRCULAR_QUEUE_HH
