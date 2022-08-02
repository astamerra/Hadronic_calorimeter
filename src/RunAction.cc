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
//
/// \file RunAction.cc
/// \brief Implementation of the B4::RunAction class

#include "RunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

namespace B4
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);

  // Create analysis manager
  // The choice of the output format is done via the specified
  // file extension.
  auto analysisManager = G4AnalysisManager::Instance();

  // Create directories
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
    // Note: merging ntuples is available only with Root output

  //G4int  fNofLayers = 100;     // number of layers
  

  // Book histograms, ntuple
  //

  // Creating histograms
  analysisManager->CreateH1("Eabs","Edep in absorber", 1000, 0., 30*GeV); //Hist ID 0
  analysisManager->CreateH1("Egap","Edep in gap", 1000, 0., 10*MeV); //Hist ID 1
  analysisManager->CreateH1("Labs","trackL in absorber", 10000, 0., 100*m); //Hist ID 2
  analysisManager->CreateH1("Lgap","trackL in gap", 10000, 0., 10*m); //Hist ID 3
  analysisManager->CreateH1("nHits","Number of hits", B4c::fNofPixelsXY*B4c::fNofPixelsXY*B4c::fNofLayers, 0, B4c::fNofPixelsXY*B4c::fNofPixelsXY*B4c::fNofLayers); //Hist ID 4

  // Creating ntuple per event
  //
  analysisManager->CreateNtuple("Event", "Info per event per hit");
  
  analysisManager->CreateNtupleIColumn("EventID");		//ID 0
  analysisManager->CreateNtupleIColumn("HitID");		//ID 1
  
  analysisManager->CreateNtupleDColumn("Eabs"); 		//ID 2
  analysisManager->CreateNtupleDColumn("Egap");		//ID 3
  
  analysisManager->CreateNtupleIColumn("ParticleID");	//ID 4
  
  analysisManager->CreateNtupleDColumn("Xposition");		//ID 5
  analysisManager->CreateNtupleDColumn("YPosition");		//ID 6
  analysisManager->CreateNtupleDColumn("ZPosition");		//ID 7
  
  analysisManager->CreateNtupleDColumn("Layer");		//ID 8
  analysisManager->CreateNtupleDColumn("Row");		//ID 9
  analysisManager->CreateNtupleDColumn("Column");		//ID 10
  
  analysisManager->CreateNtupleDColumn("Glob_time");		//ID 11

  analysisManager->FinishNtuple(0);
  
  
  // Creating ntuple per step
  //
  analysisManager->CreateNtuple("Step", "Info per step");
  
  analysisManager->CreateNtupleIColumn("EventID");		//ID 0
  analysisManager->CreateNtupleIColumn("TrackID");		//ID 1
  analysisManager->CreateNtupleIColumn("StepID");		//ID 2
  analysisManager->CreateNtupleIColumn("CellID");		//ID 3
  
  
  analysisManager->CreateNtupleDColumn("Edep"); 		//ID 4

  
  analysisManager->CreateNtupleIColumn("ParticleID");	//ID 5
  
  analysisManager->CreateNtupleDColumn("Xposition");		//ID 6
  analysisManager->CreateNtupleDColumn("YPosition");		//ID 7
  analysisManager->CreateNtupleDColumn("ZPosition");		//ID 8
  
  analysisManager->CreateNtupleIColumn("Layer");		//ID 9
  analysisManager->CreateNtupleIColumn("Row");		//ID 10
  analysisManager->CreateNtupleIColumn("Column");		//ID 11
  
  analysisManager->CreateNtupleDColumn("Glob_time");		//ID 12

  analysisManager->FinishNtuple(1);
  
  
  //create TTree
  
  
  //tree->Branch
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "B4.root";
  // Other supported output types:
  // G4String fileName = "B4.csv";
  // G4String fileName = "B4.hdf5";
  // G4String fileName = "B4.xml";
  analysisManager->OpenFile(fileName);
  G4cout << "Using " << analysisManager->GetType() << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // print histogram statistics
  //
  auto analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->GetH1(1) ) {
    G4cout << G4endl << " ----> print histograms statistic ";
    if(isMaster) {
      G4cout << "for the entire run " << G4endl << G4endl;
    }
    else {
      G4cout << "for the local thread " << G4endl << G4endl;
    }

    G4cout << " EAbs : mean = "
       << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy")
       << " rms = "
       << G4BestUnit(analysisManager->GetH1(0)->rms(),  "Energy") << G4endl;

    G4cout << " EGap : mean = "
       << G4BestUnit(analysisManager->GetH1(1)->mean(), "Energy")
       << " rms = "
       << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Energy") << G4endl;

    G4cout << " LAbs : mean = "
      << G4BestUnit(analysisManager->GetH1(2)->mean(), "Length")
      << " rms = "
      << G4BestUnit(analysisManager->GetH1(2)->rms(),  "Length") << G4endl;

    G4cout << " LGap : mean = "
      << G4BestUnit(analysisManager->GetH1(3)->mean(), "Length")
      << " rms = "
      << G4BestUnit(analysisManager->GetH1(3)->rms(),  "Length") << G4endl;
  }

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
