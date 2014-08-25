#include "consHandler.h"
#include <iostream>

#include "G4SolidStore.hh"
#include "G4cons.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"

consHandler::consHandler(std::string s):XMLHandler(s)
{
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
		
	G4SolidStore* sStore=G4SolidStore::GetInstance();
	G4VSolid* aSolid=sStore->GetSolid(name);
	if (aSolid) 
	{
		std::cout<<"!!!! Warning !!!! solid "<<name<<" already in the store!!!! "<<std::endl;
	}
	G4Cons* aCons=new G4Cons(name,vv[0],vv[1],vv[2],vv[3],vv[4]/2.,phi0,dPhi);
	
	if (material.empty()) return;
	
	G4Material *mat=G4Material::GetMaterial(material);
	if (!mat) std::cout<<"!!!! Material "<<material<<" not found!!!! LV "<<name<<" has no material associated to it!!!!"<<std::endl;

	G4LogicalVolume *lv;
	lv=new G4LogicalVolume(aCons,mat,name);
}
