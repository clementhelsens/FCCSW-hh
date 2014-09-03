#include "orbHandler.h"
#include <iostream>

#include "Geant4Factory.h"
#include "G4Orb.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"

static orbHandler orb("orb");

orbHandler::orbHandler(std::string s):XMLHandler(s)
{
	AddSupportedHandler("position");
}

void orbHandler::ElementHandle()
{
//	bool res;
	std::string name=getAttributeAsString("name", "");
	std::string material=getAttributeAsString("material","");
	double radius =getAttributeAsDouble("radius");
	
	Geant4Factory* factory=Geant4Factory::Factory();
    
    if (name.empty()) {
        name= (factory->GetSolidVector().back()->GetName()+"1");
    }
    
	if (factory->FindSolid(name))
	{
		std::cout<<"!!!! Warning !!!! solid "<<name<<" already in the store!!!! "<<std::endl;
	}
	G4VSolid *anOrb=factory->CreateOrb(name,radius);
	
	if (material.empty()) return;
	
	factory->CreateLogicalVolume(name,material,anOrb);
}
