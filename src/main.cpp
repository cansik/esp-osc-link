#include <Arduino.h>
#include <Wire.h>
#include <inttypes.h>
#include <util/StatusLed.h>
#include <uplink/SerialUplink.h>
#include "controller/BaseController.h"
#include "controller/network/NetworkController.h"
#include "controller/network/OTAController.h"
#include "controller/network/OscController.h"
#include "util/MathUtils.h"

// status
#define STATUS_LED_PIN 2

// serial
#define BAUD_RATE 9600

// network
#define DEVICE_NAME String("esp-osc-link")

#define SSID_NAME "Hello"
#define SSID_PASSWORD ""

#define OTA_PASSWORD "osclink"
#define OTA_PORT 8266

// twisted
#define OSC_OUT_PORT 9000
#define OSC_IN_PORT 8000

// typedefs
typedef BaseController *BaseControllerPtr;

// controllers
auto network = NetworkController(DEVICE_NAME.c_str(), SSID_NAME, SSID_PASSWORD, WIFI_STA);
auto ota = OTAController(DEVICE_NAME.c_str(), OTA_PASSWORD, OTA_PORT);
auto osc = OscController(OSC_IN_PORT, OSC_OUT_PORT);

// data buffer
auto buffer = MessageBuffer();

// uplink
auto uplink = SerialUplink(&osc, &buffer);

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
   // todo: add to buffer
}