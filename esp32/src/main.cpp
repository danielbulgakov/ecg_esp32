#include <Arduino.h>
#include "ble/ble_service_handler.hh"
#include "message/data_package.hh"

BLEServiceHandler bleHandler;
SingletonPackage* pack;
uint16_t num = 0;

void setup() {
    bleHandler.setup();
    pack = SingletonPackage::getInstance();
}

void loop() {

    // If package is full we clear previous package and update
    // counter of package
    if (pack->getSize() >= 20) {
        pack->clear();
        pack->setNumber(num++);
    }

    // For testing we use data auto-generative method
    for (int i = 0; i < MAX_DATA_SIZE; i++) {
        pack->addData(random(0, 4096));
    }

    // Update BLE data characteristics
    bleHandler.setData(pack->getData());
    bleHandler.setNumber(pack->getNumber());
    bleHandler.setSize(pack->getSize());

    // Notify about data update
    bleHandler.bcastIndicate();

    delay(1000);
}
