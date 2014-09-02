#include "Geant4Factory.h"

#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4Para.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4CutTubs.hh"
#include "G4Torus.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4Polycone.hh"
#include "G4ExtrudedSolid.hh"

#include "G4Polyhedra.hh"
#include "G4Colour.hh"


#include <iostream>

Geant4Factory* Geant4Factory::Factory() 
{
	static Geant4Factory* theFactory=new Geant4Factory;
	return theFactory;
}

G4VSolid* Geant4Factory::GetSolid(std::string name) const
{
	unsigned int size=theSolids.size();
	int iFound=0;
	G4VSolid* found=0;
	for (unsigned int i=0;i<size;i++)
	{
		if (name==theSolids[i]->GetName())
		{
			if (!iFound) found=theSolids[i];
			iFound++;
		}
	}
	if (!found) std::cout<<"solid "<<name<<" not found!!! returning 0!!!"<<std::endl;
	if (iFound>1) std::cout<<"found multiple occurrencies of solid "<<name<<" returning first!"<<std::endl;
	return found;
}
G4LogicalVolume* Geant4Factory::GetLogicalVolume(std::string name) const
{
	unsigned int size=theLogVolumes.size();
	int iFound=0;
	G4LogicalVolume* found=0;
	for (unsigned int i=0;i<size;i++)
	{
		if (name==theLogVolumes[i]->GetName())
		{
			if (!iFound) found=theLogVolumes[i];
			iFound++;
		}
	}
	if (!found) std::cout<<"Logical volume "<<name<<" not found!!! returning 0!!!"<<std::endl;
	if (iFound>1) std::cout<<"found multiple occurrencies of Logical Volume "<<name<<" returning first!"<<std::endl;
	return found;
}

G4Material* Geant4Factory::GetMaterial(std::string name) const
{
	unsigned int size=theMaterials.size();
	int iFound=0;
	G4Material* found=0;
	for (unsigned int i=0;i<size;i++)
	{
		if (name==theMaterials[i]->GetName())
		{
			if (!iFound) found=theMaterials[i];
			iFound++;
		}
	}
	if (!found) std::cout<<"Material "<<name<<" not found!!! returning 0!!!"<<std::endl;
	if (iFound>1) std::cout<<"found multiple occurrencies of material "<<name<<" returning first!"<<std::endl;
	return found;
}

G4Element* Geant4Factory::GetElement(std::string name) const
{
	unsigned int size=theElements.size();
	int iFound=0;
	G4Element* found=0;
	for (unsigned int i=0;i<size;i++)
	{
		if (name==theElements[i]->GetSymbol())
		{
			if (!iFound) found=theElements[i];
			iFound++;
		}
	}
	if (!found) std::cout<<"Element "<<name<<" not found!!! returning 0!!!"<<std::endl;
	if (iFound>1) std::cout<<"found multiple occurrencies of element "<<name<<" returning first!"<<std::endl;
	return found;
}

G4Colour* Geant4Factory::GetColor(std::string name)
{
	if (FindColor(name)) return theColors[name];
	return 0;
}

G4VSolid* Geant4Factory::CreateBox(std::string name, double xDim,double yDim,double zDim)
{
	G4Box* aBox=new G4Box(name,xDim/2.,yDim/2.,zDim/2.);
	theSolids.push_back(aBox);
	return aBox;
}

G4VSolid* Geant4Factory::CreatePara(std::string name, double xDim,double yDim,double zDim, double alpha, double theta, double phi)
{
	G4Para* aPara=new G4Para(name,xDim/2.,yDim/2.,zDim/2.,alpha,theta,phi);
	theSolids.push_back(aPara);
	return aPara;
}

G4VSolid* Geant4Factory::CreateOrb(std::string name, double radius)
{
	G4Orb* anOrb=new G4Orb(name,radius);
	theSolids.push_back(anOrb);
	return anOrb;
}


G4VSolid* Geant4Factory::CreateTubs(std::string name, double Ri,double Ro,double zDim,double phi0, double dPhi)
{
	G4Tubs* aTube=new G4Tubs(name,Ri,Ro,zDim/2.,phi0,dPhi);
	theSolids.push_back(aTube);
	return aTube;
}

