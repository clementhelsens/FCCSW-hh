#ifndef componentHandler_H
#define componentHandler_H

#include "XMLHandler.h"
#include "Component.h"
#include <string>

class componentHandler:public XMLHandler {
public:
	componentHandler(std::string);
	void ElementHandle();
	static Component Currentcomponent() {return pComponent;}
private:
	static Component pComponent;
};

#endif
