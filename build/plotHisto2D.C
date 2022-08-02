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
  TH2D* hist1 = (TH2D*)f.Get("Eabs_l");
  hist1->SetTitle("60 GeV Pion beam - 1x1 m^{2} transverse size");
  hist1->GetXaxis()->SetTitle("Cell Number");
  hist1->GetYaxis()->SetTitle("Energy deposited (MeV)");
  hist1->Draw("COLZ");
  
  TH2D* hist_gap = (TH2D*)f.Get("Egap_l");
  
  // Draw Labs histogram in the pad 2
  c1->cd(2);
  TH1D* Profile = (TH1D*)(hist1->ProfileX("Profile", 1, -1, "o"));
  Profile->GetYaxis()->SetTitle("Deposited energy (MeV)");
  Profile->Draw();
 
  TH1D* ProfileGap = (TH1D*)(hist_gap->ProfileX("ProfileGap", 1, -1, "o"));
  
  const int n_l=50;
  const int n_r=50;
 
 Double_t edep_cum[n_r], err_layer[n_r], err_edep[n_r];
  Double_t nlayer[n_r];
  
  //Double_t edep_cum[n_l], err_layer[n_l], err_edep[n_l];
  //Double_t nlayer[n_l];
  
  std::cout<<Profile->GetNbinsX()<<std::endl;
  std::cout<<Profile->Integral() + ProfileGap->Integral()<<std::endl;
  std::cout<<ProfileGap->Integral()<<std::endl;
  for(int i = 0; i < n_r; i++){
	//edep_cum[i] = (Profile->Integral(0,i)) / (Profile->Integral());
	edep_cum[i] = ( Profile->Integral(0,i) + ProfileGap->Integral(0,i) ) / 10000.;
	nlayer[i] = i+1;
	err_edep[i] = 0;
	err_layer[i] = 0;
  	//std::cout<<(Profile->Integral(i,i+1)) / (Profile->Integral())<<std::endl;
  }
  /*
    for(int i = 0; i < n_l; i++){
        edep_cum[i] = (Profile->Integral(0,i)) / (Profile->Integral(0,50));
	//edep_cum[n_l-1-i] = (Profile->Integral(0,i)) / (Profile->Integral(0,50));
	//edep_cum[i] = Profile->Integral(0,i) / 60000.;
	nlayer[i] = i+1;
	err_edep[i] = 0;
	err_layer[i] = 0;
  	//std::cout<<(Profile->Integral(i,i+1)) / (Profile->Integral())<<std::endl;
  }
  */
  TCanvas* c2 = new TCanvas("c2", "", 20, 20, 1000, 1000);
  //TGraphErrors *gr_low = new TGraphErrors(points, energy_low, mean_low, err_energy_low, err_mean_low);
  TGraphErrors *plot = new TGraphErrors(n_r, nlayer, edep_cum, err_layer, err_edep);
  plot->SetMarkerStyle(20);
  plot->GetXaxis()->SetTitle("Depth [column ID]");
  plot->GetYaxis()->SetTitle("Fraction of deposited energy");
  plot->Draw("APL");
  
  
 gPad->SetGrid();
}  
