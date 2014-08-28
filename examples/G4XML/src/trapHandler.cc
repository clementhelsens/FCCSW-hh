#include <iostream>

#include "polyplaneHandler.h"
#include "XercesParser.h"
#include "Geant4Factory.h"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "trapHandler.h"


static trapHandler trap("trap");

trapHandler::trapHandler(std::string s):XMLHandler(s)
{
//	std::cout<<"Creating handler for trap"<<std::endl;
}

void trapHandler::ElementHandle()
{
	bool res;
    
    

	std::string name=getAttributeAsString("name",res);
	std::string material=getAttributeAsString("material",res);
    double  pDz =getAttributeAsDouble("pDz",res);
    double  pTheta =getAttributeAsDouble("pTheta",res);
    double  pPhi =getAttributeAsDouble("pPhi",res);
    double  pDy1 =getAttributeAsDouble("pDy1",res);
    double  pDx1 =getAttributeAsDouble("pDx1",res);
    double  pDx2 =getAttributeAsDouble("pDx2",res);
    double  pAlph1 =getAttributeAsDouble("pAlph1",res);
    double  pDy2 =getAttributeAsDouble("pDy2",res);
    double  pDx3 =getAttributeAsDouble("pDx3",res);
    double  pDx4 =getAttributeAsDouble("pDx4",res);
    double  pAlph2 =getAttributeAsDouble("pAlph2",res);


//	
	Geant4Factory* factory=Geant4Factory::Factory();
	G4VSolid* sol=factory->CreateTrap(name,pDz,pTheta,pPhi,pDy1,pDx1,pDx2,pAlph1, pDy2,pDx3,pDx4,pAlph2);
//
    
	if (material.empty()) return;
//
	factory->CreateLogicalVolume(name,material,sol);
//	delete rin;
//	delete rou;
//	delete z;
//
}
