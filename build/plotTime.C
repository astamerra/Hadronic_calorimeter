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
  //TFile f("B4_edepLayer.root");
  TFile f("B4.root");
  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(2);
  
  // Draw Eabs histogram in the pad 1
  c1->cd(1);
  TH2D* hist1 = (TH2D*)f.Get("Glob_Time_layer");
  hist1->SetTitle("60 GeV Pion beam - 1x1 m^{2} transverse size");
  hist1->GetXaxis()->SetTitle("Layer ID");
  hist1->GetYaxis()->SetTitle("Time (ns)");
  hist1->Draw("COLZ");
  
 // TH2D* hist_gap = (TH2D*)f.Get("Egap_c");
  
  // Draw Labs histogram in the pad 2
  c1->cd(2);
  TH1D* Profile = (TH1D*)(hist1->ProfileX("Profile", 1, -1, "o"));
  Profile->GetYaxis()->SetTitle("Time (ns)");
  Profile->Draw();
  
   TCanvas* c = new TCanvas("c", "", 20, 20, 1000, 1000);
  c->Divide(2);
  
  // Draw Eabs histogram in the pad 1
  c->cd(1);
  TH2D* hist = (TH2D*)f.Get("Loc_Time_layer");
  hist->SetTitle("60 GeV Pion beam - 1x1 m^{2} transverse size");
  hist->GetXaxis()->SetTitle("Layer ID");
  hist->GetYaxis()->SetTitle("Time (ns)");
  hist->Draw("COLZ");
  
 // TH2D* hist_gap = (TH2D*)f.Get("Egap_c");
  
  // Draw Labs histogram in the pad 2
  c->cd(2);
  TH1D* Profile1 = (TH1D*)(hist->ProfileX("Profile1", 1, -1, "o"));
  Profile1->GetYaxis()->SetTitle("Time (ns)");
  Profile1->Draw();
 

}  
