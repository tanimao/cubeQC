#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>


void TTree_cube2(){

TString gorb = "bad";
TString filedate = "1114";
TString date = "1114";
TString makeroot = "1_th150.root";
TString opentxt1 = "../../files/cube_data";
TString opentxt2 = "1_th150.txt";

TString file_root= date + gorb + makeroot; 
TString file_txt = opentxt1 + filedate + gorb + opentxt2;

TFile *file = new TFile(file_root,"recreate");
TTree *tree = new TTree("tree","tree");

std::ifstream fin;
fin.open(file_txt);
if(fin.fail()){
    cerr << "cannot open file. " << endl;
    return 1;
}
 Int_t n_cube = 70; 
 Int_t n = 6;

std::string saveName[n];
double radius[n];
double col[n];
double colw[n];
double colall[n];
double vote[n];
double xhole[n];
double yhole[n];
int xsize[n];
int ysize[n];

tree->Branch("radius", radius, "radius[6]/D");
tree->Branch("col", col, "col[6]/D");
tree->Branch("colw", colw, "colw[6]/D");
tree->Branch("colall", colall, "colall[6]/D");
tree->Branch("vote", vote, "vote[6]/D");
tree->Branch("xhole", xhole, "xhole[6]/D");
tree->Branch("yhole", yhole, "yhole[6]/D");
tree->Branch("xsize", xsize, "xsize[6]/I");
tree->Branch("ysize", ysize, "ysize[6]/I");

for(Int_t i=0; i<n_cube;i++){
    for(Int_t j=0; j<n;j++){
        fin >> saveName[j] >>  radius[j] 
        >> col[j] >> colw[j] >> colall[j] >> vote[j] 
        >> xhole[j] >> yhole[j] >> xsize[j] >> ysize[j];
    
    }


    tree->Fill();
}
tree->Write();
fin.close();
file->Close();

}
