#ifndef SPI_FLASH_H
#define SPI_FLASH_H

#include "FS.h"
#include "SPI.h"
#include "SPIFFS.h"

#include "spi/spi_config.hh"

class SPIFlash {
   private:
    static SPIFlash* instance;
    SPIFlash();
    SPIFlash(const SPIFlash&) = delete;
    SPIFlash& operator=(const SPIFlash&) = delete;

   public:
    static SPIFlash* getInstance() {
        if (!instance) {
            instance = new SPIFlash();
        }
        return instance;
    }

    void begin() {
        // pins got from spi_config file
        SPI.begin(SCLK, MISO, MOSI, CS);
        if (!SPIFFS.begin(true)) {
            Serial.println("An error has occurred while mounting SPIFFS");
        }
    }

    void writeData(int number, uint8_t* data, size_t length) {
        String filename = "/" + String(number);
        File file = SPIFFS.open(filename, FILE_WRITE);
        if (!file) {
            Serial.println("Failed to open file for writing");
            return;
        }

        size_t written = file.write(data, length);
        if (written != length) {
            Serial.println("Failed to write data to file");
        }

        file.close();
    }

    void readData(int number, uint8_t* buffer, size_t length) {
        String filename = "/" + String(number);
        File file = SPIFFS.open(filename, FILE_READ);
        if (!file) {
            Serial.println("Failed to open file for reading");
            return;
        }

        size_t read = file.read(buffer, length);
        if (read != length) {
            Serial.println("Failed to read data from file");
        }

        file.close();
    }


};

// Define static members of classes

SPIFlash* SPIFlash::instance = nullptr;

#endif  // SPI_FLASH_H