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
#ifdef MUTEX
        mtx.lock();
#endif  // MUTEX
        bufferQ.push(currentPack);
#ifdef MUTEX
        mtx.unlock();
#endif  // MUTEX
        currentPack.clear();
        log_i("BufferQueue :: Added pack");
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
        log_i("BufferQueue :: Extracted pack");
        return p;
    }
    return p;
}
