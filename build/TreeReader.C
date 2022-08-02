void TreeReader()
{
 
 	TFile *input = new TFile("B4.root", "read");
 	
 	TTree *tree = (TTree*)input->Get("B4");
 	
 	int entries = tree->GetEntries();
 	
 	double edep; int evt, hitID;
 	
 	vector<int> nHits;
 	
 	
 	
 	//cout << entries << endl;
 	
 	
 		for(int j=0; j<entries; j++) {
 			tree->GetEntry(j);
 			
 			tree->SetBranchAddress("Egap", &edep);
 			tree->SetBranchAddress("EventID", &evt);
 			tree->SetBranchAddress("HitID", &hitID);
 			
 			for(int i=0; i<evt; i++){
 				if(edep > 0.030) nHits.at(i)++;
 		}
 		
 		//cout << nHits.at(i) << endl;
 	}
 	
 	for(int i= nHits.begin(); i=!nHits.end(); i++) cout << nHits.at(i) << endl;
 	
}
