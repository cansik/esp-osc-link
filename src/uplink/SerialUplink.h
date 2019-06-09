//
// Created by Florian Bruggisser on 2019-05-12.
//

#ifndef ESP_OSC2SERIAL_UPLINK_SERIALUPLINK_H
#define ESP_OSC2SERIAL_UPLINK_SERIALUPLINK_H


#include <controller/TimeBasedController.h>
#include <controller/network/OscController.h>
#include <model/MessageBuffer.h>

#define UPLINK_FRAMERATE 60

class SerialUplink : public TimeBasedController {
private:
    OscController *osc;
    MessageBuffer *buffer;

    String inputString;

public:
    explicit SerialUplink(OscController *osc, MessageBuffer *buffer);

    void timedLoop() override;

    void publishMessage();
};


#endif //ESP_OSC2SERIAL_UPLINK_SERIALUPLINK_H
