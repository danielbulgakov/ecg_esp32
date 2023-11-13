#ifndef BUFFER_QUEUE_HH
#define BUFFER_QUEUE_HH

#include <queue>
#include <vector>

#include <helpers/config.hh>

typedef std::vector<uint16_t> PackageType;

class BufferQueue {
   private:
    std::queue<PackageType> bufferQ;
    PackageType currentPack;
    uint16_t maxSize;

   public:
    explicit BufferQueue(uint16_t size = Config::Package::MAX_DATA_SIZE)
        : maxSize(size) {}

    void insert(uint16_t element);
    PackageType extract();

    bool isEmpty() { return bufferQ.empty(); }
};

#endif  // BUFFER_QUEUE_HH