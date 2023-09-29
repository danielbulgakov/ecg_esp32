#ifndef BLE_SERVICE_HANDLER_H
#define BLE_SERVICE_HANDLER_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include <ble/ble_config.hh>

class MyServerCallbacks : public BLEServerCallbacks {
    bool deviceConnected;

    void onConnect(BLEServer* pServer) { deviceConnected = true; }

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
        reconnect(pServer);
    }

    void reconnect(BLEServer* pServer) {
        while (!deviceConnected) {
            pServer->getAdvertising()->start();
            delay(100);
        }
    }
};

class BLEServiceHandler {
   public:
    BLEServiceHandler() {
        pServer = nullptr;
        pDataCharacteristic = nullptr;
        pSizeCharacteristic = nullptr;
        pPackageCharacteristic = nullptr;
    }

    void setup() {
        BLEDevice::init("ESP32");
        pServer = BLEDevice::createServer();
        BLEService* pService = pServer->createService(SERVICE_UUID);

        BLEDescriptor dataDescriptor(BLEUUID((uint16_t)0x2902));
        BLEDescriptor sizeDescriptor(BLEUUID((uint16_t)0x2902));
        BLEDescriptor packDescriptor(BLEUUID((uint16_t)0x2902));

        pDataCharacteristic = pService->createCharacteristic(
            DATA_UUID, BLECharacteristic::PROPERTY_READ |
                           BLECharacteristic::PROPERTY_WRITE |
                           BLECharacteristic::PROPERTY_INDICATE);

        pSizeCharacteristic = pService->createCharacteristic(
            SIZE_UUID, BLECharacteristic::PROPERTY_READ |
                           BLECharacteristic::PROPERTY_WRITE |
                           BLECharacteristic::PROPERTY_INDICATE);

        pPackageCharacteristic = pService->createCharacteristic(
            PACKAGE_UUID, BLECharacteristic::PROPERTY_READ |
                              BLECharacteristic::PROPERTY_WRITE |
                              BLECharacteristic::PROPERTY_INDICATE);

        pDataCharacteristic->addDescriptor(&dataDescriptor);
        pSizeCharacteristic->addDescriptor(&sizeDescriptor);
        pPackageCharacteristic->addDescriptor(&packDescriptor);

        pService->start();

        // Could be added later
        // BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
        // pAdvertising->addServiceUUID(SERVICE_UUID);
        // pAdvertising->setScanResponse(true);
        // pAdvertising->setMinPreferred(0x06);
        BLEDevice::startAdvertising();
    }

    void bcastIndicate() {
        pDataCharacteristic->indicate();
        pSizeCharacteristic->indicate();
        pPackageCharacteristic->indicate();
    }

    void setSize(uint16_t size) { pSizeCharacteristic->setValue(size); }

    void setNumber(uint16_t number) {
        pPackageCharacteristic->setValue(number);
    }

    void setData(uint16_t* data) {
        if (data == nullptr)
            return;
        pDataCharacteristic->setValue(reinterpret_cast<uint8_t*>(data),
                                      MAX_DATA_SIZE * sizeof(uint16_t));
    }

   private:
    BLEServer* pServer;
    BLECharacteristic* pDataCharacteristic;
    BLECharacteristic* pSizeCharacteristic;
    BLECharacteristic* pPackageCharacteristic;
};

#endif  // BLE_SERVICE_HANDLER_H