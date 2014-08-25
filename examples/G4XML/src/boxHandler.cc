#include "boxHandler.h"
#include <iostream>

#include "Geant4Factory.h"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"

static boxHandler box("box");

boxHandler::boxHandler(std::string s):XMLHandler(s)
{
	AddSupportedHandler("position");
}

void boxHandler::ElementHandle()
{
//	bool res;
	std::string name=getAttributeAsString("name");
	std::string material=getAttributeAsString("material","");
	double xDim =getAttributeAsDouble("X");
	double yDim =getAttributeAsDouble("Y");
	double zDim =getAttributeAsDouble("Z");
	//std::cout<<"handling for box "<<name<<std::endl;
	
	Geant4Factory* factory=Geant4Factory::Factory();
	if (factory->FindSolid(name)) 
	{
		std::cout<<"!!!! Warning !!!! solid "<<name<<" already in the store!!!! "<<std::endl;
	}
	G4VSolid *aBox=factory->CreateBox(name,xDim,yDim,zDim);
	
	if (material.empty()) return;
	
	factory->CreateLogicalVolume(name,material,aBox);
}
