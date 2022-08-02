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
  TFile f("B4_10Gev.root");

  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  //c1->Divide(2,2);


  TH2D* hist1 = (TH2D*)f.Get("X-Z");
  hist1->GetXaxis()->SetTitle("X [Cell ID]");
  hist1->GetYaxis()->SetTitle("Z [Layer ID]");

  hist1->Draw("COLZ");

  std::cout<<"Integral " << hist1->Integral()<< std::endl;
  
  Double_t f_edep[100];
  Double_t nlayer[100];
  for(int i = 0; i < hist1->GetNbinsX(); i++){
  	//for(int j = 0; j < hist1->GetNbiny(); j++){
        	f_edep[i] = hist1->Integral(0,i,0,i) / hist1->Integral();
        	nlayer[i] = i+1;
  		if ((hist1->Integral(0,i,0,i) / hist1->Integral()) > 0.9) std::cout << i << std::endl;
  	
  }
  
  TCanvas* c2 = new TCanvas("c2", "", 20, 20, 1000, 1000);
  //TGraphErrors *gr_low = new TGraphErrors(points, energy_low, mean_low, err_energy_low, err_mean_low);
  TGraph *plot = new TGraph(100, nlayer, f_edep);
  plot->SetMarkerStyle(20);
  plot->GetXaxis()->SetTitle("Depth [layer ID]");
  plot->GetYaxis()->SetTitle("Fraction of deposited energy");
  plot->Draw("AP");
  
  
 gPad->SetGrid();
  
  
  }
