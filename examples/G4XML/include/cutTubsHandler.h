#ifndef cutTubsHandler_H
#define cutTubsHandler_H

#include "XMLHandler.h"

#include <string>

class cutTubsHandler:public XMLHandler {
public:
	cutTubsHandler(std::string);
	void ElementHandle();

};

#endif
