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
/// \file FCC0ContainmentHit.cc
/// \brief Implementation of the FCC0ContainmentHit class
//

#include "FCC0ContainmentHit.hh"

#include <G4UnitsTable.hh>
#include "G4SystemOfUnits.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//            G4Allocator<FCC0ContainmentHit>* FCC0ContainmentHitAllocator = 0;

G4ThreadLocal G4Allocator<FCC0ContainmentHit>* FCC0ContainmentHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FCC0ContainmentHit::FCC0ContainmentHit()
 : G4VHit(),
   fLayerNumber(-1),
   fEdep(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FCC0ContainmentHit::~FCC0ContainmentHit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FCC0ContainmentHit::FCC0ContainmentHit(const FCC0ContainmentHit& /*right*/)
 : G4VHit() 
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const FCC0ContainmentHit& 
FCC0ContainmentHit::operator=(const FCC0ContainmentHit& /*right*/)
{
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int FCC0ContainmentHit::operator==(const FCC0ContainmentHit& /*right*/) const
{
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FCC0ContainmentHit::Print()
{
  //  if ( fEdep > 0. ) {
    G4cout << "Containment hit in layer: " << fLayerNumber 
           << "  Edep: " << std::setw(7) << G4BestUnit(fEdep,"Energy")
	   << G4endl;
    //}          
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


