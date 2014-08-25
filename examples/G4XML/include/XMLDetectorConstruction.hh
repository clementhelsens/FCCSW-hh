
#ifndef XMLDetectorConstruction_h
#define XMLDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class XMLDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    XMLDetectorConstruction();
    virtual ~XMLDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

