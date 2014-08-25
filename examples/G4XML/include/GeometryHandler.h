#ifndef GeometryHandler_H
#define GeometryHandler_H

#include "XMLHandler.h"
#include <string>

class GeometryHandler:public XMLHandler {
public:
	GeometryHandler(std::string);
	void ElementHandle();

};

#endif
