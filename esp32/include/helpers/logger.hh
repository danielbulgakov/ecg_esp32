#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

class Logger {
public:
    enum class Urgency {
        INFO,
        WARNING,
        ERROR
    };

    static void init() {
        Serial.begin(115200);
    }

    static void log(const char* label, Urgency urgency, const char* message) {
#ifdef DEBUG
        Serial.print("[");
        Serial.print(label);
        Serial.print("] [");
        switch (urgency) {
            case Urgency::INFO:
                Serial.print("INFO");
                break;
            case Urgency::WARNING:
                Serial.print("WARNING");
                break;
            case Urgency::ERROR:
                Serial.print("ERROR");
                break;
        }
        Serial.print("] ");
        Serial.println(message);
#endif
    }

    static void log(const String& label, Urgency urgency, const String& message) {
        log(label.c_str(), urgency, message.c_str());
    }
};

#endif  // LOGGER_H
