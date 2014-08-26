#ifndef paraHandler_H
#define paraHandler_H

#include "XMLHandler.h"
#include <string>

class paraHandler:public XMLHandler {
public:
	paraHandler(std::string);
	void ElementHandle();

};

#endif
