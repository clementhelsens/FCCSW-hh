#ifndef sphereHandler_H
#define sphereHandler_H

#include "XMLHandler.h"
#include <string>

class sphereHandler:public XMLHandler {
public:
	sphereHandler(std::string);
	void ElementHandle();

};

#endif
