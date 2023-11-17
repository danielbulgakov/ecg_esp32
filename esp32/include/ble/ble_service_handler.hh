#ifndef BLE_SERVICE_HANDLER_HH
#define BLE_SERVICE_HANDLER_HH

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include <helpers/config.hh>

class BLEServiceHandler {
   private:
    BLEServer* pServer;
    BLECharacteristic* pDataCharacteristic;
    BLECharacteristic* pDataCharacteristic1;
    BLECharacteristic* pSizeCharacteristic;
    BLECharacteristic* pPackageCharacteristic;
    uint64_t globalPackageNumber;
    void setPackageNumber(uint16_t number);

   public:
    void setup(uint64_t start_index = 0);
    void broadcastIndicate();
    void broadcastNotify();
    void setPackageSize(uint16_t size);
    void setDataPack0(uint16_t* data, uint16_t size);
    void setDataPack1(uint16_t* data, uint16_t size);

   private:
    static BLEServiceHandler* instance;
    explicit BLEServiceHandler();

   public:
    static BLEServiceHandler* inst();
};

#endif  // BLE_SERVICE_HANDLER_HH