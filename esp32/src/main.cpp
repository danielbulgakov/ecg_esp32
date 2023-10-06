#include <Arduino.h>
#include "ble/ble_service_handler.hh"
#include "message/data_package.hh"
#include "spi/spi_flash.hh"

BLEServiceHandler bleHandler;
SPIFlash* flash;
SingletonPackage* pack;
uint16_t num = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("G");
    bleHandler.setup();
    pack = SingletonPackage::getInstance();
    flash = SPIFlash::getInstance();
    Serial.println("GG");
    flash->begin();
    Serial.println("A");
}

void loop() {

    // If package is full we clear previous package and update
    // counter of package
    if (pack->getSize() >= 20) {
        flash->writeData(pack->getNumber(),
                         reinterpret_cast<uint8_t*>(pack->getData()),
                         pack->getSize());
        pack->clear();
        pack->setNumber(num++);
    }
    Serial.println("B");

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
