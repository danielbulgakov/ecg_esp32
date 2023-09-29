#ifndef SPI_FLASH_H
#define SPI_FLASH_H

#include "FS.h"
#include "SPI.h"
#include "SPIFFS.h"

class SPIFlash {
   public:
    SPIFlash(int sclk, int miso, int mosi, int cs)
        : sclk(sclk), miso(miso), mosi(mosi), cs(cs) {}

    void begin() {
        SPI.begin(sclk, miso, mosi, cs);
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

   private:
    int sclk, miso, mosi, cs;
};

#endif  // SPI_FLASH_H