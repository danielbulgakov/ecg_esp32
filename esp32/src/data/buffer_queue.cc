#include "data/buffer_queue.hh"

#ifdef MUTEX
#include <mutex>

/**
 * Using mutex to avoid racing on
 * push and pop methods of queue
 */
std::mutex mtx;
#endif  // MUTEX

void
BufferQueue::insert(uint16_t element) {
    currentPack.push_back(element);

    if (currentPack.size() >= maxSize) {
        log_i("BufferQueue :: Added pack");
#ifdef MUTEX
        mtx.lock();
#endif  // MUTEX
        bufferQ.push(currentPack);
#ifdef MUTEX
        mtx.unlock();
#endif  // MUTEX
        currentPack.clear();
    }
}

PackageType
BufferQueue::extract() {
    PackageType p;
    if (!bufferQ.empty()) {
        p = bufferQ.front();
#ifdef MUTEX
        mtx.lock();
#endif  // MUTEX
        bufferQ.pop();
#ifdef MUTEX
        mtx.unlock();
#endif  // MUTEX
        return p;
    }
    return p;
}
