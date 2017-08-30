#ifndef MODULEHANDLER_H
#define MODULEHANDLER_H

#include "common.h"

#define MODULEHANDLER_DEBUG false

using namespace std;

class RequestPacket;
class Module;

class ModuleHandler {
private:
	std::map<string, Module *> modules;

public:
	ModuleHandler();
	~ModuleHandler();

	void registerModule(string name, Module *module);
	bool dispatch(RequestPacket *packet);
};

#endif