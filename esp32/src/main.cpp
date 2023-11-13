#include <Arduino.h>
#include <Thread.h>

#include <ble/ble_service_handler.hh>      // BLE
#include <ble/custom_server_callbacks.hh>  // BLE CALLBACKS
#include <data/package.hh>                 // PACKAGE
#include <helpers/config.hh>               // GLOBAL CONFIG
#include <spi/spi_flash.hh>                // SPI

BLEServiceHandler* ble;
SPIFlash* flash;
Package pack;

/** Create threads to handle 
 * Data saving and saveing routines
*/
Thread sensorsThread = Thread();
Thread saveThread = Thread();
constexpr uint16_t sensorDelay = 1000;
constexpr uint16_t saveDelay = 1000;

void
saveData() {
    /** For debug purposes we firstly use
     * to init save data as random values
    */
    for (int i = 0; i < Config::Package::MAX_DATA_SIZE; i++) {
        pack.insert(random(0, 4096), 0);
        pack.insert(random(0, 4096), 1);
    }
}

void
saveData() {
    while (!flash->isEmpty()) {
        uint8_t *buff1, *buff2;
        uint16_t size;
        flash->readData(buff1, buff2, size);

        // Update BLE data characteristics
        ble->setDataPack0(reinterpret_cast<uint16_t*>(buff1), size);
        ble->setDataPack1(reinterpret_cast<uint16_t*>(buff2), size);
        ble->setPackageSize(size);

        // Notify about data update
        ble->broadcastIndicate();

        delay(saveDelay);
    }

    while (!pack.isEmpty() && !CustomServerCallbacks::isConnected()) {
        flash->writeData(reinterpret_cast<uint8_t*>(pack.extract(0).data()),
                         reinterpret_cast<uint8_t*>(pack.extract(1).data()),
                         pack.getSize() * 2);
        delay(saveDelay);
    }

    while (!pack.isEmpty() && CustomServerCallbacks::isConnected()) {
        // Update BLE data characteristics
        ble->setDataPack0(pack.extract(0).data(), pack.getSize());
        ble->setDataPack1(pack.extract(1).data(), pack.getSize());
        ble->setPackageSize(pack.getSize());

        // Notify about data update
        ble->broadcastIndicate();
        delay(saveDelay);
    }
}

void
setup() {
    /** BLE setup */
    ble = BLEServiceHandler::inst();
    ble->setup();

    /** Package setup */
    pack = Package();

    /** SPI flash setup */
    flash = SPIFlash::inst();
    flash->begin();

    /** Init threads */
    sensorsThread.onRun(saveData);
    sensorsThread.setInterval(sensorDelay);

    saveThread.onRun(saveData);
    saveThread.setInterval(saveDelay);
}

void
loop() {
    /** Run sensor thread */
    if (sensorsThread.shouldRun()) {
        sensorsThread.run();
    }
    /** Run save thread */
    if (saveThread.shouldRun()) {
        saveThread.run();
    }
}