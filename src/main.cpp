#include "common.h"
#include "vec-common/Packet.h"
#include "controller/I2cController.h"
#include "controller/StateController.h"
#include "controller/RelayController.h"
#include "controller/MotorController.h"
#include "controller/StepperController.h"
#include "handler/ModuleHandler.h"
#include "module/ComfortModule.h"

I2cController i2cController;
StateController stateController;
RelayController relayController;
MotorController motorController;
//StepperController stepperController;
ModuleHandler moduleHandler;
volatile uint8_t *buffer;
volatile bool hasCommand = false;
void setup() {
    Serial.begin(115200);
    Serial.println("Starting arduino-vec-controller...");

    moduleHandler.registerModule("comfort", new ComfortModule(&relayController, &motorController, nullptr));

    buffer = new uint8_t[RequestPacket::getByteArraySize()];
    i2cController.init(0x0B);
    i2cController.setOnReceiveCallback([](int size) -> void {
        for (uint32_t i = 0; i < size; i++) {
        	buffer[i] = i2cController.read();
        }

        hasCommand = true;
    });
}

void loop() {
    if (hasCommand) {
        RequestPacket *packet = RequestPacket::fromByteArray((uint8_t *) buffer);
        moduleHandler.dispatch(packet);

        hasCommand = false;
        delete packet;
    }
}
