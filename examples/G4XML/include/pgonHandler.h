#ifndef pgonHandler_H
#define pgonHandler_H

#include "XMLHandler.h"
#include <string>

class pgonHandler:public XMLHandler {
public:
	pgonHandler(std::string);
	void ElementHandle();

};

#endif
