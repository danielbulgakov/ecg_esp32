#include <Arduino.h>

#include <helpers/config.hh>

int sensorValueRedFirst = 0;
int sensorValueRedSecond = 0;

uint32_t last_ms = 0;
int flag = 0;

void setup() {
    Serial1.begin(115200);
    last_ms = millis();
}

void loop() {
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
}
