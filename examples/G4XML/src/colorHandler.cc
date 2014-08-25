#include "colorHandler.h"
#include <iostream>

#include "Geant4Factory.h"

static colorHandler color("color");

colorHandler::colorHandler(std::string s):XMLHandler(s)
{
}

void colorHandler::ElementHandle()
{
//	bool res;
	std::string name=getAttributeAsString("name");
	double r =getAttributeAsDouble("red");
	double g =getAttributeAsDouble("green");
	double b =getAttributeAsDouble("blue");
	double alpha=getAttributeAsDouble("alpha",1.);
	
	Geant4Factory* factory=Geant4Factory::Factory();
	
	factory->CreateColor(name,r/256.,g/256.,b/256.,alpha);
}
