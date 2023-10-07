#ifndef SPI_FLASH_H
#define SPI_FLASH_H

#include "FS.h"
#include "SPI.h"
#include "SPIFFS.h"

#include <helpers/config.hh>
#include <helpers/logger.hh>

class SPIFlash {
   private:
    static SPIFlash* instance;

   public:
    static SPIFlash* inst() {
        if (!instance) {
            instance = new SPIFlash();
        }
        return instance;
    }

    void begin() {
        // pins got from spi_config file
        SPI.begin(Config::SPI::SCLK, Config::SPI::MISO, Config::SPI::MOSI,
                  Config::SPI::CS);
        if (!SPIFFS.begin(true)) {
            Logger::log("SPI", Logger::Urgency::ERROR,
                        "An error has occurred while mounting SPIFFS");
        }
        Logger::log("SPI", Logger::Urgency::INFO,
                    "SPIFFS mounted successfully");
    }

    void writeData(int number, uint8_t* data, size_t length) {
        String filename = "/" + String(number);
        File file = SPIFFS.open(filename, FILE_WRITE);
        if (!file) {
            Logger::log("SPI", Logger::Urgency::ERROR,
                        "Failed to open file for writing");
            return;
        }

        size_t written = file.write(data, length);
        if (written != length) {
            Logger::log("SPI", Logger::Urgency::ERROR,
                        "Failed to write data to file");
        }

        file.close();
    }

    void readData(int number, uint8_t* buffer, size_t length) {
        String filename = "/" + String(number);
        File file = SPIFFS.open(filename, FILE_READ);
        if (!file) {
            Logger::log("SPI", Logger::Urgency::ERROR,
                        "Failed to open file for reading");
            return;
        }

        size_t read = file.read(buffer, length);
        if (read != length) {
            Logger::log("SPI", Logger::Urgency::ERROR,
                        "Failed to read data from file");
        }

        file.close();
    }
};

// Define static members of classes

SPIFlash* SPIFlash::instance = nullptr;

#endif  // SPI_FLASH_H