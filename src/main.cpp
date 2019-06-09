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
    messageBuffer.add(&msg);
}