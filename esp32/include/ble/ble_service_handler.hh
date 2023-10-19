#ifndef BLE_SERVICE_HANDLER_H
#define BLE_SERVICE_HANDLER_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include <helpers/config.hh>

class CustomCallbacks : public BLEServerCallbacks {
   private:
    static bool deviceConnected;

    void onConnect(BLEServer* pServer) {
        log_i("BLE :: Device connected");
        deviceConnected = true;
    }

    void onDisconnect(BLEServer* pServer) {
        log_i("BLE :: disconnected");
        deviceConnected = false;
        reconnect(pServer);
    }

    void reconnect(BLEServer* pServer) {
        // reconnect endlessly
        while (!deviceConnected) {
            pServer->getAdvertising()->start();
            delay(100);
        }
    }

   public:
    static bool isConnected() { return deviceConnected; }
};

class BLEServiceHandler {
   private:
    static BLEServiceHandler* instance;
    BLEServer* pServer;
    BLECharacteristic* pDataCharacteristic;
    BLECharacteristic* pDataCharacteristic1;
    BLECharacteristic* pSizeCharacteristic;
    BLECharacteristic* pPackageCharacteristic;

    BLEServiceHandler() {
        pServer = nullptr;
        pDataCharacteristic = nullptr;
        pDataCharacteristic1 = nullptr;
        pSizeCharacteristic = nullptr;
        pPackageCharacteristic = nullptr;
    }

   public:
    static BLEServiceHandler* inst() {
        if (instance == nullptr) {
            instance = new BLEServiceHandler();
        }
        return instance;
    }

    void setup() {
        BLEDevice::init("ESP32");
        pServer = BLEDevice::createServer();
        BLEService* pService =
            pServer->createService(Config::BLE::SERVICE_UUID);

        BLEDescriptor dataDescriptor(BLEUUID((uint16_t)0x2902));
        BLEDescriptor dataDescriptor1(BLEUUID((uint16_t)0x2902));
        BLEDescriptor sizeDescriptor(BLEUUID((uint16_t)0x2902));
        BLEDescriptor packDescriptor(BLEUUID((uint16_t)0x2902));

        pDataCharacteristic = pService->createCharacteristic(
            Config::BLE::DATA_OUT1_UUID,
            BLECharacteristic::PROPERTY_READ |
                BLECharacteristic::PROPERTY_WRITE |
                BLECharacteristic::PROPERTY_INDICATE);

        pDataCharacteristic1 = pService->createCharacteristic(
            Config::BLE::DATA_OUT2_UUID,
            BLECharacteristic::PROPERTY_READ |
                BLECharacteristic::PROPERTY_WRITE |
                BLECharacteristic::PROPERTY_INDICATE);

        pSizeCharacteristic = pService->createCharacteristic(
            Config::BLE::SIZE_UUID, BLECharacteristic::PROPERTY_READ |
                                        BLECharacteristic::PROPERTY_WRITE |
                                        BLECharacteristic::PROPERTY_INDICATE);

        pPackageCharacteristic = pService->createCharacteristic(
            Config::BLE::PACKAGE_UUID,
            BLECharacteristic::PROPERTY_READ |
                BLECharacteristic::PROPERTY_WRITE |
                BLECharacteristic::PROPERTY_INDICATE);

        pDataCharacteristic->addDescriptor(&dataDescriptor);
        pDataCharacteristic1->addDescriptor(&dataDescriptor1);
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
        log_i("BLE :: Values indicated");
        pDataCharacteristic->indicate();
        pDataCharacteristic1->indicate();
        pSizeCharacteristic->indicate();
        pPackageCharacteristic->indicate();
    }

    void setSize(uint16_t size) { pSizeCharacteristic->setValue(size); }

    void setNumber(uint16_t number) {
        pPackageCharacteristic->setValue(number);
    }

    void setData(uint16_t* data, uint16_t size) {
        if (data == nullptr)
            return;
        pDataCharacteristic->setValue(reinterpret_cast<uint8_t*>(data),
                                      size * sizeof(uint16_t));
    }

    void setData1(uint16_t* data, uint16_t size) {
        if (data == nullptr)
            return;
        pDataCharacteristic1->setValue(reinterpret_cast<uint8_t*>(data),
                                       size * sizeof(uint16_t));
    }
};

// Define static members of classes

BLEServiceHandler* BLEServiceHandler::instance = nullptr;

#endif  // BLE_SERVICE_HANDLER_H