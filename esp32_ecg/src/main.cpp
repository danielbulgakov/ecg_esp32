#include <Arduino.h>

#include <helpers/config.hh>

// sudo usermod -a -G dialout daniel

#define RANDOM

int sensorValueRedFirst = 0;
int sensorValueRedSecond = 0;

uint32_t last_ms = 0;
int flag = 0;

#ifdef RANDOM
uint16_t randint = 0;
#endif // RANDOM

void setup() {
    Serial1.begin(115200);
    last_ms = millis();
}

void loop() {
    #ifdef RANDOM
        Serial1.println((randint++));
    #elif defined(REAL)
    if ((millis() - last_ms) >= Config::Td) {
        // Gather data every 2 ms
        sensorValueRedFirst = analogRead(Config::SensorPins::AnalogRedFirst);
        sensorValueRedSecond = analogRead(Config::SensorPins::AnalogRedSecond);
        // Write data to second esp32
        Serial1.print(sensorValueRedFirst);
        Serial1.print(sensorValueRedSecond);
        Serial1.println();

        flag = 0;

        last_ms = millis();
        flag++;
    }
    #endif
}
