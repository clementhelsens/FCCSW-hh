#ifndef pconHandler_H
#define pconHandler_H

#include "XMLHandler.h"
#include <string>

class pconHandler:public XMLHandler {
public:
	pconHandler(std::string);
	void ElementHandle();

};

#endif
