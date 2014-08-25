#include "elementHandler.h"
#include <iostream>

#include "Geant4Factory.h"

static elementHandler eH("element");

elementHandler::elementHandler(std::string s):XMLHandler(s)
{
}

void elementHandler::ElementHandle()
{
	std::string name=getAttributeAsString("name");
	std::string symbol=getAttributeAsString("symbol");
	double a =getAttributeAsDouble("aweight");
	double z =getAttributeAsDouble("z");
	
	Geant4Factory::Factory()->CreateElement(name,symbol,z,a);
	
	bool res;
	double density=getAttributeAsDouble("density",res);
	
	if (res)
	{
		Geant4Factory::Factory()->CreateSimpleMaterial(name,a,z,density);
	}
}
