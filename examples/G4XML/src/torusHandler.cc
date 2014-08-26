#include "torusHandler.h"
#include <iostream>

#include "Geant4Factory.h"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"

static torusHandler torus("torus");

torusHandler::torusHandler(std::string s):XMLHandler(s)
{
//	std::cout<<"Creating handler for torus"<<std::endl;
	AddSupportedHandler("position");
}

void torusHandler::ElementHandle()
{
	bool res;
	std::string name=getAttributeAsString("name",res);
	std::string material=getAttributeAsString("material",res);
	double rMin=getAttributeAsDouble("rMin");
	double rMax=getAttributeAsDouble("rMax");
	double rTorus=getAttributeAsDouble("rTorus");

	double phi0=0;
	double dPhi=360.*CLHEP::deg;
	std::vector<double> vvv=getAttributeAsVector("profile",res);
	if (res)
	{
		phi0=vvv[0];
		dPhi=vvv[1];
	}
	
	Geant4Factory* factory=Geant4Factory::Factory();
	if (factory->FindSolid(name)) 
	{
		std::cout<<"!!!! Warning !!!! solid "<<name<<" already in the store!!!! "<<std::endl;
	}
	G4VSolid *aTorus=factory->CreateTorus(name,rMin,rMax,rTorus,phi0,dPhi);
	
	if (material.empty()) return;
	
	factory->CreateLogicalVolume(name,material,aTorus);
	
}
