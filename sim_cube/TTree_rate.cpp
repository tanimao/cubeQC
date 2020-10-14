#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>


void TTree_rate(){

TString filedate = "0820";
TString dumpdate = "0823";

TString file_root= "goodrate82_3.root"; 
TString file_txt = "good_clear82_3.txt";

TFile *file = new TFile(file_root,"recreate");
TTree *tree = new TTree("tree","tree");

std::ifstream fin;
fin.open(file_txt);
if(fin.fail()){
    cerr << "cannot open file. " << endl;
    return 1;
}

int Nall[648];
double goodrate[648];
double clearrate[648];

tree->Branch("Nall", Nall, "Nall[648]/I");
tree->Branch("goodrate", goodrate, "goodrate[648]/D");
tree->Branch("clearrate", clearrate, "clearrate[648]/D");


for(Int_t i=0; i<648;i++){
        
        fin >> Nall[i] >> goodrate[i] >> clearrate[i] ;
    
    }
tree->Fill();
tree->Write();

fin.close();
file->Close();

}
