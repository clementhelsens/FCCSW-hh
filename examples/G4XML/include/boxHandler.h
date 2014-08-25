#ifndef boxHandler_H
#define boxHandler_H

#include "XMLHandler.h"
#include <string>

class boxHandler:public XMLHandler {
public:
	boxHandler(std::string);
	void ElementHandle();

};

#endif