G4VSolid* Geant4Factory::CreateCutTubs(std::string name, double Ri,double Ro,double zDim,double phi0, double dPhi, std::vector<double> lowNormV, std::vector<double> highNormV)
{
	G4ThreeVector v1,v2;
	if (lowNormV.size()>=3)
		v1=G4ThreeVector(lowNormV[0],lowNormV[1],lowNormV[2]);
	if (highNormV.size()>=3)
		v2=G4ThreeVector(highNormV[0],highNormV[1],highNormV[2]);
	G4CutTubs* aTube=new G4CutTubs(name,Ri,Ro,zDim/2.,phi0,dPhi,v1,v2);
	theSolids.push_back(aTube);
	return aTube;
}

G4VSolid* Geant4Factory::CreateTorus(std::string name, double Ri,double Ro,double rTorus,double phi0, double dPhi)
{
	G4Torus* aTorus=new G4Torus(name,Ri,Ro,rTorus,phi0,dPhi);
	theSolids.push_back(aTorus);
	return aTorus;
}






G4VSolid* Geant4Factory::CreateTrd(std::string name, double xMin,double xMax,double yMin,double yMax, double dZ)
{
	G4Trd* aTrd=new G4Trd(name,xMin/2.,xMax/2.,yMin/2.,yMax/2.,dZ/2.);
	theSolids.push_back(aTrd);
	return aTrd;
}
G4VSolid* Geant4Factory::CreateCons(std::string name, double R1i,double R1o, double R2i,double R2o,double zDim,double phi0, double dPhi)
{
	G4Cons* aCons=new G4Cons(name,R1i,R1o,R2i,R2o,zDim/2.,phi0,dPhi);
	theSolids.push_back(aCons);
	return aCons;
}

G4VSolid* Geant4Factory::CreatePcon(std::string name, int nPlanes, double phi0,double dPhi,double* ri,double* ro,double* z)
{
	G4Polycone* pCon=new G4Polycone(name,phi0,dPhi,nPlanes,z,ri,ro);
	theSolids.push_back(pCon);
	return pCon;
}

G4VSolid* Geant4Factory::CreateExtruded(std::string name, double halfZ, std::vector<G4TwoVector> polygons, G4TwoVector off1, double scale1, G4TwoVector off2, double scale2)
{
	 G4ExtrudedSolid* pxEtruded=new  G4ExtrudedSolid(name,polygons, halfZ, off1, scale1, off2, scale2 );
	theSolids.push_back(pxEtruded);
	return pxEtruded;
}

G4VSolid* Geant4Factory::CreateSphere(std::string name, double ri,double ro,double phi0,double dPhi,double theta0, double dTheta)
{
	G4Sphere* sphere=new G4Sphere(name,ri,ro,phi0,dPhi,theta0,dTheta);
	theSolids.push_back(sphere);
	return sphere;
}

G4VSolid* Geant4Factory::CreatePgon(std::string name, int nPlanes,int nPhiSides, double phi0,double dPhi,double* ri,double* ro,double* z)
{
	G4Polyhedra* pGon=new G4Polyhedra(name,phi0,dPhi,nPhiSides,nPlanes,z,ri,ro);
	theSolids.push_back(pGon);
	return pGon;
}

G4VSolid* Geant4Factory::CreateTrap(std::string name,double pDz,double pTheta,double pPhi, double pDy1,double pDx1,double pDx2,double pAlph1 ,double pDy2,double pDx3,double pDx4,double pAlph2)
{
	G4Trap* pTrap=new G4Trap(name,pDz,pTheta,pPhi,pDy1,pDx1,pDx2,pAlph1,pDy2,pDx3,pDx4,pAlph2);
	theSolids.push_back(pTrap);
	return pTrap;
}

