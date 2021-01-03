#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>


void cubesize(){


TString file_root= "size_no18.root"; 
TString file_txt = "size_no18.txt";

TFile *file = new TFile(file_root,"recreate");
TTree *tree = new TTree("tree","tree");

std::ifstream fin;
fin.open(file_txt);
if(fin.fail()){
    cerr << "cannot open file. " << endl;
    return 1;
}

double height[10];
double width[10];
double depth[10];

tree->Branch("height", height, "height[10]/D");
tree->Branch("width", width, "width[10]/D");
tree->Branch("depth", depth, "depth[10]/D");


for(Int_t i=0; i<10;i++){
        
        fin >> height[i] >> width[i] >> depth[i] ;
    
    }
tree->Fill();
tree->Write();

fin.close();
file->Close();

}
