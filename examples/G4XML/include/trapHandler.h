#ifndef trapHandler_H
#define trapHandler_H

#include "XMLHandler.h"
#include <string>

class trapHandler:public XMLHandler {
public:
	trapHandler(std::string);
	void ElementHandle();

};

#endif
