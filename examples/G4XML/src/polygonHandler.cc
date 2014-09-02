#include "polygonHandler.h"
#include "Polygon.h"
#include <iostream>

static polygonHandler poly("vertex");

Polygon polygonHandler::pPoly(0.,0.);


polygonHandler::polygonHandler(std::string s):XMLHandler(s)
{
}

void polygonHandler::ElementHandle()
{
	bool res;
	std::vector<double> vvv=getAttributeAsVector("vector",res);
	pPoly.fill(vvv);
	
}
