#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <TGraph.h>
#include <TString.h>

using namespace std;


void read_edep()
{

	Double_t bin[71];
	Double_t edep[71];
	Double_t edep_cum[71];
	Double_t evt[1000];
	
	Double_t eBeam = 60000.;

	string filename = "eDep_60GeV.txt";

	vector<vector<string>> content;
	vector<string> row;
	string line, word;
	
	fstream file (filename);
	if(file.is_open()){
		cout << "File is open" << endl;
		while(getline(file, line)){
			row.clear();
			stringstream str(line);
				
			
			while(getline(str, word, ',')){
				row.push_back(word);
				
			} 
			content.push_back(row);
			//std::cout<<content<<endl;
		}
	}else {
		cout<< "could not open the file" << endl;
	}
	
	cout<< content.size()<<endl;
	cout<<content[3].size()<<endl;
	
	for(int i=3; i<content.size(); i++) {
	
		//std::cout<< content[3][i]<<endl;
		
		//conversion from string to TString
		TString l(content[i][2]); 
		TString e(content[i][3]);
		TString v(content[i][5]);
		
		//conversion frotm TString to Double_t
		bin[i-3]=l.Atof();  
		edep[i-3]=e.Atof(); 
		evt[i-3]=v.Atof();
		
		edep[i-3] = edep[i-3] / evt[i-3] ;
	
	}
	
	
	
	for(int i=0; i<71; i++){
		
		if( i!= 0) edep_cum[i] = (edep[i] + edep[i-1]);
	}
	
	for(int i=0;i<71;i++) edep_cum[i] = edep_cum[i] / 60000;
	
	
	TGraph * g = new TGraph(71, bin, edep);
	g->SetMarkerStyle(20);
	g->GetXaxis()->SetTitle("R (cm)");
	//g->GetYaxis()->SetTitle("Deposited energy (MeV)");
	g->GetYaxis()->SetTitle("Fraction of deposited energy");
	g->SetTitle("Transversal shower development");
	g->Draw("AP");
	
	gPad->SetGrid();
    
}
