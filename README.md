# ESP OSC Link
ESP8266 Open Sound Control (OSC) Uplink for Microcontrollers.

## Setup
The idea of this software is to provide a simple uplink for non-network microcontrollers, to be capable of sending and receiving OSC data.

![Setup](images/setup.svg)

## Functions
- Connect to WIFI (with credentials)
- Store credentials in EEPROM
- Send OSC Data (`INTEGER`)
- Receive and buffer OSC data
- Poll buffered data
- Interrupt on data received


## Protocol


### Data
Send OSC message from MicroController to OSC Link:

```java
Header Address ParamCount Param0 Param1\n
LD /test 2 25 52\n
```