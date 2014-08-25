#include "GeometryHandler.h"

static GeometryHandler mats("Geometry");

GeometryHandler::GeometryHandler(std::string s):XMLHandler(s)
{
	AddSupportedHandler("box");
	AddSupportedHandler("tubs");
	AddSupportedHandler("pgon");
	AddSupportedHandler("pcon");
	AddSupportedHandler("World");
	AddSupportedHandler("var");
	AddSupportedHandler("position");
}

void GeometryHandler::ElementHandle()
{
	//std::cout<<"handling for Geometry"<<std::endl;
}
