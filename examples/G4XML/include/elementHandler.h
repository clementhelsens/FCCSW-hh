#ifndef elementHandler_H
#define elementHandler_H

#include "XMLHandler.h"
#include <string>

class elementHandler:public XMLHandler {
public:
	elementHandler(std::string);
	void ElementHandle();

};

#endif
