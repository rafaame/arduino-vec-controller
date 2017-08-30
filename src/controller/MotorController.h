#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "common.h"

#define MOTOR_DEBUG false

using namespace std;

class Motor {
public:
	uint8_t pins[2];
	uint8_t speedPin;
	uint8_t speed;

	Motor(const uint8_t pins[2], const uint8_t speedPin) {
		this->pins[0] = pins[0];
		this->pins[1] = pins[1];
		this->speedPin = speedPin;
		speed = 255;
	};
};

class MotorController {
private:
	std::map<uint8_t, Motor *> motors;

public:
	MotorController();
	~MotorController();
	
    void create(const uint8_t id, const uint8_t pins[2], const uint8_t speedPin, const uint8_t speed);
    void turn(const uint8_t id, const uint64_t duration, bool direction);
};

#endif