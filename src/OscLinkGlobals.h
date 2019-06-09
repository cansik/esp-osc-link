//
// Created by Florian Bruggisser on 2019-06-09.
//

#ifndef ESP_OSC_LINK_OSCLINKGLOBALS_H
#define ESP_OSC_LINK_OSCLINKGLOBALS_H

// status
#define STATUS_LED_PIN 2

// serial
#define BAUD_RATE 9600

// network
#define DEVICE_NAME String("esp-osc-link")

#define SSID_NAME "Der Geraet"
#define SSID_PASSWORD ""

#define OTA_PASSWORD "osclink"
#define OTA_PORT 8266

// twisted
#define OSC_OUT_PORT 9000
#define OSC_IN_PORT 8000

// buffer
#define MAX_BUFFER_SIZE 32

#endif //ESP_OSC_LINK_OSCLINKGLOBALS_H
