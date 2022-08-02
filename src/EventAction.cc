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
/// \file EventAction.cc
/// \brief Implementation of the B4c::EventAction class



#include "EventAction.hh"
#include "CalorimeterSD.hh"
#include "CalorHit.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

namespace B4c
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CalorHitsCollection*
EventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  auto hitsCollection
    = static_cast<CalorHitsCollection*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::PrintEventStatistics(
                              G4double absoEdep, G4double absoTrackLength,
                              G4double gapEdep, G4double gapTrackLength) const
{
  // print event statistics
  G4cout
     << "   Absorber: total energy: "
     << std::setw(7) << G4BestUnit(absoEdep, "Energy")
     << "       total track length: "
     << std::setw(7) << G4BestUnit(absoTrackLength, "Length")
     << G4endl
     << "        Gap: total energy: "
     << std::setw(7) << G4BestUnit(gapEdep, "Energy")
     << "       total track length: "
     << std::setw(7) << G4BestUnit(gapTrackLength, "Length")
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  // Get hits collections IDs (only once)
  if ( fAbsHCID == -1 ) {
    fAbsHCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("AbsorberHitsCollection");
    fGapHCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("GapHitsCollection");
  }

  // Get hits collections
  auto absoHC = GetHitsCollection(fAbsHCID, event);
  auto gapHC = GetHitsCollection(fGapHCID, event);

  // Get hit with total values
  auto absoHit = (*absoHC)[absoHC->entries()-1];
  auto gapHit = (*gapHC)[gapHC->entries()-1];

  G4int NHits_overThr = 0;
  G4double ave_Ar = 30 * eV;
  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;

    // DEBUG //
    /*
    G4int nHits = absoHC->entries();
    G4cout << " number of Hits: " << nHits << G4endl;
    for(G4int i=0; i< nHits; i++ ){
      auto absoHit_cell = (*absoHC)[i];
      auto gapHit_cell = (*gapHC)[i];
      //G4cout << " Edep abs layer " << i <<" : "<<  G4BestUnit(absoHit_cell->GetEdep(), "Energy") << G4endl;
      //G4cout << " Edep gap layer " << i <<" : "<<  G4BestUnit(gapHit_cell->GetEdep(), "Energy") << G4endl;
      G4cout << " Event " <<eventID<<" Hit n. " << i
        <<" Row: "<<gapHit_cell->GetRowID()<<" Column: "<<gapHit_cell->GetColumnID()<<" Layer: "<<gapHit_cell->GetLayerID()
        <<" Position: "<<G4BestUnit(gapHit_cell->GetPos(), "Length")
        <<" Global Time: "<<G4BestUnit(gapHit_cell->GetTime(), "Time")
        //<<" Rotation: "<<gapHit_cell->GetRot()
        <<" E. dep. : "<<  G4BestUnit(gapHit_cell->GetEdep(), "Energy") << G4endl;

   } */
    PrintEventStatistics(
      absoHit->GetEdep(), absoHit->GetTrackLength(),
      gapHit->GetEdep(), gapHit->GetTrackLength());
}

    // Fill histograms, ntuple
    //
    // get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    //TTree *tree = new TTree("tree", "Events and Hits");
    
   // analysisManager->AddNtupleRow();
    
    G4int nHits = absoHC->entries();
    G4int nhits = 0;
    //G4cout << " number of Hits: " << nHits << G4endl;
    for(G4int i=0; i< nHits; i++ ){
      auto absoHit_cell = (*absoHC)[i];
      auto gapHit_cell = (*gapHC)[i];
      //G4cout << " Edep abs layer " << i <<" : "<<  G4BestUnit(absoHit_cell->GetEdep(), "Energy") << G4endl;
      //G4cout << " Edep gap layer " << i <<" : "<<  G4BestUnit(gapHit_cell->GetEdep(), "Energy") << G4endl;
     /* G4cout << " Event " <<eventID<<" Hit n. " << i
        <<" Row: "<<gapHit_cell->GetRowID()<<" Column: "<<gapHit_cell->GetColumnID()<<" Layer: "<<gapHit_cell->GetLayerID()
        <<" Position: "<<G4BestUnit(gapHit_cell->GetPos(), "Length")
        <<" Global Time: "<<G4BestUnit(gapHit_cell->GetTime(), "Time")
        //<<" Rotation: "<<gapHit_cell->GetRot()
        <<" E. dep. : "<<  G4BestUnit(gapHit_cell->GetEdep(), "Energy") << 
        " PDG Particle : "<< gapHit_cell->GetParticleID() << G4endl;
       */ 
        
        if(gapHit_cell->GetLayerID() != -1){
        
        nhits++;       
        
        analysisManager->FillNtupleIColumn(0, 0, eventID);
        analysisManager->FillNtupleIColumn(0, 1, i);
        
        analysisManager->FillNtupleDColumn(0, 2, absoHit_cell->GetEdep());
        analysisManager->FillNtupleDColumn(0, 3, gapHit_cell->GetEdep());
        
        analysisManager->FillNtupleIColumn(0, 4, gapHit_cell->GetParticleID());
        
        analysisManager->FillNtupleDColumn(0, 5, (gapHit_cell->GetPos())[0]);
        analysisManager->FillNtupleDColumn(0, 6, (gapHit_cell->GetPos())[1]);
        analysisManager->FillNtupleDColumn(0, 7, (gapHit_cell->GetPos())[2]);
        
        
        analysisManager->FillNtupleDColumn(0, 8, gapHit_cell->GetLayerID());
        analysisManager->FillNtupleDColumn(0, 9, gapHit_cell->GetRowID());
        analysisManager->FillNtupleDColumn(0, 10, gapHit_cell->GetColumnID());
        
        analysisManager->FillNtupleDColumn(0, 11, gapHit_cell->GetTime());
        
        analysisManager->AddNtupleRow(0);
        
        // tree->Branch("EvtID", &eventID, "EvtID/I");
        // tree->Branch("HitID", &i, "HitID/I");
	// tree->Branch("Eabs", &(absoHit_cell->GetEdep()), "Eabs/D");
	// tree->Branch("Egap", &(gapHit_cell->GetEdep()), "Egap/D");
       // G4cout << " number of Hits: " << i << G4endl;
        }
        
        if(gapHit_cell->GetEdep() > ave_Ar) NHits_overThr++;
        
        }
 	
 	G4cout << " Event " <<eventID<<" Hit n. " << nhits << G4endl;
  // fill histograms
  //analysisManager->FillH1(0, absoHit->GetEdep());
  //analysisManager->FillH1(1, gapHit->GetEdep());
  //analysisManager->FillH1(2, absoHit->GetTrackLength());
  //analysisManager->FillH1(3, gapHit->GetTrackLength());

  analysisManager->FillH1(4, NHits_overThr);


	
	
}
      
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
