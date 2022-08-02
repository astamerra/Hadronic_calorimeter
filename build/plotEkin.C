{
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  
  // Open file filled by Geant4 simulation
  TFile f("B4.root");

  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  
  TH1D* hist1 = (TH1D*)f.Get("Ekin_vertex");
  
  hist1->GetXaxis()->SetTitle("Kinetic energy (MeV)");
  hist1->GetYaxis()->SetTitle("Entries");
  //gPad->SetLogy();

  Double_t integral = hist1->Integral();
  
  //hist1->Scale(1/integral);
  hist1->Draw("");

  std::cout<<"Integral width " << hist1->Integral("width")<< std::endl;
  std::cout<<"Integral "<<hist1->Integral()<<std::endl;
  std::cout<<"Entries " << hist1->GetEntries()<< std::endl;
  
}
