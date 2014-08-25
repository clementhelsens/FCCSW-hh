#include "pconHandler.h"
#include "XercesParser.h"
#include "polyplaneHandler.h"
#include "Geant4Factory.h"
#include "G4Box.hh"
#include <iostream>

static pconHandler pcon("pcon");

pconHandler::pconHandler(std::string s):XMLHandler(s)
{
}

void pconHandler::ElementHandle()
{
	bool res;
	std::string name=getAttributeAsString("name");
	std::string material=getAttributeAsString("material",res);
		
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
	
	std::vector<double> rin_v;
	std::vector<double> rou_v;
	std::vector<double> z_v;

	int iCurr=0;
	const DOMNode* cElement=XercesParser::GetCurrentElement();
        for (child=cElement->getFirstChild();child!=0;child=child->getNextSibling())
        {
                if (child->getNodeType()==DOMNode::ELEMENT_NODE) 
		{
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
	G4VSolid* sol=factory->CreatePcon(name,nZPlanes,phi0,dPhi,rin,rou,z);
	
	if (material.empty()) return;
	
	factory->CreateLogicalVolume(name,material,sol);
	delete rin;
	delete rou;
	delete z;
}
