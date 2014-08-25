#ifndef WorldHandler_H
#define WorldHandler_H

#include "XMLHandler.h"
#include <string>

class WorldHandler:public XMLHandler {
public:
	WorldHandler(std::string);
	void ElementHandle();

};

#endif
