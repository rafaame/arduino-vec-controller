class StepperController;
#if 0
#ifndef STEPPERCONTROLLER_H
#define STEPPERCONTROLLER_H

#include "common.h"

#define STEPPER_DEBUG false

using namespace std;

class StepperController {
private:
	std::map<uint8_t, Stepper *> steppers;

public:
	StepperController();
	~StepperController();
	
    void create(const uint8_t id, const uint8_t pins[4], const uint8_t stepsPerRev, const uint8_t speed);
    void step(const uint8_t id, const int64_t steps);
};

#endif
#endif