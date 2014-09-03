#include <iostream>
#include "polyplaneHandler.h"
#include "XercesParser.h"
#include "Geant4Factory.h"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "pgonHandler.h"
#include "G4Polyhedra.hh"


static pgonHandler pgon("pgon");

pgonHandler::pgonHandler(std::string s):XMLHandler(s)
{
//	std::cout<<"Creating handler for pgon"<<std::endl;
}

void pgonHandler::ElementHandle()
{
//	std::cout<<"handling for pgon";
	bool res;
	std::string name=getAttributeAsString("name","");
	std::string material=getAttributeAsString("material",res);
	int nSidesPhi=getAttributeAsInt("nSidesPhi",res);
	
	double phi0=0;
	double dPhi=360*CLHEP::deg;
	std::vector<double> vvv=getAttributeAsVector("profile",res);
	if (res)
	{
		phi0=vvv[0];
		dPhi=vvv[1];
	}
	
	StopLoop(true);

 	DOMNode* child;
	int iCurr=0;
	
	std::vector<double> rin_v;
	std::vector<double> rou_v;
	std::vector<double> z_v;

    	const DOMNode* cElement=XercesParser::GetCurrentElement();
    	for (child=cElement->getFirstChild();child!=0;child=child->getNextSibling())
    	{
        	if (child->getNodeType()==DOMNode::ELEMENT_NODE) {
        	    	XercesParser::elementLoop(child);
         		Polyplane p=polyplaneHandler::CurrentPolyplane();
			rin_v.push_back(p.rin());
			rou_v.push_back(p.rou());
			z_v.push_back(p.z());
			iCurr++;
        	}
    	}

	int nZPlanes=iCurr;
	
	double *rin=new double[nZPlanes];
	double *rou=new double[nZPlanes];
	double *z=new double[nZPlanes];
	
	for (int i=0;i<nZPlanes;i++)
	{
		rin[i]=rin_v[i];
		rou[i]=rou_v[i];
		z[i]=z_v[i];
	}
	
	Geant4Factory* factory=Geant4Factory::Factory();
    
    if (name.empty()) {
        name= (factory->GetSolidVector().back()->GetName()+"1");
    }
    
	G4VSolid* sol=factory->CreatePgon(name,nZPlanes,nSidesPhi,phi0,dPhi,rin,rou,z);
	
	if (material.empty()) return;
	
	factory->CreateLogicalVolume(name,material,sol);
	delete rin;
	delete rou;
	delete z;

}
