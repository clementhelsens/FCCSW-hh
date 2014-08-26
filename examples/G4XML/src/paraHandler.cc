#include "paraHandler.h"
#include <iostream>

#include "Geant4Factory.h"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"

static paraHandler para("para");

paraHandler::paraHandler(std::string s):XMLHandler(s)
{
	AddSupportedHandler("position");
}

void paraHandler::ElementHandle()
{
//	bool res;
	std::string name=getAttributeAsString("name");
	std::string material=getAttributeAsString("material","");
	double xDim =getAttributeAsDouble("X");
	double yDim =getAttributeAsDouble("Y");
	double zDim =getAttributeAsDouble("Z");
	double alpha=getAttributeAsDouble("alpha",0);
	double theta=getAttributeAsDouble("theta",0);
	double phi  =getAttributeAsDouble("phi",0);
	//std::cout<<"handling for para "<<name<<std::endl;
	
	Geant4Factory* factory=Geant4Factory::Factory();
	if (factory->FindSolid(name)) 
	{
		std::cout<<"!!!! Warning !!!! solid "<<name<<" already in the store!!!! "<<std::endl;
	}
	G4VSolid *apara=factory->CreatePara(name,xDim,yDim,zDim,alpha,theta,phi);
	
	if (material.empty()) return;
	
	factory->CreateLogicalVolume(name,material,apara);
}
