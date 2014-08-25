
#include "XMLDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "Geant4Factory.h"

XMLDetectorConstruction::XMLDetectorConstruction()
: G4VUserDetectorConstruction()
{ 
}

XMLDetectorConstruction::~XMLDetectorConstruction()
{
}

G4VPhysicalVolume* XMLDetectorConstruction::Construct()
{  
  G4VPhysicalVolume* world=Geant4Factory::Factory()->WorldPhysical();
  if (!world) std::cout<<"DetectorConstruction: world is not set!!!!!!!!!!!"<<std::endl;
  return world;
}
