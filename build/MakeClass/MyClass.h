//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 18 17:54:42 2022 by ROOT version 6.22/00
// from TTree B4/Hits Info
// found on file: B4.root
//////////////////////////////////////////////////////////

#ifndef MyClass_h
#define MyClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class MyClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           EventID;
   Int_t           HitID;
   Double_t        Eabs;
   Double_t        Egap;
   Int_t           ParticleID;
   Double_t        Xposition;
   Double_t        YPosition;
   Double_t        ZPosition;
   Double_t        Layer;
   Double_t        Row;
   Double_t        Column;
   Double_t        Glob_time;

   // List of branches
   TBranch        *b_EventID;   //!
   TBranch        *b_HitID;   //!
   TBranch        *b_Eabs;   //!
   TBranch        *b_Egap;   //!
   TBranch        *b_ParticleID;   //!
   TBranch        *b_Xposition;   //!
   TBranch        *b_YPosition;   //!
   TBranch        *b_ZPosition;   //!
   TBranch        *b_Layer;   //!
   TBranch        *b_Row;   //!
   TBranch        *b_Column;   //!
   TBranch        *b_Glob_time;   //!

   MyClass(TTree *tree=0);
   virtual ~MyClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MyClass_cxx
MyClass::MyClass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("B4.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("B4.root");
      }
      f->GetObject("B4",tree);

   }
   Init(tree);
}

MyClass::~MyClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MyClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MyClass::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MyClass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventID", &EventID, &b_EventID);
   fChain->SetBranchAddress("HitID", &HitID, &b_HitID);
   fChain->SetBranchAddress("Eabs", &Eabs, &b_Eabs);
   fChain->SetBranchAddress("Egap", &Egap, &b_Egap);
   fChain->SetBranchAddress("ParticleID", &ParticleID, &b_ParticleID);
   fChain->SetBranchAddress("Xposition", &Xposition, &b_Xposition);
   fChain->SetBranchAddress("YPosition", &YPosition, &b_YPosition);
   fChain->SetBranchAddress("ZPosition", &ZPosition, &b_ZPosition);
   fChain->SetBranchAddress("Layer", &Layer, &b_Layer);
   fChain->SetBranchAddress("Row", &Row, &b_Row);
   fChain->SetBranchAddress("Column", &Column, &b_Column);
   fChain->SetBranchAddress("Glob_time", &Glob_time, &b_Glob_time);
   Notify();
}

Bool_t MyClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MyClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MyClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MyClass_cxx
