#ifndef polygoneHandler_H
#define polygoneHandler_H

#include "XMLHandler.h"
#include "Polygon.h"
#include <string>

class polygonHandler:public XMLHandler {
public:
	polygonHandler(std::string);
	void ElementHandle();
	static Polygon CurrentPolygon() {return pPoly;}
private:
	static Polygon pPoly;
};

#endif
