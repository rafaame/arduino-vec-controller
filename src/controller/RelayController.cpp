#include "RelayController.h"

using namespace std;

RelayController::RelayController() {
    pinMode(RELAY_0, OUTPUT);
    pinMode(RELAY_1, OUTPUT);
    pinMode(RELAY_2, OUTPUT);
    pinMode(RELAY_3, OUTPUT);
    pinMode(RELAY_4, OUTPUT);
    pinMode(RELAY_5, OUTPUT);
    pinMode(RELAY_6, OUTPUT);
    pinMode(RELAY_7, OUTPUT);

    pinMode(RELAY_8, OUTPUT);
    pinMode(RELAY_9, OUTPUT);
    pinMode(RELAY_10, OUTPUT);
    pinMode(RELAY_11, OUTPUT);
    pinMode(RELAY_12, OUTPUT);
    pinMode(RELAY_13, OUTPUT);
    pinMode(RELAY_14, OUTPUT);
    pinMode(RELAY_15, OUTPUT);
    
    pinMode(RELAY_16, OUTPUT);
    pinMode(RELAY_17, OUTPUT);
    pinMode(RELAY_18, OUTPUT);
    pinMode(RELAY_19, OUTPUT);
    pinMode(RELAY_20, OUTPUT);
    pinMode(RELAY_21, OUTPUT);
    pinMode(RELAY_22, OUTPUT);

    reset();
}

RelayController::~RelayController() {

}

void RelayController::reset() {
    setLow(RELAY_0);
    setLow(RELAY_1);
    setLow(RELAY_2);
    setLow(RELAY_3);
    setLow(RELAY_4);
    setLow(RELAY_5);
    setLow(RELAY_6);
    setLow(RELAY_7);
    
    setLow(RELAY_8);
    setLow(RELAY_9);
    setLow(RELAY_10);
    setLow(RELAY_11);
    setLow(RELAY_12);
    setLow(RELAY_13);
    setLow(RELAY_14);
    setLow(RELAY_15);

    setLow(RELAY_16);
    setLow(RELAY_17);
    setLow(RELAY_18);
    setLow(RELAY_19);
    setLow(RELAY_20);
    setLow(RELAY_21);
    setLow(RELAY_22);
}

void RelayController::setHigh(Relay_t relay) {
    digitalWrite(relay, HIGH);
}

void RelayController::setLow(Relay_t relay) {
    digitalWrite(relay, LOW);
}