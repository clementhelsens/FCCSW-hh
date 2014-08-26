#include "consHandler.h"
#include <iostream>

#include "Geant4Factory.h"
#include "G4LogicalVolume.hh"

static consHandler cons("cons");

consHandler::consHandler(std::string s):XMLHandler(s)
{
	AddSupportedHandler("position");
}

void consHandler::ElementHandle()
{
	bool res;
	std::string name=getAttributeAsString("name");
	std::string material=getAttributeAsString("material");
	std::vector<double> vv=getAttributeAsVector("Rio1_Rio2_Z");
	
	std::vector<double> vvv=getAttributeAsVector("profile",res);
	double phi0=0.;
	double dPhi=360.*CLHEP::deg;
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
	G4VSolid *aCons=factory->CreateCons(name,vv[0],vv[1],vv[2],vv[3],vv[4],phi0,dPhi);
	
	if (material.empty()) return;
	
	factory->CreateLogicalVolume(name,material,aCons);
}
