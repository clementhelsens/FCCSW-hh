#ifndef polyplaneHandler_H
#define polyplaneHandler_H

#include "XMLHandler.h"
#include "Polyplane.h"
#include <string>

class polyplaneHandler:public XMLHandler {
public:
	polyplaneHandler(std::string);
	void ElementHandle();
	static Polyplane CurrentPolyplane() {return pPlane;}
private:
	static Polyplane pPlane;
};

#endif
