#ifndef addmaterialHandler_H
#define addmaterialHandler_H

#include "XMLHandler.h"
#include <string>

class addmaterialHandler:public XMLHandler {
public:
	addmaterialHandler(std::string);
	void ElementHandle();

};

#endif
