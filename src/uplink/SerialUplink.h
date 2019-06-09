//
// Created by Florian Bruggisser on 2019-05-12.
//

#ifndef ESP_OSC2SERIAL_UPLINK_SERIALUPLINK_H
#define ESP_OSC2SERIAL_UPLINK_SERIALUPLINK_H


#include <controller/TimeBasedController.h>
#include <controller/network/OscController.h>
#include <model/MutableBuffer.h>

#define UPLINK_FRAMERATE 60

class SerialUplink : public TimeBasedController {
private:
    OscController *osc;
    MutableBuffer<OSCMessage> *buffer;

    String inputString;

public:
    explicit SerialUplink(OscController *osc, MutableBuffer<OSCMessage> *buffer);

    void timedLoop() override;

    void publishMessage();
};


#endif //ESP_OSC2SERIAL_UPLINK_SERIALUPLINK_H
