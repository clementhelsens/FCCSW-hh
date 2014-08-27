#include "sphereHandler.h"
#include <iostream>

#include "Geant4Factory.h"
#include "G4LogicalVolume.hh"

static sphereHandler sphere("sphere");

sphereHandler::sphereHandler(std::string s):XMLHandler(s)
{
	AddSupportedHandler("position");
}

void sphereHandler::ElementHandle()
{
	std::string name=getAttributeAsString("name");
	std::string material=getAttributeAsString("material");
	double rMin=getAttributeAsDouble("rMin",0);
	double rMax=getAttributeAsDouble("rMax");
	double phi0=getAttributeAsDouble("phi0",0.);
	double dPhi=getAttributeAsDouble("dPhi",360.*CLHEP::deg);
	double theta0=getAttributeAsDouble("theta0",0.);
	double dTheta=getAttributeAsDouble("ddTheta",180.*CLHEP::deg);
		
	Geant4Factory* factory=Geant4Factory::Factory();
	if (factory->FindSolid(name)) 
	{
		std::cout<<"!!!! Warning !!!! solid "<<name<<" already in the store!!!! "<<std::endl;
	}
	G4VSolid *asphere=factory->CreateSphere(name,rMin,rMax,phi0,dPhi,theta0,dTheta);
	
	if (material.empty()) return;
	
	factory->CreateLogicalVolume(name,material,asphere);
}
