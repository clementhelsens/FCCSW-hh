#include "mixtureHandler.h"
#include <iostream>

#include "Geant4Factory.h"

static mixtureHandler mH("mixture");

mixtureHandler::mixtureHandler(std::string s):XMLHandler(s)
{
	AddSupportedHandler("addmaterial");
}

void mixtureHandler::ElementHandle()
{
	std::string name=getAttributeAsString("name");
	double density =getAttributeAsDouble("density");
	int ncomp=getAttributeAsInt("ncomponents");
	
	Geant4Factory::Factory()->CreateMixture(name,density,ncomp);
}
