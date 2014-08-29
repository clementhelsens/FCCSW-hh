#ifndef unionHandler_H
#define unionHandler_H

#include "XMLHandler.h"
#include <string>

class unionHandler:public XMLHandler {
public:
	unionHandler(std::string);
	void ElementHandle();

};

#endif
