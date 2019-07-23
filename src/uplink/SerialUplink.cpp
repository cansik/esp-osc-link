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
    if (inputString.startsWith("LC")) {
        processConfiguration();
    }

    // received osc data
    if (inputString.startsWith("LD")) {
        processData();
    }
}

void SerialUplink::processConfiguration() {
    char command[10];

    // parse cmd
    sscanf(inputString.c_str(), "LC %s", &command);
    Serial.println(inputString);

    if (String(command).startsWith("DEBUG")) {
        Serial.printf("Messages in Buffer: %d\n", messageBuffer->length());
    }
}

void SerialUplink::processData() {
    char oscAddress[MAX_OSC_ADDRESS_SIZE];
    int paramCount = 0;
    int params[3];

    auto input = inputString.c_str();

    // read header
    auto res = sscanf(input, "LD %s %d", &oscAddress, &paramCount);

    // check if parsing worked
    if (res <= 0) {
        return;
    }

    // read parameters
    switch (paramCount) {
        case 1:
            sscanf(input, "LD %*s %*d %d", &params[0]);
            break;

        case 2:
            sscanf(input, "LD %*s %*d %d %d", &params[0], &params[1]);
            break;

        case 3:
            sscanf(input, "LD %*s %*d %d %d %d", &params[0], &params[1], &params[2]);
            break;
    }

    // fill params to message
    OSCMessage msg(oscAddress);
    for (int i = 0; i < paramCount; i++) {
        msg.add(params[i]);
    }

    // send osc message
    osc->sendMessage(msg);
    msg.empty();
}