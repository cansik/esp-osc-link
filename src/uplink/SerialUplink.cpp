//
// Created by Florian Bruggisser on 2019-05-12.
//

#include "SerialUplink.h"

SerialUplink::SerialUplink(OscController *osc, RingBuffer<OSCMessage> *messageBuffer) :
        TimeBasedController(UPLINK_FRAMERATE, FRAMES_PER_SECOND) {
    this->messageBuffer = messageBuffer;
    this->osc = osc;

    // set timeout for string reading
    Serial.setTimeout(20);
}

void SerialUplink::timedLoop() {
    TimeBasedController::timedLoop();

    // read command
    inputString = Serial.readStringUntil('\n');

    // if no input -> opt out
    if (inputString.length() == 0) {
        return;
    }

    // display osc messages
    if(inputString.startsWith("OSC:CFG")) {
        processConfiguration();
    }

    // received osc data
    if (inputString.startsWith("OSC:DAT")) {
        processData();
    }
}

void SerialUplink::processConfiguration() {
    char command[10];

    // parse cmd
    sscanf(inputString.c_str(), "OSC:CFG %s", &command);
    Serial.println(inputString);

    if(String(command).startsWith("DEBUG")) {
        Serial.printf("Messages in Buffer: %d\n", messageBuffer->length());
    }
}

void SerialUplink::processData() {

}