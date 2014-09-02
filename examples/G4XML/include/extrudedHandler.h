#ifndef extrudedHandler_H
#define extrudedHandler_H

#include "XMLHandler.h"
#include <string>

class extrudedHandler:public XMLHandler {
public:
	extrudedHandler(std::string);
	void ElementHandle();

};

#endif
