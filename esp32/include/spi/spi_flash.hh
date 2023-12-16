#ifndef SPI_FLASH_H
#define SPI_FLASH_H

#include "FS.h"
#include "SD.h"
#include "SPI.h"

#include <helpers/config.hh>

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
        // pins got from config file
        SPI.begin(Config::SPI::SCLK, Config::SPI::MISO, Config::SPI::MOSI,
                  Config::SPI::CS);
        if (!SD.begin(Config::SPI::CS, SPI)) {
            log_e("SPI :: An error has occurred while mounting SD");
        }
        if (SD.cardType() == CARD_NONE) {
            log_e("No SD card attached");
            return;
        }
        log_i("SPI :: SD mounted successfully");
    }

    void writeData(int number, uint8_t* data1, uint8_t* data2, size_t length) {
        String filename = "/" + String(number);
        File file = SD.open(filename, FILE_WRITE);
        if (!file) {
            log_e("SPI :: Failed to open file for writing");
            return;
        }

        size_t written = file.write(data1, length);
        written += file.write((uint8_t*)"\n", 1);
        written += file.write(data2, length);

        if (written != 2 * length + 1) {
            log_e("SPI :: Failed to write data to file");
        }

        file.close();

        log_i("SPI :: Wrote package to file");
    }

    void readData(int number, uint8_t* buffer1, uint8_t* buffer2,
                  size_t length) {
        String filename = "/" + String(number);
        File file = SD.open(filename, FILE_READ);
        if (!file) {
            log_e("SPI :: Failed to open file for reading");
            return;
        }

        size_t read = file.read(buffer1, length);
        file.read();  // Skip newline
        read += file.read(buffer2, length);

        if (read != 2 * length) {
            log_e("SPI :: Failed to read data from file");
        }

        file.close();

        log_i("SPI :: Wrote package to file");
    }
};

// Define static members of classes

SPIFlash* SPIFlash::instance = nullptr;

#endif  // SPI_FLASH_H