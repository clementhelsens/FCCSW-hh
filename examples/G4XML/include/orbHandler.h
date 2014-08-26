#ifndef orbHandler_H
#define orbHandler_H

#include "XMLHandler.h"
#include <string>

class orbHandler:public XMLHandler {
public:
	orbHandler(std::string);
	void ElementHandle();

};

#endif
