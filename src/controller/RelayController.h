#ifndef RELAYCONTROLLER_H
#define RELAYCONTROLLER_H

#include "common.h"

#define RELAY_DEBUG false

using namespace std;

enum Relay_t {
    RELAY_0 = 22,
    RELAY_1 = 24,
    RELAY_2 = 26,
    RELAY_3 = 28,
    RELAY_4 = 30,
    RELAY_5 = 32,
    RELAY_6 = 34,
    RELAY_7 = 36,

    RELAY_8  = 38,
    RELAY_9  = 40,
    RELAY_10 = 42,
    RELAY_11 = 44,
    RELAY_12 = 46,
    RELAY_13 = 48,
    RELAY_14 = 50,
    RELAY_15 = 52,

    RELAY_16 = 21,
    RELAY_17 = 23,
    RELAY_18 = 25,
    RELAY_19 = 27,
    RELAY_20 = 31,
    RELAY_21 = 33,
    RELAY_22 = 35,
    RELAY_23 = 37
};

class RelayController {
public:
	RelayController();
	~RelayController();

	void reset();	
    void setHigh(Relay_t relay);
    void setLow(Relay_t relay);
};

#endif