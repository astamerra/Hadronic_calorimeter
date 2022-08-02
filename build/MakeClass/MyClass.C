#define MyClass_cxx
#include "MyClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void MyClass::Loop()
{
//   In a ROOT session, you can do:
//      root> .L MyClass.C
//      root> MyClass t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   cout << " entries " << nentries << endl;

   Int_t evt_number = 0; 
   Double_t threshold = 0.00003;
   Int_t counter = 0; Int_t controller =0;
   vector<Int_t> Nhits_over_thre;
   
   TH1D *Nhits = new TH1D("Nhits", "Nhits", 100, 0, 1000);
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
     // cout << ientry << " " << jentry << endl;
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;           
      // cout << "entry " << jentry << " Evt " << EventID << " hit number " << HitID << " Edep " << Egap << endl;
      	if(EventID > evt_number) evt_number = EventID;
      
   }
   
   cout << evt_number << endl;
   Int_t hit_number = 0;
            //loop on events
   for(int i=0; i < evt_number+1; i++){
        hit_number = 0;
   	//loop on entries
   	for (Long64_t jentry=0; jentry<nentries;jentry++) {
     	 Long64_t ientry = LoadTree(jentry);
     	 // cout << ientry << " " << jentry << endl;
     	 if (ientry < 0) break;
         nb = fChain->GetEntry(jentry);   nbytes += nb;

         //counting number of hits per event
         if(EventID == i){
         hit_number++;
      		cout << " EventID " << i << " Hits " << hit_number << " edep " << Egap << endl;
      		//if(Egap > threshold) controller = 1;
      }
      }
     
      //if(controller == 1) counter++;
      //cout << hit_number << endl;
     Nhits_over_thre.push_back(hit_number);
   }
   
   cout << " Size " << Nhits_over_thre.size() << endl;
   for(int k=0; k< Nhits_over_thre.size(); k++){
   cout << Nhits_over_thre.at(k) << endl;
   Nhits->Fill(Nhits_over_thre.at(k));
   }
   Nhits->Draw();
   
   
   
}
