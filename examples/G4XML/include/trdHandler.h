#ifndef trdHandler_H
#define trdHandler_H

#include "XMLHandler.h"

#include <string>

class trdHandler:public XMLHandler {
public:
	trdHandler(std::string);
	void ElementHandle();

};

#endif
