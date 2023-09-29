#ifndef DATA_PACKAGE
#define DATA_PACKAGE

#include <stdint.h>
#include <vector>

#include "package_format.hh"

typedef uint16_t DataType;

class DataPackage {
 private:
  PackageFormat format;
  uint16_t size;
  uint16_t number;
  std::vector<DataType> payload;

 public:
  DataPackage(uint16_t number = 0) : number(number) {}

  void addData(DataType value) {
    if (!isPayloadFull()) {
      payload.push_back(value);
    }
  }

  bool isPayloadFull() const { return payload.size() >= size; }

  uint16_t* getData() { return payload.data(); }

  uint16_t getSize() {
    size = (uint16_t)payload.size();
    return size;
  }

  uint16_t getNumber() { return number; }

  void clear() {
    payload.clear();
    size = 0;
    number = 0;
  }

  void setNumber(uint16_t number) { this->number = number; }
};

class SingletonePackage : public DataPackage {
 private:
  static SingletonePackage* instance;

  SingletonePackage() : DataPackage() {}

  SingletonePackage(const SingletonePackage&) = delete;
  SingletonePackage& operator=(const SingletonePackage&) = delete;

 public:
  static SingletonePackage* getInstance() {
    if (!instance) {
      instance = new SingletonePackage();
    }
    return instance;
  }
};

// Define static members of classes

SingletonePackage* SingletonePackage::instance = nullptr;

#endif  // DATA_PACKAGE
