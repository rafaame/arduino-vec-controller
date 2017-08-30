#include "MotorController.h"

using namespace std;

MotorController::MotorController() {
    
}

MotorController::~MotorController() {

}

void MotorController::create(const uint8_t id, const uint8_t pins[2], const uint8_t speedPin, const uint8_t speed) {
    Motor *motor = new Motor(pins, speedPin);
    motor->speed = speed;

    motors.insert(make_pair(id, motor));
}

void MotorController::turn(const uint8_t id, const uint64_t duration, bool direction) {
    analogWrite(motors[id]->speedPin, motors[id]->speed);
    digitalWrite(motors[id]->pins[0], direction ? HIGH : LOW);
    digitalWrite(motors[id]->pins[1], direction ? LOW : HIGH);
    
    delay(duration);
    analogWrite(motors[id]->speedPin, 0);
}