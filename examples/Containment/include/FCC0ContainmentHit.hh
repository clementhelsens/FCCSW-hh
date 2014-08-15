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
/// \file FCC0ContainmentHit.hh
/// \brief Definition of the FCC0ContainmentHit class
//

#ifndef FCC0ContainmentHit_h
#define FCC0ContainmentHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Types.hh"


class FCC0ContainmentHit : public G4VHit
{
public:
  FCC0ContainmentHit();
  virtual ~FCC0ContainmentHit();
  FCC0ContainmentHit(const FCC0ContainmentHit& right);
  const FCC0ContainmentHit& operator=(const FCC0ContainmentHit& right);
  int operator==(const FCC0ContainmentHit& right) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void* hit);
  
  virtual void Print();
  
  // add setter/getter methods
  void SetLayerNumber(G4int number) { fLayerNumber = number; }
  void AddEdep(G4double edep)       { fEdep += edep; }
  
  G4int    GetLayerNumber() const { return fLayerNumber;}
  G4double GetEdep() const        { return fEdep; }
  
private:
  // add data members
  G4int     fLayerNumber;
  G4double  fEdep;
};

typedef G4THitsCollection<FCC0ContainmentHit> FCC0ContainmentHitsCollection;

extern G4ThreadLocal G4Allocator<FCC0ContainmentHit>* FCC0ContainmentHitAllocator;

inline void* FCC0ContainmentHit::operator new(size_t)
{
  if (! FCC0ContainmentHitAllocator)
        FCC0ContainmentHitAllocator = new G4Allocator<FCC0ContainmentHit>;
  return (void*)FCC0ContainmentHitAllocator->MallocSingle();
}

inline void FCC0ContainmentHit::operator delete(void* hit)
{
  FCC0ContainmentHitAllocator->FreeSingle((FCC0ContainmentHit*) hit);
}

#endif


