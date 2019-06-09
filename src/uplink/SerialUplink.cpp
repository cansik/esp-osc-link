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
    if(inputString.startsWith("OSC:DBG")) {
        Serial.printf("Messages: %d\n", messageBuffer->length());
    }

    // received osc data
    if (inputString.startsWith("OSC:ACC")) {

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
