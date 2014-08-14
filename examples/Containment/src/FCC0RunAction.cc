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
/// \file FCC0RunAction.cc
/// \brief Implementation of the FCC0RunAction class

#include "FCC0RunAction.hh"
#include "FCC0Analysis.hh"

#include "G4Run.hh"
#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FCC0RunAction::FCC0RunAction()
: G4UserRunAction(),
  fStoreRandom(false),
  fRestoreRandom(false),
  fRandomFileName("") 
{
  // Generic messenger
  // Define /B4/event commands using generic messenger class
  fMessenger 
    = new G4GenericMessenger(this, "/FCC0/random/", "Random number generator control");

  // Define /FCC0/random/* commands
  fMessenger
    ->DeclareProperty("setStoreRandom", 
                      fStoreRandom, 
                      "Activate/Inactivate storing random status option");

  fMessenger
    ->DeclareProperty("setRestoreRandom", 
                      fRestoreRandom, 
                      "Activate/Inactivate restoring random status option");

  fMessenger
    ->DeclareProperty("setRandomFileName", 
                      fRandomFileName, 
                      "Set random status file name");

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in B4Analysis.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  G4cout << "Using " << analysisManager->GetType() 
         << " analysis manager" << G4endl;

  // Creating histograms
  //
  analysisManager->CreateH1("leakage", "leakage", 100, 0., 100*GeV);

  // Creating ntuples
  //
  analysisManager->CreateNtuple("Leakage", "Leakage");
  analysisManager->CreateNtupleIColumn("Layer");   // column id = 0 
  analysisManager->CreateNtupleDColumn("Energy");    // column id = 1 
  analysisManager->FinishNtuple();

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FCC0RunAction::~FCC0RunAction()
{
  delete fMessenger;
  delete G4AnalysisManager::Instance();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FCC0RunAction::BeginOfRunAction(const G4Run* run)
{ 
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

  if ( fStoreRandom ) { 
    // Define a directory per run 
    std::ostringstream fileName;
    fileName << "beginOfRun" << run->GetRunID() << ".rndm";
    G4cout << "... storing random status in " << fileName << G4endl;
    CLHEP::HepRandom::saveEngineStatus(fileName.str().c_str());
    CLHEP::HepRandom::showEngineStatus();
  }
  
  if ( fRestoreRandom ) {
    G4cout << "... retrieving random status from " << fRandomFileName << G4endl;
    CLHEP::HepRandom::restoreEngineStatus(fRandomFileName.c_str());
    CLHEP::HepRandom::showEngineStatus();
  }  

  // Open an output file
  //
  G4String fileName = "FCC0";
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FCC0RunAction::EndOfRunAction(const G4Run* /*run*/)
{  
  // save histograms 
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
