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
  BLEServiceHandler() {}

  void setup() {
    BLEDevice::init("ESP32");
    pServer = BLEDevice::createServer();
    BLEService* pService = pServer->createService(SERVICE_UUID);

    BLEDescriptor notifyDescriptor(BLEUUID((uint16_t)0x2907));

    pDataCharacteristic = pService->createCharacteristic(
        DATA_UUID, BLECharacteristic::PROPERTY_READ |
                       BLECharacteristic::PROPERTY_WRITE |
                       BLECharacteristic::PROPERTY_NOTIFY);

    pSizeCharacteristic = pService->createCharacteristic(
        SIZE_UUID, BLECharacteristic::PROPERTY_READ |
                       BLECharacteristic::PROPERTY_WRITE |
                       BLECharacteristic::PROPERTY_NOTIFY);

    pPackageCharacteristic = pService->createCharacteristic(
        PACKAGE_UUID, BLECharacteristic::PROPERTY_READ |
                          BLECharacteristic::PROPERTY_WRITE |
                          BLECharacteristic::PROPERTY_NOTIFY);

    pDataCharacteristic->addDescriptor(&notifyDescriptor);
    pSizeCharacteristic->addDescriptor(&notifyDescriptor);
    pPackageCharacteristic->addDescriptor(&notifyDescriptor);

    pService->start();

    // Could be added later
    // BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    // pAdvertising->addServiceUUID(SERVICE_UUID);
    // pAdvertising->setScanResponse(true);
    // pAdvertising->setMinPreferred(0x06);
    BLEDevice::startAdvertising();
  }

  void bcastNotify() {
    pDataCharacteristic->notify();
    pSizeCharacteristic->notify();
    pPackageCharacteristic->notify();
  }

  void setSize(uint16_t size) { pSizeCharacteristic->setValue(size); }

  void setNumber(uint16_t number) { pPackageCharacteristic->setValue(number); }

  void setData(uint16_t* data) {
    if (data == nullptr)
      return;
    pDataCharacteristic->setValue((uint8_t*)data,
                                  MAX_DATA_SIZE * sizeof(uint16_t));
  }

 private:
  BLEServer* pServer;
  BLECharacteristic* pDataCharacteristic;
  BLECharacteristic* pSizeCharacteristic;
  BLECharacteristic* pPackageCharacteristic;
};

#endif  // BLE_SERVICE_HANDLER_H