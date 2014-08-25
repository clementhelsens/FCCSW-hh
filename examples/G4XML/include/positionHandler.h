#ifndef positionHandler_H
#define positionHandler_H

#include "XMLHandler.h"
#include <string>

class positionHandler:public XMLHandler {
public:
	positionHandler(std::string);
	void ElementHandle();

};

#endif
