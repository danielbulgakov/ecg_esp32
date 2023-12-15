#ifndef PACKAGE_HH
#define PACKAGE_HH

#include <data/buffer_queue.hh>
#include <helpers/config.hh>

class Package {
   private:
    std::vector<BufferQueue> payloads;
    uint64_t maxSize;

   public:
    explicit Package(uint64_t size = Config::Package::MAX_DATA_SIZE);

    void insert(uint16_t element, uint8_t channel);

    PackageType extract(uint8_t channel);

    uint64_t getSize() { return maxSize; }

    bool isEmpty() { return payloads[0].isEmpty() || payloads[1].isEmpty(); }
};

#endif  // PACKAGE_HH