#ifndef consHandler_H
#define consHandler_H

#include "XMLHandler.h"
#include <string>

class consHandler:public XMLHandler {
public:
	consHandler(std::string);
	void ElementHandle();

};

#endif
