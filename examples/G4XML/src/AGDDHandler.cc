#include "AGDDHandler.h"

static AGDDHandler agdd("AGDD");

AGDDHandler::AGDDHandler(std::string s):XMLHandler(s)
{
}

void AGDDHandler::ElementHandle()
{
	std::cout<<"handling for AGDD "<<std::endl;
}
