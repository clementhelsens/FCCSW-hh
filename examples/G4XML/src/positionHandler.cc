#include "positionHandler.h"
#include <iostream>

#include "Geant4Factory.h"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"

static positionHandler Pos("position");

positionHandler::positionHandler(std::string s):XMLHandler(s)
{
}

void positionHandler::ElementHandle()
{
	bool res;
	std::string daughter=getAttributeAsString("daughter","");
	std::string mother=getAttributeAsString("mother","");
	int copyNo=getAttributeAsInt("copyNumber",0);
	
	G4ThreeVector pos3D;
	std::vector<double> pos = getAttributeAsVector("translate",res);
	if (res) pos3D=G4ThreeVector(pos[0],pos[1],pos[2]);
	
	G4RotationMatrix *rotation=0;
	std::vector<double> rot = getAttributeAsVector("rotate",res);
	if (res)
	{
		rotation=new G4RotationMatrix;
		rotation->rotateX(rot[0]);
		rotation->rotateY(rot[1]);
		rotation->rotateZ(rot[2]);
	}
	
	Geant4Factory* factory=Geant4Factory::Factory();
	G4LogicalVolume *mom;
	if (mother.empty()) 
		mom=factory->CurrentEnvelope();
	else 
		mom=factory->GetLogicalVolume(mother);
	
	G4LogicalVolume *dau;
	if (daughter.empty())	
		dau=factory->CurrentLogicalVolume();
	else
		dau=factory->GetLogicalVolume(daughter);
	
	G4PVPlacement *pv;
	pv=new G4PVPlacement(rotation,pos3D,dau,dau->GetName(),mom,false,copyNo);
}
