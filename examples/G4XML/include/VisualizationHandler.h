#ifndef VisualizationHandler_H
#define VisualizationHandler_H

#include "XMLHandler.h"
#include <string>

class VisualizationHandler:public XMLHandler {
public:
	VisualizationHandler(std::string);
	void ElementHandle();

};

#endif
