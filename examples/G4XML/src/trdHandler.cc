#include "trdHandler.h"
#include <iostream>

#include "Geant4Factory.h"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"

static trdHandler trd("trd");

trdHandler::trdHandler(std::string s):XMLHandler(s)
{
//	std::cout<<"Creating handler for trd"<<std::endl;
}

void trdHandler::ElementHandle()
{
	bool res;
	std::string name=getAttributeAsString("name",res);
	std::string material=getAttributeAsString("material",res);
	std::vector<double> vv=getAttributeAsVector("Xmp_Ymp_Z",res);
	
	Geant4Factory* factory=Geant4Factory::Factory();
	if (factory->FindSolid(name)) 
	{
		std::cout<<"!!!! Warning !!!! solid "<<name<<" already in the store!!!! "<<std::endl;
	}
	G4VSolid *aTrd=factory->CreateTrd(name,vv[0],vv[1],vv[2],vv[3],vv[4]);
	
	if (material.empty()) return;
	
	factory->CreateLogicalVolume(name,material,aTrd);
}
