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
/// \file FCC0ContainmentSD.cc
/// \brief Implementation of the FCC0ContainmentSD class
//

#include "FCC0ContainmentSD.hh"
#include "FCC0Analysis.hh"

#include <G4UnitsTable.hh>
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4TouchableHistory.hh"
#include "G4Step.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FCC0ContainmentSD::FCC0ContainmentSD(const G4String& name, 
                                     const G4String& hitsCollectionName,
				     const G4int& Nlayers)
 : G4VSensitiveDetector(name),
   fHitsCollection(0),
   fNlayers(Nlayers)
{
  collectionName.insert(hitsCollectionName);
  eventNum = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FCC0ContainmentSD::~FCC0ContainmentSD()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FCC0ContainmentSD::Initialize(G4HCofThisEvent* hce)
{

  fHitsCollection 
    = new FCC0ContainmentHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  G4int hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection ); 

  for (G4int i=0; i<fNlayers; i++ ) {
    FCC0ContainmentHit* newHit = new FCC0ContainmentHit();
    newHit->SetLayerNumber(i);
    fHitsCollection->insert(newHit);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool FCC0ContainmentSD::ProcessHits(G4Step* step,
                                      G4TouchableHistory* /*history*/)
{

  G4double edep = step->GetTotalEnergyDeposit();
  if ( edep==0. ) return false;     
  
  G4TouchableHistory* touchable
    = (G4TouchableHistory*)(step->GetPreStepPoint()->GetTouchable());
  G4VPhysicalVolume* layerPV = touchable->GetVolume();
  G4int layerNumber = layerPV->GetCopyNo();
  
  // Get hit accounting data for this layer
  FCC0ContainmentHit* hit = (*fHitsCollection)[layerNumber];
  if ( ! hit ) {
    G4cerr << "Cannot access hit " << layerNumber << G4endl;
    exit(1);
  }         
  
  // Add values
  hit->AddEdep(edep);

  return true;


  /*FCC0ContainmentHit* newHit = new FCC0ContainmentHit();


  G4StepPoint* preStepPoint = step->GetPreStepPoint();
  G4StepPoint* postStepPoint = step->GetPostStepPoint();

  G4TouchableHistory* touchable
    = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  G4VPhysicalVolume* motherPhysical = touchable->GetVolume(0); // mother
  G4int copyNo = motherPhysical->GetCopyNo();
  newHit->SetLayerNumber(copyNo);

  // Position
  G4ThreeVector position = preStepPoint->GetPosition();
  G4ThreeVector position_post = postStepPoint->GetPosition();
  G4Track* track         = step->GetTrack();
  G4ThreeVector momentum = track->GetMomentum();
  G4double kinEnergy     = track->GetKineticEnergy();
  G4double globalTime    = track->GetGlobalTime();

  //G4cout << "  " << position.mag()  << "    " << position_post.mag() << "   " << kinEnergy<< G4endl;
  
  if (position_post.mag() - position.mag() > 0.){

    newHit->SetLayerNumber(copyNo);
    newHit->SetPosition(position);
    newHit->SetMomentum(momentum);
    newHit->SetKinEnergy(kinEnergy);
    newHit->SetGlobalTime(globalTime);
    fHitsCollection->insert(newHit);
  }

  //G4cout << "------------------------------> layer num    " << copyNo <<  "    kinene   " << kinEnergy  << " momentum  "<< momentum << "  " << momentum.mag() << G4endl;
  else
    track->SetTrackStatus(fStopAndKill);
  //exit(1);
  return false;*/

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FCC0ContainmentSD::EndOfEvent(G4HCofThisEvent* /*hce*/)
{
  G4cout << "\n-------->" <<  fHitsCollection->GetName() 
         << ": in this event: " << G4endl;
  G4int nofHits = fHitsCollection->entries();
  //for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();

  // Loop over hits
  // and fill each value in appropriate histogram
  G4cout << " ==  nofHits  == " << nofHits << G4endl;
  G4double esum=0.;
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  for ( G4int i=0; i<nofHits; i++ )  {
    FCC0ContainmentHit* hit = (FCC0ContainmentHit*)(*fHitsCollection)[i];
    G4double edep = hit->GetEdep();
    analysisManager->FillNtupleIColumn(0, 0, eventNum);
    analysisManager->FillNtupleIColumn(0, 1, i);
    analysisManager->FillNtupleDColumn(0, 2, edep);
    analysisManager->AddNtupleRow(0);  
    //G4cout << " energy deposited in layer " << i << "   " << G4BestUnit(edep,"Energy") << G4endl; 
    esum+=edep;
  } 
  G4cout << " energy deposited sum "  << "   " << G4BestUnit(esum,"Energy") << G4endl; 

  eventNum+=1;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
