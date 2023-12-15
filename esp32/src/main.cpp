#include <Arduino.h>
#include <Thread.h>

#include <ble/ble_service_handler.hh>      // BLE
#include <ble/custom_server_callbacks.hh>  // BLE CALLBACKS
#include <data/package.hh>                 // PACKAGE
#include <helpers/config.hh>               // GLOBAL CONFIG
#include <spi/spi_flash.hh>                // SPI

#ifndef NO_BLE
BLEServiceHandler* ble;
#endif // NO_BLE
#ifndef NO_SPI
SPIFlash* flash;
#endif // NO_SPI
Package pack;

/** Create threads to handle 
 * Data saving and saveing routines
*/
Thread sensorsThread = Thread();
Thread saveThread    = Thread();

constexpr uint16_t sensorDelay = 1000;
constexpr uint16_t saveDelay   = 500;

void
getData() {
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
    /** For debug purposes we firstly use
     * to simply pop data
    */
    pack.extract(0);
    pack.extract(1);
}

// void
// saveData() {
//     bool isFlashEmpty = true;
// #ifndef NO_SPI
//     isFlashEmpty = flash->isEmpty();
// #endif  // NO_SPI
//     while (!isFlashEmpty && CustomServerCallbacks::isConnected()) {
//         uint8_t *buff1, *buff2;
//         uint16_t size;
// #ifndef NO_SPI
//         flash->readData(buff1, buff2, size);
// #endif  // NO_SPI

//         // Update BLE data characteristics
//         ble->setDataPack0(reinterpret_cast<uint16_t*>(buff1), size);
//         ble->setDataPack1(reinterpret_cast<uint16_t*>(buff2), size);
//         ble->setPackageSize(size);

//         // Notify about data update
//         ble->broadcastIndicate();
//     }

//     while (!pack.isEmpty() && !CustomServerCallbacks::isConnected()) {
// #ifndef NO_SPI
//         flash->writeData(reinterpret_cast<uint8_t*>(pack.extract(0).data()),
//                          reinterpret_cast<uint8_t*>(pack.extract(1).data()),
//                          pack.getSize() * 2);
// #endif  // NO_SPI
//     }

//     while (!pack.isEmpty() && CustomServerCallbacks::isConnected()) {
//         // Update BLE data characteristics
//         ble->setDataPack0(pack.extract(0).data(), pack.getSize());
//         ble->setDataPack1(pack.extract(1).data(), pack.getSize());
//         ble->setPackageSize(pack.getSize());

//         // Notify about data update
//         ble->broadcastIndicate();
//     }
// }

void
setup() {
    /** BLE setup */
#ifndef NO_BLE
    ble = BLEServiceHandler::inst();
    ble->setup();
#endif // NO_BLE

    /** Package setup */
    // pack = Package();

#ifndef NO_SPI
    /** SPI flash setup */
    flash = SPIFlash::inst();
    flash->begin();
#endif  // NO_SPI

    /** Init threads */
    sensorsThread.onRun(getData);
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