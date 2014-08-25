#include "polyplaneHandler.h"
#include "Polyplane.h"
#include <iostream>

static polyplaneHandler poly("zPlane");

Polyplane polyplaneHandler::pPlane(0.,0.,0.);


polyplaneHandler::polyplaneHandler(std::string s):XMLHandler(s)
{
}

void polyplaneHandler::ElementHandle()
{
	bool res;
	std::vector<double> vvv=getAttributeAsVector("Rio_Z",res);
	pPlane.rin(vvv[0]);
	pPlane.rou(vvv[1]);
	pPlane.z(vvv[2]);
}
