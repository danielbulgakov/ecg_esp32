#ifndef DATA_PACKAGE
#define DATA_PACKAGE

#include <stdint.h>
#include <vector>
#include "package_format.h"

typedef uint16_t DataType;

class DataPackage {
private:
    PackageFormat format;
    uint16_t size;
    uint16_t number;
    std::vector<DataType> payload;
public:
    DataPackage(uint16_t size = 0, uint16_t number = 0) :
        size(size), number(number) {}

    void addData(DataType value) {
        if (!isPayloadFull()) {
            payload.push_back(value);
        }
    }

    bool isPayloadFull() const {
        return payload.size() >= size;
    }

    std::vector<uint8_t> serialize() {
        std::vector<uint8_t> package;

        // Add header to package
        package.push_back(format.HEADER);
        
        // Add size to package
        package.push_back((size >> 8) & 0xFF);
        package.push_back(size & 0xFF);

        // Add number to package
        package.push_back((number >> 8) & 0xFF);
        package.push_back(number & 0xFF);

        // Add items to package
        for (DataType item : payload) {
            package.push_back((item >> 8) & 0xFF);
            package.push_back(item & 0xFF);
        }

        // Add trailer to package
        package.push_back(format.TRAILER);

        return package;
    }

    void deserialize(const std::vector<uint8_t>& package) {
        payload.clear();
        uint16_t i, start_index = 5;
        
        size = package[1] << 8 | package[2];
        number = package[3] << 8 | package[4];

        for (i = start_index; i < start_index + size * 2; i += 2) {
            uint16_t value = package[i] << 8 | package[i + 1];
            payload.push_back(value);
        }
    }

    void clear() {
        payload.clear();
        size = 0;
        number = 0;
    }

    void setSize(uint16_t size) {this->size = size;}

    void setNumber(uint16_t number) {this->number = number;} 
};

class SingletonePackage : public DataPackage {
private:
    static SingletonePackage* instance;

    SingletonePackage() : DataPackage() {}

    SingletonePackage(const SingletonePackage &) = delete;
    SingletonePackage & operator = (const SingletonePackage &) = delete;

public:

    static SingletonePackage* getInstance() {
        if (!instance) {
            instance = new SingletonePackage();
        }
        return instance;
    }

};

#endif // DATA_PACKAGE
