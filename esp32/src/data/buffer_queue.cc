#include "data/buffer_queue.hh"

void
BufferQueue::insert(uint16_t element) {
    currentPack.push_back(element);

    if (currentPack.size() >= maxSize) {
        bufferQ.push(currentPack);
        currentPack.clear();
    }
}

PackageType
BufferQueue::extract() {
    PackageType p;
    if (!bufferQ.empty()) {
        p = bufferQ.front();
        bufferQ.pop();
        return p;
    }
    return p;
}
