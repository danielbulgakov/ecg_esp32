#include <Arduino.h>

#include "ble/ble_service_handler.hh"
#include "message/data_package.hh"
#include "spi/spi_flash.hh"

#include <helpers/config.hh>

BLEServiceHandler* bleHandler;
SPIFlash* flash;
SingletonPackage* pack;

uint16_t num = 0;

void setup() {
    bleHandler = BLEServiceHandler::inst();
    bleHandler->setup();
    pack = SingletonPackage::inst();
    flash = SPIFlash::inst();
    flash->begin();
}

void loop() {
    // If package is full we clear previous package and update
    // counter of package
    if (pack->isPayloadFull()) {
        flash->writeData(pack->getNumber(),
                         reinterpret_cast<uint8_t*>(pack->getData(0)),
                         reinterpret_cast<uint8_t*>(pack->getData(1)),
                         pack->getSize() * 2 /* 2x for cast from 16 to 8 */);
        pack->clear();
        pack->setNumber(num++);  // Set package number for next packet
    }

    // For testing we use data auto-generative method
    for (int i = 0; i < Config::Package::MAX_DATA_SIZE; i++) {
        pack->addData(random(0, 4096), random(0, 4096));
    }

    // Update BLE data characteristics
    bleHandler->setData(pack->getData(0), pack->getSize());
    bleHandler->setData1(pack->getData(1), pack->getSize());
    bleHandler->setNumber(pack->getNumber());
    bleHandler->setSize(pack->getSize());

    // Notify about data update
    bleHandler->bcastIndicate();

    delay(1000);
}
