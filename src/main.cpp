#include <Arduino.h>
#include <Wire.h>
#include <inttypes.h>
#include <util/StatusLed.h>
#include <uplink/SerialUplink.h>
#include <model/RingBuffer.h>
#include "controller/BaseController.h"
#include "controller/network/NetworkController.h"
#include "controller/network/OTAController.h"
#include "controller/network/OscController.h"
#include "util/MathUtils.h"
#include "OscLinkGlobals.h"

// typedefs
typedef BaseController *BaseControllerPtr;

// controllers
auto network = NetworkController(DEVICE_NAME.c_str(), SSID_NAME, SSID_PASSWORD, WIFI_STA);
auto ota = OTAController(DEVICE_NAME.c_str(), OTA_PASSWORD, OTA_PORT);
auto osc = OscController(OSC_IN_PORT, OSC_OUT_PORT);

// data buffer
auto messageBuffer = RingBuffer<OSCMessage>(MAX_BUFFER_SIZE);

// uplink
auto uplink = SerialUplink(&osc, &messageBuffer);

// controller list
BaseControllerPtr controllers[] = {
        &network,
        &ota,
        &osc,
        &uplink
};

// methods
void handleOsc(OSCMessage &msg);

void setup() {
    Serial.begin(BAUD_RATE);
    StatusLed::setup(STATUS_LED_PIN);

    // setup controllers
    for (auto &controller : controllers) {
        controller->setup();
    }

    // setup handlers
    osc.onMessageReceived(handleOsc);

    // add osc mdns
    // todo: fix this again
    //network.addMDNSService("_osc", "_udp", OSC_IN_PORT);

    Serial.println("esp uplink is setup!");
}

void loop() {
    // loop controllers
    for (auto &controller : controllers) {
        controller->loop();
    }
}

void handleOsc(OSCMessage &msg) {
    char buffer [MAX_OSC_STRING_SIZE];
    char address[MAX_OSC_ADDRESS_SIZE];

    // read address
    msg.getAddress(address);

    // read parameters
    switch (msg.size()) {
        case 0:
            sprintf (buffer, "LD %s 0", address);
            break;

        case 1:
            sprintf (buffer, "LD %s %d %d", address, msg.size(), msg.getInt(0));
            break;

        case 2:
            sprintf (buffer, "LD %s %d %d %d", address, msg.size(), msg.getInt(0), msg.getInt(1));
            break;

        case 3:
            sprintf (buffer, "LD %s %d %d %d %d", address, msg.size(), msg.getInt(0), msg.getInt(1), msg.getInt(2));
            break;
    }

    Serial.printf("%s\n", buffer);
}