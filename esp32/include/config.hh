#ifndef CONFIG_H
#define CONFIG_H

namespace Config {
    namespace BLE {
        const char* SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
        const char* DATA_OUT1_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8";
        const char* DATA_OUT2_UUID = "beb5483e-e29b-41d4-a716-446655440000";
        const char* SIZE_UUID = "aeb5483e-36e1-4688-b7f5-ea07361b26a9";
        const char* PACKAGE_UUID = "afb5483e-36e1-4688-b7f5-ea07361b26aa";
    }  // namespace BLE

    namespace Package {
        const int MAX_DATA_SIZE = 20;
        const unsigned char HEADER = 0;
        const unsigned char TRAILER = 0;
        const unsigned char DELIMETER = ',';
    }  // namespace Package

    namespace SPI {
        const int MOSI = 6;
        const int MISO = 5;
        const int SCLK = 4;
        const int CS = 7;
    }  // namespace SPI
}  // namespace Config

#endif  // CONFIG_H
