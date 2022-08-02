#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <TGraph.h>
#include <TString.h>

using namespace std;


vector<vector<string>> read_from_file(string filename)
{

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

	return content;

}

int read_edep_1()
{
	vector<vector<string>> content60;
	
	content60 = read_from_file("eDep_60GeV.txt");
	

}
