#include <Arduino.h>

#include "ble/ble_service_handler.hh"
#include "message/data_package.hh"

BLEServiceHandler bleHandler;
SingletonePackage* pack;
uint16_t num = 0;

void setup() {
  bleHandler.setup();
  pack = SingletonePackage::getInstance();
}

void loop() {
  pack->setNumber(num++);
  for (int i = 0; i < MAX_DATA_SIZE; i++) {
    pack->addData(random(0, 4096));
  }

  bleHandler.setData(pack->getData());
  bleHandler.setNumber(pack->getNumber());
  bleHandler.setSize(pack->getSize());

  bleHandler.bcastNotify();
  pack->clear();

  delay(1000);
}