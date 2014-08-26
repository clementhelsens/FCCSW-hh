#ifndef torusHandler_H
#define torusHandler_H

#include "XMLHandler.h"

#include <string>

class torusHandler:public XMLHandler {
public:
	torusHandler(std::string);
	void ElementHandle();

};

#endif
