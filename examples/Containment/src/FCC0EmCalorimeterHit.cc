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
/// \file FCC0EmCalorimeterHit.cc
/// \brief Implementation of the FCC0EmCalorimeterHit class
//

#include "FCC0EmCalorimeterHit.hh"

#include <G4UnitsTable.hh>
#include "G4SystemOfUnits.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//            G4Allocator<FCC0EmCalorimeterHit>* FCC0EmCalorimeterHitAllocator = 0;

G4ThreadLocal G4Allocator<FCC0EmCalorimeterHit>* FCC0EmCalorimeterHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FCC0EmCalorimeterHit::FCC0EmCalorimeterHit()
 : G4VHit(),
   fLayerNumber(-1),
   fEdep(0.),
   fPosition()

{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FCC0EmCalorimeterHit::~FCC0EmCalorimeterHit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FCC0EmCalorimeterHit::FCC0EmCalorimeterHit(const FCC0EmCalorimeterHit& /*right*/)
 : G4VHit() 
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const FCC0EmCalorimeterHit& 
FCC0EmCalorimeterHit::operator=(const FCC0EmCalorimeterHit& /*right*/)
{
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int FCC0EmCalorimeterHit::operator==(const FCC0EmCalorimeterHit& /*right*/) const
{
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FCC0EmCalorimeterHit::Print()
{
  //  if ( fEdep > 0. ) {
    G4cout << "EmCalorimeter hit in layer: " << fLayerNumber 
           << "  kinEnergy: " << std::setw(7) << G4BestUnit(fKinEnergy,"Energy")
	   << "   position [mm]: " <<  fPosition/mm
 	   << "   momentum : " <<  fMomentum
	   << G4endl;
    //}          
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


