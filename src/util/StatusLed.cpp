//
// Created by Florian Bruggisser on 19.11.18.
//

#include <Arduino.h>
#include "StatusLed.h"

uint8_t StatusLed::ledPin;

bool StatusLed::blinking;

uint8_t StatusLed::brightness;

void StatusLed::setup(uint8_t ledPin) {
    StatusLed::ledPin = ledPin;

    pinMode(StatusLed::ledPin, OUTPUT);
    turnOff();
}

void StatusLed::loop() {

}

void StatusLed::turnOn() {
    digitalWrite(ledPin, LOW);
}

void StatusLed::turnOff() {
    digitalWrite(ledPin, HIGH);
}