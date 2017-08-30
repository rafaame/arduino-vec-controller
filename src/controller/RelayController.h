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

    RELAY_8  = 23,
    RELAY_9  = 25,
    RELAY_10 = 27,
    RELAY_11 = 29,
    RELAY_12 = 31,
    RELAY_13 = 33,
    RELAY_14 = 35,
    RELAY_15 = 37,

    RELAY_16 = 39,
    RELAY_17 = 41,
    RELAY_18 = 43,
    RELAY_19 = 45,
    RELAY_20 = 47,
    RELAY_21 = 49,
    RELAY_22 = 51
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