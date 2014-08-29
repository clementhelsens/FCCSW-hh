#ifndef intersectionHandler_H
#define intersectionHandler_H

#include "XMLHandler.h"
#include <string>

class intersectionHandler:public XMLHandler {
public:
	intersectionHandler(std::string);
	void ElementHandle();

};

#endif
