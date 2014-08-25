#ifndef mixtureHandler_H
#define mixtureHandler_H

#include "XMLHandler.h"
#include <string>

class mixtureHandler:public XMLHandler {
public:
	mixtureHandler(std::string);
	void ElementHandle();

};

#endif
