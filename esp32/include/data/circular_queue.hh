#ifndef CIRCULAR_QUEUE_HH
#define CIRCULAR_QUEUE_HH

#include "helpers/config.hh"

namespace circular {
template <typename T>
class queue {
   public:
    queue() {};

    void push(const T& value) {
    }

    void pop() {

    }

    T& front() {
        static T dummy;
        return dummy;
    }

    T& back() {
        static T dummy;
        return dummy;
    }

    bool empty() {
        return false;
    }

    bool isFull() {
        return false;
    }
};
}  // namespace circular

#endif  // CIRCULAR_QUEUE_HH
