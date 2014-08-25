#ifndef Geant4Factory_H
#define Geant4Factory_H

//factory class to build everything G4 and to keep directories of everything

#include <string>
#include <vector>
#include <map>

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4Element;
class G4VSolid;
class G4Colour;

class Geant4Factory {
public:	
	~Geant4Factory() {;}
	static Geant4Factory* 	Factory();
	G4VSolid* 		GetSolid(std::string) const;
	G4LogicalVolume* 	GetLogicalVolume(std::string) const;
	G4Material*	 	GetMaterial(std::string) const;
	G4Element*		GetElement(std::string) const;
	G4Colour*		GetColor(std::string);
	G4VSolid* 		CreateBox(std::string, double,double,double);
	G4VSolid* 		CreateTubs(std::string, double,double,double,double,double);
	G4VSolid* 		CreateTrd(std::string, double,double,double,double,double);
	G4VSolid* 		CreateCons(std::string,double,double,double,double,double,double,double);
	G4VSolid* 		CreatePcon(std::string,int,double,double,double*,double*,double*);
	G4VSolid* 		CreatePgon(std::string,int,int,double,double,double*,double*,double*);
	G4LogicalVolume* 	CreateLogicalVolume(std::string,std::string,G4VSolid*);
	G4Material*		CreateSimpleMaterial(std::string,double,double,double);
	G4Material*		CreateMixture(std::string,double,int);
	G4Element*		CreateElement(std::string,std::string,double,double);
	G4Colour*		CreateColor(std::string, double,double,double,double);
	
	bool			FindMaterial(std::string) const;
	bool 			FindSolid(std::string) const;
	bool			FindLogicalVolume(std::string) const;
	bool			FindElement(std::string) const;
	bool			FindColor(std::string) const;
	
	void 			AddMaterial(std::string,int);
	void			AddMaterial(std::string,double);
	
	void 			SetAsWorld(std::string);
	
	G4VPhysicalVolume*	WorldPhysical() const {return WorldPhysicalVolume;}
	
	G4LogicalVolume*	CurrentEnvelope() const {return envelopeBranch.back();}
	G4LogicalVolume*	CurrentLogicalVolume() const {return theLogVolumes.back();}
	G4VSolid*		CurrentSolid() const {return theSolids.back();}
	
private:
	Geant4Factory() {;}
	std::vector<G4VSolid*> theSolids;
	std::vector<G4LogicalVolume*> theLogVolumes;
	std::vector<G4Material*> theMaterials;
	std::vector<G4Element*> theElements;
	std::map<std::string,G4Colour*> theColors;
	
	G4LogicalVolume* WorldLogicalVolume;
	G4VPhysicalVolume* WorldPhysicalVolume;
	
	std::vector<G4LogicalVolume*> envelopeBranch;
};

#endif
