// ROOT macro file for plotting example B4 histograms
//
// Can be run from ROOT session:
// root[0] .x plotHisto.C

{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  // Draw histos filled by Geant4 simulation
  //

  // Open file filled by Geant4 simulation
  TFile f("B4_20GeV_Raf.root");

  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 800, 600);
  //c1->Divide(2,2);


  TH2D* hist1 = (TH2D*)f.Get("X-Z");
  hist1->GetYaxis()->SetTitle("X [Cell ID]");
  //hist1->GetXaxis()->SetTitle("Y [Cell ID]");
  hist1->GetXaxis()->SetTitle("Z [Layer ID]");
  hist1->SetTitle("");

  hist1->Draw("COLZ");


 gPad->SetGrid();
  gStyle->SetOptStat(false);
  
  }
