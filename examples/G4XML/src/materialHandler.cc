#include "materialHandler.h"
#include <iostream>

#include "Geant4Factory.h"

static materialHandler mH("material");

materialHandler::materialHandler(std::string s):XMLHandler(s)
{
}

void materialHandler::ElementHandle()
{
	std::string name=getAttributeAsString("name");
	double a =getAttributeAsDouble("a");
	double Z =getAttributeAsDouble("Z");
	double density =getAttributeAsDouble("density");
	
	Geant4Factory::Factory()->CreateSimpleMaterial(name,a,Z,density);
}
