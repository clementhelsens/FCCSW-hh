#ifndef materialHandler_H
#define materialHandler_H

#include "XMLHandler.h"
#include <string>

class materialHandler:public XMLHandler {
public:
	materialHandler(std::string);
	void ElementHandle();

};

#endif
