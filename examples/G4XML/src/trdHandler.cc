#include "trdHandler.h"
#include <iostream>

#include "G4SolidStore.hh"
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
	
	G4SolidStore* sStore=G4SolidStore::GetInstance();
	G4VSolid* aSolid=sStore->GetSolid(name);
	if (aSolid) 
	{
		std::cout<<"!!!! Warning !!!! solid "<<name<<" already in the store!!!! "<<std::endl;
	}
	G4Trd* aTrd=new G4Trd(name,vv[0]/2.,vv[1]/2.,vv[2]/2.,vv[3]/2.,vv[4]/2.);
	
	if (material.empty()) return;
	
	G4Material *mat=G4Material::GetMaterial(material);
	if (!mat) std::cout<<"!!!! Material "<<material<<" not found!!!! LV "<<name<<" has no material associated to it!!!!"<<std::endl;

	G4LogicalVolume *lv;
	lv=new G4LogicalVolume(aTrd,mat,name);
}
