#include <spi/spi_flash.hh>

/** Define static member of class */
SPIFlash* SPIFlash::instance        = nullptr;
uint64_t  SPIFlash::number_to_read  = 0;
uint64_t  SPIFlash::number          = 0;

void
SPIFlash::begin() {
    number = 0;
    number_to_read = 0;
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

void
SPIFlash::writeData(uint8_t* data0, uint8_t* data1, size_t length) {
    String filename = "/" + String(number);
    File file = SD.open(filename, FILE_WRITE);
    if (!file) {
        log_e("SPI :: Failed to open file for writing");
        return;
    }

    size_t written = file.write(data0, length);
    written += file.write((uint8_t*)"\n", 1);
    written += file.write(data1, length);

    if (written != 2 * length + 1) {
        log_e("SPI :: Failed to write data to file");
    }

    file.close();

    log_i("SPI :: Wrote package to file");
    number++;
}

void
SPIFlash::readData(uint8_t* buffer1, uint8_t* buffer2, size_t length) {
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
    number_to_read++;
}

SPIFlash*
SPIFlash::inst() {
    if (!instance) {
        instance = new SPIFlash();
    }
    return instance;
}
