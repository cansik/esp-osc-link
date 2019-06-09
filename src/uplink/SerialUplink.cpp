//
// Created by Florian Bruggisser on 2019-05-12.
//

#include "SerialUplink.h"

SerialUplink::SerialUplink(OscController *osc, MutableBuffer<OSCMessage> *buffer) :
        TimeBasedController(UPLINK_FRAMERATE, FRAMES_PER_SECOND) {
    this->buffer = buffer;
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

    // received accelerometer data
    if (inputString.startsWith("")) {

        // parse data
        //sscanf(inputString.c_str(), "DAT:ACC;%d;%d;%d", &x, &y, &z);

        // todo: implement protocol
    }
}

void SerialUplink::publishMessage() {
    OSCMessage msg("");

    osc->sendMessage(msg);

    msg.empty();
}
