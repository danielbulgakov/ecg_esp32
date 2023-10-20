#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG

#include <cstdint>

namespace Config {
    namespace SensorPins {
        const uint8_t AnalogInPinPurple = 32;
        const uint8_t AnalogInPinAd623Black = 33;
        const uint8_t AnalogInPinBlue = 35;
        const uint8_t AnalogInPinRed = 34;
        const uint8_t AnalogRedFirst = 1;
        const uint8_t AnalogRedSecond = 2;
    }  // namespace SensorPins
    
    const uint8_t Td = 2;
}  // namespace Config

#endif  // CONFIG_H
