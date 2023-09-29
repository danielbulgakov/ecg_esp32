#ifndef DATA_PACKAGE_H
#define DATA_PACKAGE_H

#include <stdint.h>
#include <vector>
#include "message/package_format.hh"

typedef uint16_t DataType;

class DataPackage {
   private:
    PackageFormat format;
    uint16_t maxSize;
    uint16_t number;
    std::vector<DataType> payload;

   public:
    explicit DataPackage(uint16_t number = 0, uint16_t maxSize = 20)
        : number(number), maxSize(maxSize) {}

    void addData(DataType value) {
        if (!isPayloadFull()) {
            payload.push_back(value);
        }
    }

    bool isPayloadFull() const { return payload.size() >= maxSize; }

    uint16_t* getData() { return payload.data(); }

    uint16_t getSize() { return (uint16_t)payload.size(); }

    uint16_t getNumber() { return number; }

    void clear() {
        payload.clear();
        number = 0;
    }

    void setNumber(uint16_t number) { this->number = number; }
};

class SingletonPackage : public DataPackage {
   private:
    static SingletonPackage* instance;

    SingletonPackage() : DataPackage() {}

    SingletonPackage(const SingletonPackage&) = delete;
    SingletonPackage& operator=(const SingletonPackage&) = delete;

   public:
    static SingletonPackage* getInstance() {
        if (!instance) {
            instance = new SingletonPackage();
        }
        return instance;
    }
};

// Define static members of classes

SingletonPackage* SingletonPackage::instance = nullptr;

#endif  // DATA_PACKAGE_H
