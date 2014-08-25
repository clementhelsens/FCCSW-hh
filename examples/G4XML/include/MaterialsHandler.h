#ifndef MaterialsHandler_H
#define MaterialsHandler_H

#include "XMLHandler.h"
#include <string>

class MaterialsHandler:public XMLHandler {
public:
	MaterialsHandler(std::string);
	void ElementHandle();

};

#endif
