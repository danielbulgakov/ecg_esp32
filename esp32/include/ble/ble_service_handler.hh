#ifndef BLE_SERVICE_HANDLER_H
#define BLE_SERVICE_HANDLER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "ble_config.hh"

class BLEServiceHandler {

public:
    BLEServiceHandler() {}

void setup() {
    BLEDevice::init("ESP32");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);

    pDataCharacteristic = pService->createCharacteristic(
                                         DATA_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );

    pSizeCharacteristic = pService->createCharacteristic(
                                         SIZE_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );

    pPackageCharacteristic = pService->createCharacteristic(
                                         PACKAGE_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    BLEDevice::startAdvertising();
}

void bcastNotify() {
    pDataCharacteristic->notify();
    pSizeCharacteristic->notify();
    pPackageCharacteristic->notify();
}

void setSize(uint16_t size) {
    pSizeCharacteristic->setValue(size);
}

void setNumber(uint16_t number) {
    pPackageCharacteristic->setValue(number);
}

void setData(uint16_t* data) {
    if (data == nullptr) return;
    pDataCharacteristic->setValue((uint8_t*)data, MAX_DATA_SIZE * sizeof(uint16_t));
}

private:
    BLECharacteristic *pDataCharacteristic;
    BLECharacteristic *pSizeCharacteristic;
    BLECharacteristic *pPackageCharacteristic;

};

#endif // BLE_SERVICE_HANDLER_H