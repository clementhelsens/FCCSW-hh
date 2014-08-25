#ifndef AGDDHandler_H
#define AGDDHandler_H

#include "XMLHandler.h"
#include <string>

class AGDDHandler:public XMLHandler {
public:
	AGDDHandler(std::string);
	void ElementHandle();

};

#endif
