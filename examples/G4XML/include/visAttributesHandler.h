#ifndef visAttributesHandler_H
#define visAttributesHandler_H

#include "XMLHandler.h"
#include <string>

class visAttributesHandler:public XMLHandler {
public:
	visAttributesHandler(std::string);
	void ElementHandle();

};

#endif
