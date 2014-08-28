#include "GeometryHandler.h"

static GeometryHandler mats("Geometry");

GeometryHandler::GeometryHandler(std::string s):XMLHandler(s)
{
	AddSupportedHandler("box");
	AddSupportedHandler("para");
	AddSupportedHandler("trd");
	AddSupportedHandler("cons");
	AddSupportedHandler("orb");
	AddSupportedHandler("tubs");
	AddSupportedHandler("torus");
	AddSupportedHandler("pgon");
	AddSupportedHandler("pcon");
	AddSupportedHandler("trap");
	AddSupportedHandler("World");
	AddSupportedHandler("var");
	AddSupportedHandler("position");
}

void GeometryHandler::ElementHandle()
{
	//std::cout<<"handling for Geometry"<<std::endl;
}
