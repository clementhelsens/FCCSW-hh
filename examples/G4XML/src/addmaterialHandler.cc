#include "addmaterialHandler.h"
#include <iostream>

#include "Geant4Factory.h"

static addmaterialHandler aM("addmaterial");

addmaterialHandler::addmaterialHandler(std::string s):XMLHandler(s)
{
}

void addmaterialHandler::ElementHandle()
{
	bool res;
	std::string name=getAttributeAsString("material");
	//std::cout<<"handling for addMaterial "<<std::endl;
	double fractionmass=getAttributeAsDouble("fractionmass",res);
	if (!res)
	{
		int natoms=getAttributeAsInt("natoms");
		Geant4Factory::Factory()->AddMaterial(name,natoms);
	}
	else 
		Geant4Factory::Factory()->AddMaterial(name,fractionmass);
}
