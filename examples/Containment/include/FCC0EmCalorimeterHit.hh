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
/// \file FCC0EmCalorimeterHit.hh
/// \brief Definition of the FCC0EmCalorimeterHit class
//

#ifndef FCC0EmCalorimeterHit_h
#define FCC0EmCalorimeterHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Types.hh"


class FCC0EmCalorimeterHit : public G4VHit
{
public:
  FCC0EmCalorimeterHit();
  virtual ~FCC0EmCalorimeterHit();
  FCC0EmCalorimeterHit(const FCC0EmCalorimeterHit& right);
  const FCC0EmCalorimeterHit& operator=(const FCC0EmCalorimeterHit& right);
  int operator==(const FCC0EmCalorimeterHit& right) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void* hit);
  
  virtual void Print();
  
  // add setter/getter methods
  void SetLayerNumber(G4int number) { fLayerNumber = number; }
  void AddEdep(G4double edep)       { fEdep += edep; }
  void SetPosition(G4ThreeVector position) { fPosition = position; }
  void SetMomentum(G4ThreeVector momentum) { fMomentum = momentum;}
  void SetKinEnergy(G4double kinEnergy)    {fKinEnergy = kinEnergy;}
  void SetGlobalTime(G4double globalTime)  {fGlobalTime = globalTime;}

  
  G4int    GetLayerNumber() const { return fLayerNumber;}
  G4double GetEdep() const        { return fEdep; }
  G4ThreeVector  GetPosition() const    { return fPosition; } 
  G4ThreeVector  GetMomentum() const    { return fMomentum; } 
  G4double GetKinEnergy() const { return fKinEnergy;}
  G4double GetGlobalTime() const { return fGlobalTime;}
  
private:
  // add data members
  G4int     fLayerNumber;
  G4double  fEdep;
  G4ThreeVector  fPosition;
  G4double fGlobalTime;
  G4double fKinEnergy;
  G4ThreeVector fMomentum;
};

typedef G4THitsCollection<FCC0EmCalorimeterHit> FCC0EmCalorimeterHitsCollection;

extern G4ThreadLocal G4Allocator<FCC0EmCalorimeterHit>* FCC0EmCalorimeterHitAllocator;

inline void* FCC0EmCalorimeterHit::operator new(size_t)
{
  if (! FCC0EmCalorimeterHitAllocator)
        FCC0EmCalorimeterHitAllocator = new G4Allocator<FCC0EmCalorimeterHit>;
  return (void*)FCC0EmCalorimeterHitAllocator->MallocSingle();
}

inline void FCC0EmCalorimeterHit::operator delete(void* hit)
{
  FCC0EmCalorimeterHitAllocator->FreeSingle((FCC0EmCalorimeterHit*) hit);
}

#endif


