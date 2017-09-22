#ifndef COMFORTMODULE_H
#define COMFORTMODULE_H

#include "common.h"
#include "Module.h"

#define BUTTON_PRESS_TIME         500
#define RELAY_VENTILATOR_SPEED_1  RELAY_11
#define RELAY_VENTILATOR_SPEED_2  RELAY_10
#define RELAY_VENTILATOR_SPEED_3  RELAY_9
#define RELAY_VENTILATOR_SPEED_4  RELAY_8
#define RELAY_AIR_CONDITIONING_1  RELAY_4
#define RELAY_AIR_CONDITIONING_2  RELAY_5
#define RELAY_AIR_RECIRCULATION_1 RELAY_2
#define RELAY_AIR_RECIRCULATION_2 RELAY_3
#define RELAY_HAZARD_LIGHTS_1     RELAY_0
#define RELAY_HAZARD_LIGHTS_2     RELAY_1
#define RELAY_DOOR_LOCKS          RELAY_7
#define RELAY_DEFROST             RELAY_6
#define RELAY_TRUNK               RELAY_12

#define RELAY_CHARGE_BATTERY      RELAY_13

#define VENTILATOR_POSITION_MOTOR_ID             0
#define VENTILATOR_POSITION_MOTOR_PINS           (const uint8_t[]) {39, 41}
#define VENTILATOR_POSITION_MOTOR_SPEED_PIN		 7
#define VENTILATOR_POSITION_MOTOR_SPEED          255
#define VENTILATOR_POSITION_CHANGE_DURATION      150

using namespace std;

enum VentilatorPosition_t {
	VENTILATOR_POSITION_MIRROR          = 1,
	VENTILATOR_POSITION_FOOT            = 2,
	VENTILATOR_POSITION_PEOPLE          = 3,
	VENTILATOR_POSITION_PEOPLE_AND_FOOT = 4,
	VENTILATOR_POSITION_ALL             = 5
};

class ComfortModule : public Module {
private:
	VentilatorPosition_t ventilatorPosition;
	uint8_t ventilatorSpeed;
	bool airConditioning;
	bool airRecirculation;
	bool hazardLights;
	bool doorLocks;
	bool defrost;

	bool isCharging;
	uint64_t chargingTimer;

public:
	ComfortModule(RelayController *relayController, MotorController *motorController, StepperController *stepperController);
	
	void changeVentilatorPosition(int8_t positionChange);
	
	bool setVentilatorPosition(RequestPacket *packet);
	bool setVentilatorSpeed(RequestPacket *packet);
	bool setAirConditioning(RequestPacket *packet);
	bool setAirRecirculation(RequestPacket *packet);
	bool setHazardLights(RequestPacket *packet);
	bool toggleDoorLocks(RequestPacket *packet);
	bool toggleDefrost(RequestPacket *packet);
	bool openTrunk(RequestPacket *packet);
};

#endif