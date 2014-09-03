#include "componentHandler.h"
#include "Component.h"
#include <iostream>

#include <G4DisplacedSolid.hh>
#include "XercesParser.h"
#include "Geant4Factory.h"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4IntersectionSolid.hh"

#include "G4Material.hh"

static componentHandler component("component");

Component componentHandler::pComponent("",0.,0.,0.,0.,0.,0.);


componentHandler::componentHandler(std::string s):XMLHandler(s)
{
}

void componentHandler::ElementHandle()
{
    bool res;
    std::string volume_ =getAttributeAsString("volume","");
    std::vector<double> vvv_position(3);
	vvv_position=getAttributeAsVector("position",res);
    std::vector<double> vvv_rotation(3);
	 vvv_rotation=getAttributeAsVector("rotation",res);
    StopLoop(true);
	DOMNode* child;
    
    const DOMNode* cElement=XercesParser::GetCurrentElement();
    for (child=cElement->getFirstChild();child!=0;child=child->getNextSibling())
    {
        if (child->getNodeType()==DOMNode::ELEMENT_NODE)
		{
            XercesParser::elementLoop(child);
        }
    
	}
    
    
    
    
    if (volume_.empty()){
        Geant4Factory* factory=Geant4Factory::Factory();
        
        std::vector<G4VSolid*> solidvector = factory->GetSolidVector();
        volume_ = solidvector.back()->GetName();
        
        
    }

    pComponent.volume(volume_);
    pComponent.x_pos(vvv_position[0]);
    pComponent.y_pos(vvv_position[1]);
    pComponent.z_pos(vvv_position[2]);
    pComponent.alpha(vvv_rotation[0]);
    pComponent.beta(vvv_rotation[1]);
    pComponent.gamma(vvv_rotation[2]);

	
   
    
    
}
