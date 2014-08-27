#include "cutTubsHandler.h"
#include <iostream>

#include "Geant4Factory.h"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"

static cutTubsHandler cutTubs("cutTubs");

cutTubsHandler::cutTubsHandler(std::string s):XMLHandler(s)
{

	AddSupportedHandler("position");
}

void cutTubsHandler::ElementHandle()
{
	bool res;
	std::string name=getAttributeAsString("name",res);
	std::string material=getAttributeAsString("material",res);
	std::vector<double> vv=getAttributeAsVector("Rio_Z",res);

	double phi0=0;
	double dPhi=360.*CLHEP::deg;
	std::vector<double> vvv=getAttributeAsVector("profile",res);
	if (res)
	{
		phi0=vvv[0];
		dPhi=vvv[1];
	}
	
	std::vector<double> lowNorm_v=getAttributeAsVector("lowNorm");
	std::vector<double> highNorm_v=getAttributeAsVector("highNorm");
	
	Geant4Factory* factory=Geant4Factory::Factory();
	if (factory->FindSolid(name)) 
	{
		std::cout<<"!!!! Warning !!!! solid "<<name<<" already in the store!!!! "<<std::endl;
	}
	G4VSolid *aCutTubs=factory->CreateCutTubs(name,vv[0],vv[1],vv[2],phi0,dPhi,lowNorm_v,highNorm_v);
	
	if (material.empty()) return;
	
	factory->CreateLogicalVolume(name,material,aCutTubs);
	
}
