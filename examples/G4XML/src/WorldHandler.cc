#include "WorldHandler.h"
#include <iostream>

#include "Geant4Factory.h"

static WorldHandler world("World");

WorldHandler::WorldHandler(std::string s):XMLHandler(s)
{
}

void WorldHandler::ElementHandle()
{

	std::string name=getAttributeAsString("volume");
	//std::cout<<"handling for World: volume="<<name<<std::endl;

	Geant4Factory* factory=Geant4Factory::Factory();

	factory->SetAsWorld(name);
}