G4LogicalVolume* Geant4Factory::CreateLogicalVolume(std::string name,std::string material,G4VSolid* solid)
{
    G4Material *mat=G4Material::GetMaterial(material);
	if (!mat) std::cout<<"!!!! Material "<<material<<" not found!!!! LV "<<name<<" has no material associated to it!!!!"<<std::endl;
	G4LogicalVolume *lv=new G4LogicalVolume(solid,mat,name);
	theLogVolumes.push_back(lv);
	return lv;
}

G4Material* Geant4Factory::CreateSimpleMaterial(std::string name,double a,double Z,double density)
{
	bool res=FindMaterial(name);
	if (res) 
	{
		std::cout<<"CreateMSimpleMaterial: trying to create existing material "<<name<<" ...skipping!"<<std::endl;
		return 0;
	}	
	G4Material *mat=new G4Material(name,Z,a,density);
	theMaterials.push_back(mat);
	return mat;
}

G4Element* Geant4Factory::CreateElement(std::string name,std::string symbol,double z,double a)
{
	bool res=FindElement(name);
	if (res) 
	{
		std::cout<<"CreateElement: trying to create existing element "<<name<<" ...skipping!"<<std::endl;
		return 0;
	}	
	G4Element *mat=new G4Element(name,symbol,z,a);
	theElements.push_back(mat);
	return mat;
}

G4Material* Geant4Factory::CreateMixture(std::string name,double density,int ncomp)
{
	bool res=FindMaterial(name);
	if (res) 
	{
		std::cout<<"CreateMixture: trying to create existing material "<<name<<" ...skipping!"<<std::endl;
		return 0;
	}	
	G4Material *mat=new G4Material(name,density,ncomp);
	theMaterials.push_back(mat);
	return mat;
}

G4Colour* Geant4Factory::CreateColor(std::string name,double r,double g,double b,double a)
{
	if (FindColor(name))
	{
		std::cout<<"CreateColor: trying to create an existing color "<<name<<" ...skipping!"<<std::endl;
		return 0;
	}
	G4Colour* col=new G4Colour(r,g,b,a);
	theColors[name]=col;
	return col;
}

bool Geant4Factory::FindSolid(std::string name) const
{
	for (unsigned int i=0;i<theSolids.size();i++)
		if (name==theSolids[i]->GetName()) return true;
	return false;
}
bool Geant4Factory::FindLogicalVolume(std::string name) const
{
	for (unsigned int i=0;i<theLogVolumes.size();i++)
		if (name==theLogVolumes[i]->GetName()) return true;
	return false;
}
bool Geant4Factory::FindMaterial(std::string name) const
{
	for (unsigned int i=0;i<theMaterials.size();i++)
		if (name==theMaterials[i]->GetName()) return true;
	return false;
}
bool Geant4Factory::FindElement(std::string name) const
{
	for (unsigned int i=0;i<theElements.size();i++)
		if (name==theElements[i]->GetSymbol()) return true;
	return false;
}
bool Geant4Factory::FindColor(std::string name) const
{
	return theColors.find(name)!=theColors.end();
}

void Geant4Factory::AddMaterial(std::string element, int natoms)
{
	G4Material* mat=theMaterials.back();
	G4Element* a_mat=GetElement(element);
	mat->AddElement(a_mat,natoms);
}

void Geant4Factory::AddMaterial(std::string material,double fractionmass)
{
	G4Material* mat=theMaterials.back();
	G4Material* a_mat=GetMaterial(material);
	mat->AddMaterial(a_mat,fractionmass);
}

void Geant4Factory::SetAsWorld(std::string name)
{
	WorldLogicalVolume=GetLogicalVolume(name);
	if (!WorldLogicalVolume) 
		std::cout<<"Geant4Factory::SetAsWorld - Something is wrong!!!! The LogicalVolume is not set!!!"<<std::endl;
	else
		WorldPhysicalVolume=new G4PVPlacement(0,
                      		G4ThreeVector(),
                      		WorldLogicalVolume,
                      		"World",               
                      		0,                     
                      		false,                 
                      		0,  
				false);		// to be reviewed
	envelopeBranch.push_back(WorldLogicalVolume);
	return;                   
}

