#include "ComfortModule.h"

using namespace std;
using namespace std::placeholders;

ComfortModule::ComfortModule(RelayController *relayController, MotorController *motorController, StepperController *stepperController) : Module(relayController, motorController, stepperController) {
	motorController->create(
		VENTILATOR_POSITION_MOTOR_ID,
		VENTILATOR_POSITION_MOTOR_PINS,
		VENTILATOR_POSITION_MOTOR_SPEED_PIN,
		VENTILATOR_POSITION_MOTOR_SPEED);

	ventilatorPosition = VENTILATOR_POSITION_MIRROR;
	ventilatorSpeed = 0;
	airConditioning = false;
	airRecirculation = false;
	hazardLights = false;
	doorLocks = false;
	defrost = false;

	isCharging = false;
	chargingTimer = 0;

	registerAction("set-ventilator-position", bind(&ComfortModule::setVentilatorPosition, this, _1));
	registerAction("set-ventilator-speed", bind(&ComfortModule::setVentilatorSpeed, this, _1));
	registerAction("set-air-conditioning", bind(&ComfortModule::setAirConditioning, this, _1));
	registerAction("set-air-recirculation", bind(&ComfortModule::setAirRecirculation, this, _1));
	registerAction("set-hazard-lights", bind(&ComfortModule::setHazardLights, this, _1));
	registerAction("toggle-door-locks", bind(&ComfortModule::toggleDoorLocks, this, _1));
	registerAction("toggle-defrost", bind(&ComfortModule::toggleDefrost, this, _1));
	registerAction("open-trunk", bind(&ComfortModule::openTrunk, this, _1));
}

/*void ComfortModule::processData(DataPacket *dataPacket) {
	Serial.println("processData");
	Serial.println(dataPacket->isAlternatorOn);

	if (! dataPacket->isAlternatorOn) {
		isCharging = false;
		chargingTimer = 0;
		relayController->setLow(RELAY_CHARGE_BATTERY);

		Serial.println("Disabling");

		return;
	}

	if (! isCharging && dataPacket->isAlternatorOn) {
		if (! chargingTimer) {
			chargingTimer = millis() + 10000;

			return;
		}

		if (millis() > chargingTimer) {
			isCharging = true;
			chargingTimer = 0;
			relayController->setHigh(RELAY_CHARGE_BATTERY);

			Serial.println("Enabling");
		}
	}
}*/

void ComfortModule::changeVentilatorPosition(int8_t positionChange) {
	motorController->turn(VENTILATOR_POSITION_MOTOR_ID, VENTILATOR_POSITION_CHANGE_DURATION, false);
}

bool ComfortModule::setVentilatorPosition(RequestPacket *packet) {
	if (packet->dataType != PACKET_DATA_TYPE_INTEGER) {
		return false;
	}

	VentilatorPosition_t position = (VentilatorPosition_t) atoi(packet->data.c_str());
	if (position < 0 || position > 5) {
		return false;
	}

	ventilatorPosition = position;
	changeVentilatorPosition(position);

	return true;
}

bool ComfortModule::setVentilatorSpeed(RequestPacket *packet) {
	if (packet->dataType != PACKET_DATA_TYPE_INTEGER) {
		return false;
	}

	uint8_t speed = (uint8_t) atoi(packet->data.c_str());
	relayController->setLow(RELAY_VENTILATOR_SPEED_1);
	relayController->setLow(RELAY_VENTILATOR_SPEED_2);
	relayController->setLow(RELAY_VENTILATOR_SPEED_3);
	relayController->setLow(RELAY_VENTILATOR_SPEED_4);
	ventilatorSpeed = speed;

	if (! speed) {
		return true;
	}

	switch (speed) {
		case 1:
			relayController->setHigh(RELAY_VENTILATOR_SPEED_1);
			break;
		case 2:
			relayController->setHigh(RELAY_VENTILATOR_SPEED_2);
			break;
		case 3:
			relayController->setHigh(RELAY_VENTILATOR_SPEED_3);
			break;
		case 4:
			relayController->setHigh(RELAY_VENTILATOR_SPEED_4);
			break;
		default:
			return false;
	}

	return true;
}

bool ComfortModule::setAirConditioning(RequestPacket *packet) {
	if (packet->dataType != PACKET_DATA_TYPE_BOOL) {
		return false;
	}

	bool on = (bool) atoi(packet->data.c_str());
	airConditioning = on;

	if (on) {
		relayController->setHigh(RELAY_AIR_CONDITIONING_1);
		relayController->setHigh(RELAY_AIR_CONDITIONING_2);
	} else {
		relayController->setLow(RELAY_AIR_CONDITIONING_1);
		relayController->setLow(RELAY_AIR_CONDITIONING_2);
	}

	return true;
}

bool ComfortModule::setAirRecirculation(RequestPacket *packet) {
	if (packet->dataType != PACKET_DATA_TYPE_BOOL) {
		return false;
	}

	bool on = (bool) atoi(packet->data.c_str());
	airRecirculation = on;

	if (on) {
		relayController->setHigh(RELAY_AIR_RECIRCULATION_1);
		relayController->setHigh(RELAY_AIR_RECIRCULATION_2);
	} else {
		relayController->setLow(RELAY_AIR_RECIRCULATION_1);
		relayController->setLow(RELAY_AIR_RECIRCULATION_2);
	}

	return true;
}

bool ComfortModule::setHazardLights(RequestPacket *packet) {
	if (packet->dataType != PACKET_DATA_TYPE_BOOL) {
		return false;
	}

	bool on = (bool) atoi(packet->data.c_str());
	hazardLights = on;

	if (on) {
		relayController->setHigh(RELAY_HAZARD_LIGHTS_1);
		relayController->setHigh(RELAY_HAZARD_LIGHTS_2);
	} else {
		relayController->setLow(RELAY_HAZARD_LIGHTS_1);
		relayController->setLow(RELAY_HAZARD_LIGHTS_2);
	}

	return true;
}

bool ComfortModule::toggleDoorLocks(RequestPacket *packet) {
	doorLocks = ! doorLocks;
	relayController->setLow(RELAY_DOOR_LOCKS);
	delay(100);

	relayController->setHigh(RELAY_DOOR_LOCKS);
	delay(BUTTON_PRESS_TIME);
	relayController->setLow(RELAY_DOOR_LOCKS);

	return true;
}

bool ComfortModule::toggleDefrost(RequestPacket *packet) {
	defrost = ! defrost;
	relayController->setLow(RELAY_DEFROST);
	delay(100);

	relayController->setHigh(RELAY_DEFROST);
	delay(BUTTON_PRESS_TIME);
	relayController->setLow(RELAY_DEFROST);

	return true;
}

bool ComfortModule::openTrunk(RequestPacket *packet) {
	relayController->setLow(RELAY_TRUNK);
	delay(100);

	relayController->setHigh(RELAY_TRUNK);
	delay(BUTTON_PRESS_TIME);
	relayController->setLow(RELAY_TRUNK);

	return true;
}