#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <TGraph.h>
#include <TString.h>
#include "TStyle.h"
using namespace std;


// ROOT macro file for plotting example B4 histograms 
// 
// Can be run from ROOT session:
// root[0] .x plotHisto.C



void setTDRStyle() {
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

// For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

// For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

// For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);
  
// For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);

  tdrStyle->SetEndErrorSize(2);
  // tdrStyle->SetErrorMarker(20);
  //tdrStyle->SetErrorX(0.);
  
  tdrStyle->SetMarkerStyle(20);
  
//For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

//For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

// For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Float_t x = 0);
  // tdrStyle->SetStatY(Float_t y = 0);

// Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.16);
  tdrStyle->SetPadRightMargin(0.02);

// For the Global title:

  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

// For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.04, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.25);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.03, "XYZ");

// For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

// Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

// Postscript options:
  tdrStyle->SetPaperSize(20.,20.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->SetHatchesLineWidth(5);
  tdrStyle->SetHatchesSpacing(0.05);

  tdrStyle->cd();

}


void readSameEdep() {

 setTDRStyle();
 
 Double_t eBeam20 = 40000.;
 const double lambda_I = 16.78;

 
 Double_t bin100[71], bin80[71], bin50[71];
 Double_t edep100[71], edep80[71], edep50[71];
 Double_t edep_cum100[71], edep_cum80[71], edep_cum50[71];
 Double_t evt100[1000], evt80[1000], evt50[1000];
 
 string filename100 = "eDep_60GeV_100L_1x1m.txt";
 string filename80 = "correctMeshSize_eDep_60GeV_80L_1x1m_200evt.txt";
 string filename50 = "correctMeshSize_eDep_60GeV_50L_1x1m_200evt.txt";
 
 
 //100 layers
 
	vector<vector<string>> content100;
	vector<string> row100;
	string line100, word100;
	
	fstream file100 (filename100);
	if(file100.is_open()){
		cout << "File is open" << endl;
		while(getline(file100, line100)){
			row100.clear();
			stringstream str(line100);
				
			
			while(getline(str, word100, ',')){
				row100.push_back(word100);
				
			} 
			content100.push_back(row100);
			//std::cout<<content<<endl;
		}
	}else {
		cout<< "could not open the file" << endl;
	}


	//conversion from string to double
	
	
		for(int i=3; i<content100.size(); i++) {
	
		//std::cout<< content[3][i]<<endl;
		
		//conversion from string to TString
		TString l(content100[i][2]); 
		TString e(content100[i][3]);
		TString v(content100[i][5]);
		
		//conversion frotm TString to Double_t
		bin100[i-3]=l.Atof();  
		edep100[i-3]=e.Atof(); 
		evt100[i-3]=v.Atof();
		
		
		
		edep100[i-3] = edep100[i-3] / evt100[i-3] ;

	
	}
	
	
	 //80 layers
 
	vector<vector<string>> content80;
	vector<string> row80;
	string line80, word80;
	
	fstream file80 (filename80);
	if(file80.is_open()){
		cout << "File is open" << endl;
		while(getline(file80, line80)){
			row80.clear();
			stringstream str(line80);
				
			
			while(getline(str, word80, ',')){
				row80.push_back(word80);
				
			} 
			content80.push_back(row80);
			//std::cout<<content<<endl;
		}
	}else {
		cout<< "could not open the file" << endl;
	}


	//conversion from string to double
	
	
		for(int i=3; i<content80.size(); i++) {
	
		//std::cout<< content[3][i]<<endl;
		
		//conversion from string to TString
		TString l(content80[i][2]); 
		TString e(content80[i][3]);
		TString v(content80[i][5]);
		
		//conversion frotm TString to Double_t
		bin80[i-3]=l.Atof();  
		edep80[i-3]=e.Atof(); 
		evt80[i-3]=v.Atof();
		
		
		
		edep80[i-3] = edep80[i-3] / evt80[i-3] ;

	
	}
	
	
	//50 layers
 
	vector<vector<string>> content50;
	vector<string> row50;
	string line50, word50;
	
	fstream file50 (filename50);
	if(file50.is_open()){
		cout << "File is open" << endl;
		while(getline(file50, line50)){
			row50.clear();
			stringstream str(line50);
				
			
			while(getline(str, word50, ',')){
				row50.push_back(word50);
				
			} 
			content50.push_back(row50);
			//std::cout<<content<<endl;
		}
	}else {
		cout<< "could not open the file" << endl;
	}


	//conversion from string to double
	
	
		for(int i=3; i<content50.size(); i++) {
	
		//std::cout<< content[3][i]<<endl;
		
		//conversion from string to TString
		TString l(content50[i][2]); 
		TString e(content50[i][3]);
		TString v(content50[i][5]);
		
		//conversion frotm TString to Double_t
		bin50[i-3]=l.Atof();  
		edep50[i-3]=e.Atof(); 
		evt50[i-3]=v.Atof();
		
		
		
		edep50[i-3] = edep50[i-3] / evt50[i-3] ;

	
	}
 
	
	edep_cum100[0] = edep100[0];
	edep_cum80[0] = edep80[0];
	edep_cum50[0] = edep50[0];
	
	
	for(int i=0; i<71; i++){	
		if( i!= 0) {
			edep_cum100[i] = (edep100[i] + edep_cum100[i-1]);
			edep_cum80[i] = (edep80[i] + edep_cum80[i-1]);
			edep_cum50[i] = (edep50[i] + edep_cum50[i-1]);
			
			
			bin100[i] = (i+1) / lambda_I;
			bin80[i] = (i+1) / lambda_I;
			bin50[i] = (i+1) / lambda_I;
			
			//bin20[i] = (i+1);
			//bin40[i] = (i+1);
			//bin60[i] = (i+1);
			
			cout << bin100[i] << " " << edep_cum100[i] << endl;
		
		}
	}
	
	
	
	for(int i=0;i<71;i++){
		edep_cum100[i] = edep_cum100[i] / eBeam20;
		edep_cum80[i] = edep_cum80[i] / eBeam20;
		edep_cum50[i] = edep_cum50[i] / eBeam20;
		
	}


	TCanvas* c1 = new TCanvas("c1", "", 20, 20, 800, 600);
	
	TGraph * g100 = new TGraph(71, bin100, edep_cum100);
	g100->SetMarkerStyle(20);
	g100->SetMarkerColor(6);
	
	TGraph * g80 = new TGraph(71, bin80, edep_cum80);
	g80->SetMarkerStyle(20);
	g80->SetMarkerColor(4);
	
	TGraph * g50 = new TGraph(71, bin50, edep_cum50);
	g50->SetMarkerStyle(20);
	g50->SetMarkerColor(2);
	
	
	TMultiGraph * mg = new TMultiGraph();
	mg->SetTitle("Transversal shower development;R (cm); Energy deposited (MeV)");
	
	mg->Add(g100); 
	mg->Add(g80); 
	mg->Add(g50); 
	//mg->Add(g10); 
	
	mg->Draw("APL");
	
	TLegend *legend2 = new TLegend(0.1,0.7,0.48,0.9);

	//legend2->AddEntry(g10,"10 GeV");
   	legend2->AddEntry(g100,"100 Layers");
  	legend2->AddEntry(g80,"80 Layers");
   	legend2->AddEntry(g50,"50 Layers");
 	legend2->Draw();

	gPad->SetGrid();
}
