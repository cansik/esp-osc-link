//
// Created by Florian Bruggisser on 19.11.18.
//

#ifndef THREE_SCAN_STATUSLED_H
#define THREE_SCAN_STATUSLED_H


#include <cstdint>

class StatusLed {
private:
    static uint8_t ledPin;

    static bool blinking;

    static uint8_t brightness;

public:
    static void setup(uint8_t ledPin = 2);

    static void loop();

    static void turnOn();

    static void turnOff();
};


#endif //THREE_SCAN_STATUSLED_H
