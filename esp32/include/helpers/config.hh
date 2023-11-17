#ifndef CONFIG_HH
#define CONFIG_HH

#define DEBUG
#include <Arduino.h>

namespace Config {
    namespace BLE {
        static const char* SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
        static const char* DATA_OUT1_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8";
        static const char* DATA_OUT2_UUID = "beb5483e-e29b-41d4-a716-446655440000";
        static const char* SIZE_UUID = "aeb5483e-36e1-4688-b7f5-ea07361b26a9";
        static const char* PACKAGE_UUID = "afb5483e-36e1-4688-b7f5-ea07361b26aa";
    }  // namespace BLE

    namespace Package {
        static const int MAX_DATA_SIZE = 20;
    }  // namespace Package

    namespace SPI {
        static const int MOSI = 6;
        static const int MISO = 5;
        static const int SCLK = 4;
        static const int CS = 7;
    }  // namespace SPI
}  // namespace Config

#endif  // CONFIG_HH
