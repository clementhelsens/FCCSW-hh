#include "intersectionHandler.h"
#include <iostream>

#include <G4DisplacedSolid.hh>
#include "componentHandler.h"
#include "XercesParser.h"
#include "Geant4Factory.h"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4IntersectionSolid.hh"

#include "G4Material.hh"

static intersectionHandler intersections("intersection");

intersectionHandler::intersectionHandler(std::string s):XMLHandler(s)
{
}

void intersectionHandler::ElementHandle()
{
	bool res;
	std::string name=getAttributeAsString("name");
	std::string material=getAttributeAsString("material",res);
		StopLoop(true);
	DOMNode* child;
	
    
    std::vector<std::string> volumes;

	std::vector<double> x_position;
	std::vector<double> y_position;
	std::vector<double> z_position;
    std::vector<double> alpha_rotation;
	std::vector<double> beta_rotation;
	std::vector<double> gamma_rotation;


	int iCurr=0;
	const DOMNode* cElement=XercesParser::GetCurrentElement();
        for (child=cElement->getFirstChild();child!=0;child=child->getNextSibling())
        {
                if (child->getNodeType()==DOMNode::ELEMENT_NODE) 
		{
                	XercesParser::elementLoop(child);
            
        
			Component p=componentHandler::Currentcomponent();
            
            volumes.push_back(p.volume());
			x_position.push_back(p.x_pos());
			y_position.push_back(p.y_pos());
			z_position.push_back(p.z_pos());
            alpha_rotation.push_back(p.alpha());
            beta_rotation.push_back(p.beta());
            gamma_rotation.push_back(p.gamma());

            
			iCurr++;
                }
        }
	

    std::vector<G4VSolid*> vol_vett;
    Geant4Factory* factory=Geant4Factory::Factory();

    for (unsigned long i = 0; i<volumes.size(); i++) {

        G4VSolid* vol = factory->GetSolid(volumes[i]);
        
        G4DisplacedSolid* vol_displ = new G4DisplacedSolid(name, vol, new CLHEP::HepRotation(alpha_rotation[i],beta_rotation[i],gamma_rotation[i]), G4ThreeVector(x_position[i],y_position[i],z_position[i]));
        vol_vett.push_back(vol_displ);
    }
    
    G4VSolid* firstSolid = vol_vett[0];
    
  
	
    for (unsigned long j=0; j<vol_vett.size(); j++)
    {
        
        G4IntersectionSolid* intersectionSolid = new G4IntersectionSolid(name, firstSolid, vol_vett[j]);
        
        firstSolid = intersectionSolid;
    
    
    }
    
    
    
    
    factory->InsertVolume(firstSolid);
	factory->CreateLogicalVolume(name,material,firstSolid);

}
