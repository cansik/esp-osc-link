//
// Created by Florian Bruggisser on 2019-05-12.
//

#ifndef ESP_OSC2SERIAL_UPLINK_SERIALUPLINK_H
#define ESP_OSC2SERIAL_UPLINK_SERIALUPLINK_H


#include <controller/TimeBasedController.h>
#include <controller/network/OscController.h>
#include <model/RingBuffer.h>

#define UPLINK_FRAMERATE 60

class SerialUplink : public TimeBasedController {
private:
    OscController *osc;
    RingBuffer<OSCMessage> *messageBuffer;

    String inputString;

    void processConfiguration();

    void processData();

public:
    explicit SerialUplink(OscController *osc, RingBuffer<OSCMessage> *messageBuffer);

    void timedLoop() override;
};


#endif //ESP_OSC2SERIAL_UPLINK_SERIALUPLINK_H
