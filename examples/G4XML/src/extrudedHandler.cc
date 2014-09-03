#include "extrudedHandler.h"
#include <iostream>

#include "polygonHandler.h"
#include "XercesParser.h"
#include "Geant4Factory.h"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4ExtrudedSolid.hh"


#include "G4TwoVector.hh"

static extrudedHandler extruded("extruded");

extrudedHandler::extrudedHandler(std::string s):XMLHandler(s)
{
}

void extrudedHandler::ElementHandle()
{
	bool res;
	std::string name=getAttributeAsString("name", "");
	std::string material=getAttributeAsString("material",res);
		
	double halfZ=getAttributeAsDouble("halfZ",res);
    
    std::vector<double> off1_(2);
    off1_= getAttributeAsVector("off1",res);
    double scale1;
    scale1=getAttributeAsDouble("scale1",res);
    std::vector<double> off2_(2);
    off2_= getAttributeAsVector("off1",res);
    double scale2;
	scale2=getAttributeAsDouble("scale2",res);

	
	StopLoop(true);
	DOMNode* child;
	
	std::vector<double> polygons1;
	std::vector<double> polygons2;


	int iCurr=0;
	const DOMNode* cElement=XercesParser::GetCurrentElement();
        for (child=cElement->getFirstChild();child!=0;child=child->getNextSibling())
        {
                if (child->getNodeType()==DOMNode::ELEMENT_NODE) 
		{
                	XercesParser::elementLoop(child);
			Polygon p=polygonHandler::CurrentPolygon();
			polygons1.push_back(p.extract1());
            polygons2.push_back(p.extract2());

			iCurr++;
                }
        }
    std::vector<G4TwoVector> polygons;
    
    for(unsigned long i = 0; i<polygons1.size(); i++){
    
        G4TwoVector temp = G4TwoVector(polygons1[i],polygons2[i]);
        polygons.push_back(temp);
    
    }
    
    if(scale1==0) scale1=1;
    if(scale2==0) scale2=1;
    
    G4TwoVector off1 = G4TwoVector(off1_[0],off1_[1]);
    G4TwoVector off2 = G4TwoVector(off2_[0],off2_[1]);

	Geant4Factory* factory=Geant4Factory::Factory();
    
    if (name.empty()) {
        name= (factory->GetSolidVector().back()->GetName()+"1");
    }
    
	G4VSolid* sol=factory->CreateExtruded(name,halfZ,polygons, off1, scale1, off2,  scale2);
	
	if (material.empty()) return;
	
	factory->CreateLogicalVolume(name,material,sol);
}
