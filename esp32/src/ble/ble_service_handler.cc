#include <ble/ble_service_handler.hh>

void
BLEServiceHandler::setup(uint64_t start_index) {
    globalPackageNumber = start_index;
    BLEDevice::init("ESP32");
    pServer = BLEDevice::createServer();
    BLEService* pService = pServer->createService(Config::BLE::SERVICE_UUID);

    BLEDescriptor dataDescriptor(BLEUUID((uint16_t)0x2902));
    BLEDescriptor dataDescriptor1(BLEUUID((uint16_t)0x2902));
    BLEDescriptor sizeDescriptor(BLEUUID((uint16_t)0x2902));
    BLEDescriptor packDescriptor(BLEUUID((uint16_t)0x2902));

    pDataCharacteristic = pService->createCharacteristic(
        Config::BLE::DATA_OUT1_UUID, BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_INDICATE);

    pDataCharacteristic1 = pService->createCharacteristic(
        Config::BLE::DATA_OUT2_UUID, BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_INDICATE);

    pSizeCharacteristic = pService->createCharacteristic(
        Config::BLE::SIZE_UUID, BLECharacteristic::PROPERTY_READ |
                                    BLECharacteristic::PROPERTY_WRITE |
                                    BLECharacteristic::PROPERTY_INDICATE);

    pPackageCharacteristic = pService->createCharacteristic(
        Config::BLE::PACKAGE_UUID, BLECharacteristic::PROPERTY_READ |
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

void
BLEServiceHandler::broadcastIndicate() {
    log_i("BLE :: Values indicated");
    setPackageNumber(globalPackageNumber++);
    pDataCharacteristic->indicate();
    pDataCharacteristic1->indicate();
    pSizeCharacteristic->indicate();
    pPackageCharacteristic->indicate();
}

void
BLEServiceHandler::broadcastNotify() {
    log_i("BLE :: Values notifyied");
    setPackageNumber(globalPackageNumber++);
    pDataCharacteristic->notify();
    pDataCharacteristic1->notify();
    pSizeCharacteristic->notify();
    pPackageCharacteristic->notify();
}

void
BLEServiceHandler::setPackageSize(uint16_t size) {
    pSizeCharacteristic->setValue(size);
}

void
BLEServiceHandler::setPackageNumber(uint16_t number) {
    pPackageCharacteristic->setValue(number);
}

void
BLEServiceHandler::setDataPack0(uint16_t* data, uint16_t size) {
    if (data == nullptr)
        return;
    pDataCharacteristic->setValue(reinterpret_cast<uint8_t*>(data),
                                  size * sizeof(uint16_t));
}

void
BLEServiceHandler::setDataPack1(uint16_t* data, uint16_t size) {
    if (data == nullptr)
        return;
    pDataCharacteristic1->setValue(reinterpret_cast<uint8_t*>(data),
                                   size * sizeof(uint16_t));
}

BLEServiceHandler::BLEServiceHandler() {
    pServer = nullptr;
    pDataCharacteristic = nullptr;
    pDataCharacteristic1 = nullptr;
    pSizeCharacteristic = nullptr;
    pPackageCharacteristic = nullptr;
}

BLEServiceHandler*
BLEServiceHandler::inst() {
    if (instance == nullptr) {
        instance = new BLEServiceHandler();
    }
    return instance;
}
