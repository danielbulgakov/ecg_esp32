#ifndef SPI_FLASH_HH
#define SPI_FLASH_HH

#include "FS.h"
#include "SD.h"
#include "SPI.h"

#include <helpers/config.hh>

class SPIFlash {
   public:
    void begin();
    void writeData(uint8_t* data0, uint8_t* data1, size_t length);
    void readData(uint8_t* buffer1, uint8_t* buffer2, size_t length);

   private:
    static SPIFlash* instance;
    static uint64_t number;
    static uint64_t number_to_read;

   public:
    static SPIFlash* inst();

    uint64_t getNumFiles() { return number - number_to_read; }

    bool isEmpty() { return number_to_read - number; }
};

/** Define static member of class */
SPIFlash* SPIFlash::instance = nullptr;

#endif  // SPI_FLASH_HH