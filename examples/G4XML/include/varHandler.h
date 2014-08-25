#ifndef varHandler_H
#define varHandler_H

#include "XMLHandler.h"
#include <string>

class varHandler:public XMLHandler {
public:
	varHandler(std::string);
	void ElementHandle();

};

#endif
