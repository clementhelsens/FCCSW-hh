#include "visAttributesHandler.h"
#include <iostream>

#include "Geant4Factory.h"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4Colour.hh"

static visAttributesHandler visAttributes("visAttributes");

visAttributesHandler::visAttributesHandler(std::string s):XMLHandler(s)
{
	AddSupportedHandler("position");
}

void visAttributesHandler::ElementHandle()
{

//	std::cout<<"visAttributes handler called "<<std::endl;
//	bool res;
	std::string name=getAttributeAsString("volume");
	std::string color=getAttributeAsString("color","");
	int visible=getAttributeAsInt("visible",1);
	int forceWireFrame=getAttributeAsInt("forceWireframe",0);
	int forceSolid=getAttributeAsInt("forceSolid",0);
	
	Geant4Factory* factory=Geant4Factory::Factory();
	
	G4LogicalVolume* lv=factory->GetLogicalVolume(name);
	G4Colour* col=0;
	if (!color.empty()) col=factory->GetColor(color);
//	if (col) std::cout<<"color "<<color<<" found"<<std::endl;
	
	G4VisAttributes* va=const_cast<G4VisAttributes*>(lv->GetVisAttributes());
	if (!va) va=new G4VisAttributes;
	
	if (col) va->SetColor(*col);
	if (!visible) va->SetVisibility(false);
//	std::cout<<" Volume "<<name<<" forceWireFrame set to "<<forceWireFrame<<std::endl;
//	std::cout<<" Volume "<<name<<" forceSolid set to "<<forceSolid<<std::endl;
	if (forceWireFrame) va->SetForceWireframe(true);
	else va->SetForceWireframe(false);
	if (forceSolid) va->SetForceSolid(true);
	else va->SetForceSolid(false);
	
	lv->SetVisAttributes(va);
}
