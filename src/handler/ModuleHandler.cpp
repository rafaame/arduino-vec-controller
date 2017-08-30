#include "ModuleHandler.h"
#include "module/Module.h"

using namespace std;

ModuleHandler::ModuleHandler() {
	
}

ModuleHandler::~ModuleHandler() {
	
}

void ModuleHandler::registerModule(string name, Module *module) {
	modules.insert(make_pair(name, module));
}

bool ModuleHandler::dispatch(RequestPacket *packet) {
	Serial.print("Dispatching (module = ");
	Serial.print(packet->module.c_str());
	Serial.print("; action = ");
	Serial.print(packet->action.c_str());
	Serial.println(")");

	if (modules.find(packet->module) == modules.end()) {
		return false;
	}

	return modules[packet->module]->dispatch(packet);
}