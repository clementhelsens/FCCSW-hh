#ifndef tubsHandler_H
#define tubsHandler_H

#include "XMLHandler.h"

#include <string>

class tubsHandler:public XMLHandler {
public:
	tubsHandler(std::string);
	void ElementHandle();

};

#endif
