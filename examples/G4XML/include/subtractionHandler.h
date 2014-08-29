#ifndef subtractionHandler_H
#define subtractionHandler_H

#include "XMLHandler.h"
#include <string>

class subtractionHandler:public XMLHandler {
public:
	subtractionHandler(std::string);
	void ElementHandle();

};

#endif
