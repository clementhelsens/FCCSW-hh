#ifndef msgHandler_H
#define msgHandler_H

#include "XMLHandler.h"
#include <string>

class msgHandler:public XMLHandler {
public:
	msgHandler(std::string);
	void ElementHandle();

};

#endif
