#include "Module.h"

Module::Module(RelayController *relayController, MotorController *motorController, StepperController *stepperController) {
	this->relayController = relayController;
	this->motorController = motorController;
	this->stepperController = stepperController;
}

Module::~Module() {
	
}

void Module::registerAction(string name, function<bool(RequestPacket *)> action) {
	actions.insert(make_pair(name, action));
}

bool Module::dispatch(RequestPacket *packet) {
	if (actions.find(packet->action) == actions.end()) {
		return false;
	}

	return actions[packet->action](packet);
}