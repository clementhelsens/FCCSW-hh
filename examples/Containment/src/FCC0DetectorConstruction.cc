//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id$
//
/// \file FCC0DetectorConstruction.cc
/// \brief Implementation of the FCC0DetectorConstruction class

#include "FCC0DetectorConstruction.hh"
#include "FCC0EmCalorimeterSD.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProductionCuts.hh"
#include "G4SystemOfUnits.hh"
#include <string>
#include <sstream>
#include <iostream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FCC0DetectorConstruction::FCC0DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FCC0DetectorConstruction::~FCC0DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* FCC0DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nistManager = G4NistManager::Instance();

  // Build materials
  G4Material* air = nistManager->FindOrBuildMaterial("G4_Galactic");
  //  G4Material* copper = nistManager->FindOrBuildMaterial("G4_Cu");
  G4Material* iron = nistManager->FindOrBuildMaterial("G4_Fe");
  //G4Material* tungsten = nistManager->FindOrBuildMaterial("G4_W");

       // There is no need to test if materials were built/found
       // as G4NistManager would issue an error otherwise
       // Try the code with "XYZ".      
       
  // Print all materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;         
  
  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double hx = 20.*m;
  G4double hy = 20.*m;
  G4double hz = 20.*m;
  
  // world volume
  G4Box* worldS = new G4Box("World", hx, hy, hz); 
      
  G4LogicalVolume* worldLV                         
    = new G4LogicalVolume(worldS, air, "World");
                                   
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      worldLV,               //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //
  // Tube
  //
  G4double rmin = 1.*m;
  hz = 10.*m;
  G4double phimin = 0.;
  G4double dphi = 360.*deg;
  
  G4double lambda = 16.77*cm;
  G4double airdr = 0.1*cm;

  fnlambda = 15;

  for (G4int i=0; i<fnlambda; ++i) {

    std::ostringstream stmp ;
    stmp << i ;
    //std::string stmp = std::to_string(i);
    G4String Name = "TubeAir"+(G4String)stmp.str();

    G4cout << "---------------------  NAME  " << Name << G4endl;
    // tube iron
    G4VSolid* tubeS = new G4Tubs("Tube", rmin+i*(lambda+airdr), rmin+(i+1)*lambda + i*airdr, hz, phimin, dphi);
    G4LogicalVolume* tubeLV = new G4LogicalVolume(tubeS, iron, "Tube");
    
    // tube air
    G4VSolid* tubeAirS = new G4Tubs(Name, rmin+(i+1)*lambda + i*airdr, rmin+(i+1)*(lambda+airdr), hz, phimin, dphi);
    G4LogicalVolume* tubeAirLV = new G4LogicalVolume(tubeAirS, air, Name);
    
    G4cout << rmin+i*(lambda+airdr) << ", " << rmin+(i+1)*lambda + i*airdr << ", " << rmin+(i+1)*lambda + i*airdr << ", "<< rmin+(i+1)*(lambda+airdr)<<G4endl;

    new G4PVPlacement(0, 
		      G4ThreeVector(),       //at (0,0,0)
		      tubeLV,                //its logical volume
		      "Tube",                //its name
		      worldLV,               //its mother  volume
		      false,                 //no boolean operation
		      i,                     //copy number
		      checkOverlaps);        //overlaps checking



    new G4PVPlacement(0, 
		      G4ThreeVector(),       //at (0,0,0)
		      tubeAirLV,                //its logical volume
		      Name,                //its name
		      worldLV,               //its mother  volume
		      false,                 //no boolean operation
		      i,                     //copy number
		      checkOverlaps);        //overlaps checking
    
    //tubeAirLV->SetSensitiveDetector(calorimeterSD);

  }

  
  //always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FCC0DetectorConstruction::ConstructSDandField()
{
  // G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  // 
  // Sensitive detectors
  //

  FCC0EmCalorimeterSD* calorimeterSD 
    = new FCC0EmCalorimeterSD("EmCalorimeterSD", "EmCalorimeterHitsCollection", fnlambda);
  for (G4int i=0; i<fnlambda; ++i) {

    std::ostringstream stmp ;
    stmp << i ;
    //std::string stmp = std::to_string(i);
    G4String Name = "TubeAir"+(G4String)stmp.str();

    //std::string stmp44 = std::to_string(i);
    //G4String Name = "TubeAir"+(G4String)stmp;
    SetSensitiveDetector(Name, calorimeterSD);
  }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
