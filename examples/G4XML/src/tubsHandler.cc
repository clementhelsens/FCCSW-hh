#include "tubsHandler.h"
#include <iostream>

#include "Geant4Factory.h"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"

static tubsHandler tubs("tubs");

tubsHandler::tubsHandler(std::string s):XMLHandler(s)
{
//	std::cout<<"Creating handler for tubs"<<std::endl;
	AddSupportedHandler("position");
}

void tubsHandler::ElementHandle()
{
	bool res;
	std::string name=getAttributeAsString("name","");
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
	
	Geant4Factory* factory=Geant4Factory::Factory();
    
    if (name.empty()) {
        name= (factory->GetSolidVector().back()->GetName()+"1");
    }
    
	if (factory->FindSolid(name))
	{
		std::cout<<"!!!! Warning !!!! solid "<<name<<" already in the store!!!! "<<std::endl;
	}
	G4VSolid *aTube=factory->CreateTubs(name,vv[0],vv[1],vv[2],phi0,dPhi);
	
	if (material.empty()) return;
	
	factory->CreateLogicalVolume(name,material,aTube);
	
}
