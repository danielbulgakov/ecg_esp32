#ifndef CONFIG_HH
#define CONFIG_HH

#include <Arduino.h>

#define DEBUG
#define NO_SPI

#define MUTEX

// #define CIRCLQUEUE
// #define RESIZEABLE

namespace Config {
namespace BLE {
constexpr const char* SERVICE_UUID   = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
constexpr const char* DATA_OUT1_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8";
constexpr const char* DATA_OUT2_UUID = "beb5483e-e29b-41d4-a716-446655440000";
constexpr const char* SIZE_UUID      = "aeb5483e-36e1-4688-b7f5-ea07361b26a9";
constexpr const char* PACKAGE_UUID   = "afb5483e-36e1-4688-b7f5-ea07361b26aa";
}  // namespace BLE

namespace Package {
constexpr int MAX_DATA_SIZE           = 20;
constexpr size_t QUEUE_INIT_CAPACITY = 10;
}  // namespace Package

namespace SPI {
constexpr int MOSI = 6;
constexpr int MISO = 5;
constexpr int SCLK = 4;
constexpr int CS   = 7;
}  // namespace SPI
}  // namespace Config

#endif  // CONFIG_HH
