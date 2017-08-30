#if 0
#include "StepperController.h"

using namespace std;

StepperController::StepperController() {
    
}

StepperController::~StepperController() {

}

void StepperController::create(const uint8_t id, const uint8_t pins[4], const uint8_t stepsPerRev, const uint8_t speed) {
    Stepper *stepper = new Stepper(stepsPerRev, pins[0], pins[1], pins[2], pins[3]);
    stepper->setSpeed(speed);

    steppers.insert(make_pair(id, stepper));
}

void StepperController::step(const uint8_t id, const int64_t steps) {
    steppers[id]->step(steps);
}
#endif