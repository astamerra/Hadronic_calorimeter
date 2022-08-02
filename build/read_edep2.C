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

void read_edep2()
{

       setTDRStyle();
       const double lambda_I = 16.78;

	Double_t bin60[71], bin40[71], bin20[71], bin10[71];
	Double_t edep60[71], edep40[71], edep20[71], edep10[71];
	Double_t edep_cum60[71], edep_cum40[71], edep_cum20[71], edep_cum10[71];
	Double_t evt60[1000], evt40[1000], evt20[1000], evt10[1000];
	
	
	Double_t eBeam60 = 60000.;
	Double_t eBeam40 = 40000.;
	Double_t eBeam20 = 20000.;
	Double_t eBeam10 = 10000.;

	//reading from file
	
	
	//string filename60 = "correctMeshSize_eDep_60GeV_100L_1x1m_2500evt.txt";
	//string filename40 = "eDep_40GeV_100L_1x1m_2500evt.txt";
	//string filename20 = "eDep_20GeV_100L_1x1m_2500evt.txt";
	//string filename10 = "eDep_10GeV.txt";
	
	//string filename60 = "eDep_60GeV.txt";
	//string filename40 = "eDep_40GeV.txt";
	//string filename20 = "eDep_20GeV.txt";
	string filename10 = "eDep_10GeV.txt";
	
	string filename60 = "correctMeshSize_eDep_60GeV_80L_1x1m_200evt.txt";
	string filename40 = "correctMeshSize_eDep_40GeV_80L_1x1m_200evt.txt";
	string filename20 = "correctMeshSize_eDep_20GeV_80L_1x1m_200evt.txt";
	
	
	//60 GeV
	vector<vector<string>> content60;
	vector<string> row60;
	string line60, word60;
	
	fstream file60 (filename60);
	if(file60.is_open()){
		cout << "File is open" << endl;
		while(getline(file60, line60)){
			row60.clear();
			stringstream str(line60);
				
			
			while(getline(str, word60, ',')){
				row60.push_back(word60);
				
			} 
			content60.push_back(row60);
			//std::cout<<content<<endl;
		}
	}else {
		cout<< "could not open the file" << endl;
	}


	//conversion from string to double
	
	
		for(int i=3; i<content60.size(); i++) {
	
		//std::cout<< content[3][i]<<endl;
		
		//conversion from string to TString
		TString l(content60[i][2]); 
		TString e(content60[i][3]);
		TString v(content60[i][5]);
		
		//conversion frotm TString to Double_t
		bin60[i-3]=l.Atof();  
		edep60[i-3]=e.Atof(); 
		evt60[i-3]=v.Atof();
		
		
		
		edep60[i-3] = edep60[i-3] / evt60[i-3] ;
		
		
	
	}
	
	//40 GeV
	vector<vector<string>> content40;
	vector<string> row40;
	string line40, word40;
	
	fstream file40 (filename40);
	if(file40.is_open()){
		cout << "File is open" << endl;
		while(getline(file40, line40)){
			row40.clear();
			stringstream str(line40);
				
			
			while(getline(str, word40, ',')){
				row40.push_back(word40);
				
			} 
			content40.push_back(row40);
			//std::cout<<content<<endl;
		}
	}else {
		cout<< "could not open the file" << endl;
	}


	//conversion from string to double
	
	
		for(int i=3; i<content40.size(); i++) {
	
		//std::cout<< content[3][i]<<endl;
		
		//conversion from string to TString
		TString l(content40[i][2]); 
		TString e(content40[i][3]);
		TString v(content40[i][5]);
		
		//conversion frotm TString to Double_t
		bin40[i-3]=l.Atof();  
		edep40[i-3]=e.Atof(); 
		evt40[i-3]=v.Atof();
		
		edep40[i-3] = edep40[i-3] / evt40[i-3] ;
	
	}
	
	
	//20 GeV
	vector<vector<string>> content20;
	vector<string> row20;
	string line20, word20;
	
	fstream file20 (filename20);
	if(file20.is_open()){
		cout << "File is open" << endl;
		while(getline(file20, line20)){
			row20.clear();
			stringstream str(line20);
				
			
			while(getline(str, word20, ',')){
				row20.push_back(word20);
				
			} 
			content20.push_back(row20);
			//std::cout<<content<<endl;
		}
	}else {
		cout<< "could not open the file" << endl;
	}


	//conversion from string to double
	
	
		for(int i=3; i<content20.size(); i++) {
	
		//std::cout<< content[3][i]<<endl;
		
		//conversion from string to TString
		TString l(content20[i][2]); 
		TString e(content20[i][3]);
		TString v(content20[i][5]);
		
		//conversion frotm TString to Double_t
		bin20[i-3]=l.Atof();  
		edep20[i-3]=e.Atof(); 
		evt20[i-3]=v.Atof();
		
		edep20[i-3] = edep20[i-3] / evt20[i-3] ;
		
		//cout<< edep20[i] << endl;
	
	}
	
	
	//10 GeV
	vector<vector<string>> content10;
	vector<string> row10;
	string line10, word10;
	
	fstream file10 (filename10);
	if(file10.is_open()){
		cout << "File is open" << endl;
		while(getline(file10, line10)){
			row10.clear();
			stringstream str(line10);
				
			
			while(getline(str, word10, ',')){
				row10.push_back(word10);
				
			} 
			content10.push_back(row10);
			//std::cout<<content<<endl;
		}
	}else {
		cout<< "could not open the file" << endl;
	}


	//conversion from string to double
	
	
		for(int i=3; i<content10.size(); i++) {
	
		//std::cout<< content[3][i]<<endl;
		
		//conversion from string to TString
		TString l(content10[i][2]); 
		TString e(content10[i][3]);
		TString v(content10[i][5]);
		
		//conversion frotm TString to Double_t
		bin10[i-3]=l.Atof();  
		edep10[i-3]=e.Atof(); 
		evt10[i-3]=v.Atof();
		
		edep10[i-3] = edep10[i-3] / evt10[i-3] ;
	
	}
	
	
	cout << edep20[0] <<endl;
	
	edep_cum60[0] = edep60[0];
	edep_cum40[0] = edep40[0];
	edep_cum20[0] = edep20[0];
	edep_cum10[0] = edep10[0];
	
	for(int i=0; i<71; i++){	
		if( i!= 0) {
			edep_cum60[i] = (edep60[i] + edep_cum60[i-1]);
			edep_cum40[i] = (edep40[i] + edep_cum40[i-1]);
			edep_cum20[i] = (edep20[i] + edep_cum20[i-1]);
			edep_cum10[i] = (edep10[i] + edep_cum10[i-1]);
			
			bin20[i] = (i+1) / lambda_I;
			bin40[i] = (i+1) / lambda_I;
			bin60[i] = (i+1) / lambda_I;
			
			//bin20[i] = (i+1);
			//bin40[i] = (i+1);
			//bin60[i] = (i+1);
			
			cout << bin20[i] << " " << edep_cum20[i] << endl;
		
		}
	}
	
	
	
	for(int i=0;i<71;i++){
		edep_cum60[i] = edep_cum60[i] / eBeam60;
		edep_cum40[i] = edep_cum40[i] / eBeam40;
		edep_cum20[i] = edep_cum20[i] / eBeam20;
		edep_cum10[i] = edep_cum10[i] / eBeam10;
	}
	
	TCanvas* c1 = new TCanvas("c1", "", 20, 20, 800, 600);
	
	TGraph * g60 = new TGraph(71, bin60, edep60);
	g60->SetMarkerStyle(20);
	g60->SetMarkerColor(6);
	
	TGraph * g40 = new TGraph(71, bin40, edep40);
	g40->SetMarkerStyle(20);
	g40->SetMarkerColor(4);
	
	TGraph * g20 = new TGraph(71, bin20, edep20);
	g20->SetMarkerStyle(20);
	g20->SetMarkerColor(2);
	
	TGraph * g10 = new TGraph(71, bin10, edep10);
	g10->SetMarkerStyle(20);
	g10->SetMarkerColor(1);
	
	TMultiGraph * mg = new TMultiGraph();
	mg->SetTitle("Transversal shower development;R (cm); Energy deposited (MeV)");
	
	mg->Add(g60); 
	mg->Add(g40); 
	mg->Add(g20); 
	//mg->Add(g10); 
	
	mg->Draw("APL");
	
	TLegend *legend2 = new TLegend(0.1,0.7,0.48,0.9);

	//legend2->AddEntry(g10,"10 GeV");
   	legend2->AddEntry(g20,"20 GeV");
  	legend2->AddEntry(g40,"40 GeV");
   	legend2->AddEntry(g60,"60 GeV");
 	legend2->Draw();
	
	
	gPad->SetGrid();
	
	TCanvas* c2 = new TCanvas("c2", "", 20, 20, 800, 600);
	
	TGraph * f60 = new TGraph(71, bin60, edep_cum60);
	f60->SetMarkerStyle(20);
	f60->SetMarkerColor(6);
	
	TGraph * f40 = new TGraph(71, bin40, edep_cum40);
	f40->SetMarkerStyle(20);
	f40->SetMarkerColor(4);
	
	TGraph * f20 = new TGraph(71, bin20, edep_cum20);
	f20->SetMarkerStyle(20);
	f20->SetMarkerColor(2);
	
	TGraph * f10 = new TGraph(71, bin10, edep_cum10);
	f10->SetMarkerStyle(20);
	f10->SetMarkerColor(1);
	
	TMultiGraph * mg2 = new TMultiGraph();
	mg2->SetTitle("Transversal shower containment;R [#lambda_{I}]; Fraction of energy deposited");
	//mg2->SetTitle("Transversal shower containment; R [cm] ; Fraction of energy deposited");
	
	mg2->Add(f60); 
	mg2->Add(f40); 
	mg2->Add(f20); 
	//mg2->Add(f10); 
	
	mg2->Draw("APL");
	
	TLegend *legend = new TLegend(0.1,0.7,0.48,0.9);

	//legend->AddEntry(f10,"10 GeV");
   	legend->AddEntry(f20,"20 GeV");
  	legend->AddEntry(f40,"40 GeV");
   	legend->AddEntry(f60,"60 GeV");
 	legend->Draw();
	
	gPad->SetGrid();
	
}
