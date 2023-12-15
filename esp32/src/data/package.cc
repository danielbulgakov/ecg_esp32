#include "data/package.hh"

constexpr uint8_t channelsNum = 2;

Package::Package(uint64_t size) {
    this->maxSize = size;
    for (uint64_t i = 0; i < channelsNum; i++) {
        payloads.push_back(BufferQueue());
    }
}

void
Package::insert(uint16_t element, uint8_t channel) {
    if (channel >= channelsNum)
        return;
    payloads[channel].insert(element);
}

PackageType
Package::extract(uint8_t channel) {
    if (&payloads[channel] == nullptr)
        return PackageType();
    return payloads[channel].extract();
}
