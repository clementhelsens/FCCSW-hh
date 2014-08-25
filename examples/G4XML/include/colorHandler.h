#ifndef colorHandler_H
#define colorHandler_H

#include "XMLHandler.h"
#include <string>

class colorHandler:public XMLHandler {
public:
	colorHandler(std::string);
	void ElementHandle();

};

#endif
