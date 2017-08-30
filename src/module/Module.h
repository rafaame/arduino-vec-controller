#ifndef MODULE_H
#define MODULE_H

#include "common.h"
#include "vec-common/Packet.h"
#include "controller/RelayController.h"
#include "controller/MotorController.h"
#include "controller/StepperController.h"

using namespace std;

class Module {
protected:
	RelayController *relayController;
	MotorController *motorController;
	StepperController *stepperController;
	std::map<string, function<bool(RequestPacket *)>> actions;

public:
	Module(RelayController *relayController, MotorController *motorController, StepperController *stepperController);
	~Module();

	void registerAction(string name, function<bool(RequestPacket *)> action);
	virtual bool dispatch(RequestPacket *packet);
};

#endif