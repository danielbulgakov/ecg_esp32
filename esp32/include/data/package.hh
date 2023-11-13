#ifndef PACKAGE_HH
#define PACKAGE_HH

#include <data/buffer_queue.hh>
#include <helpers/config.hh>

class Package {
   private:
    std::vector<BufferQueue> payloads;
    uint64_t maxSize;

   public:
    explicit Package(uint64_t size = Config::Package::MAX_DATA_SIZE)
        : maxSize(size) {}

    void insert(uint16_t element, uint8_t id) { payloads[id].insert(element); };

    std::vector<uint16_t> extract(uint8_t id) {
        return payloads[id].extract();
    };

    uint64_t getSize() { return maxSize; }

    bool isEmpty() { return payloads[0].isEmpty() || payloads[1].isEmpty(); }
};

#endif  // PACKAGE_HH