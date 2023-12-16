#ifndef DATA_PACKAGE_H
#define DATA_PACKAGE_H

#include <stdint.h>
#include <vector>

#include <helpers/config.hh>

class DataPackage {
   private:
    uint16_t number;
    std::vector<std::vector<uint16_t>> payloads;  // Vector of payloads

   public:
    explicit DataPackage(uint16_t number = 0) : number(number) {
        payloads.resize(2);  // Initialize 2 vectors for payloads
    }

    void addData(uint16_t value, uint16_t value1) {
        if (!isPayloadFull()) {
            payloads[0].push_back(value);
            payloads[1].push_back(value1);
        }
    }

    bool isPayloadFull() const {
        return payloads[0].size() >= Config::Package::MAX_DATA_SIZE;
    }

    uint16_t* getData(int index) { return payloads[index].data(); }

    uint16_t getSize() { return (uint16_t)payloads[0].size(); }

    uint16_t getNumber() { return number; }

    void clear() {
        payloads[0].clear();
        payloads[1].clear();
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
    static SingletonPackage* inst() {
        if (!instance) {
            instance = new SingletonPackage();
        }
        return instance;
    }
};

// Define static members of classes

SingletonPackage* SingletonPackage::instance = nullptr;

#endif  // DATA_PACKAGE_H
