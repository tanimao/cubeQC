#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>


void TTree_cube(){

TString filedate = "0820daiza2";
TString dumpdate = "0821daiza2";
TString makeroot = ".root";
TString opentxt1 = "../../files/data";
TString opentxt2 = ".txt";

TString file_root= dumpdate + makeroot; 
TString file_txt = opentxt1 + filedate + opentxt2;

TFile *file = new TFile(file_root,"recreate");
TTree *tree = new TTree("tree","tree");

std::ifstream fin;
fin.open(file_txt);
if(fin.fail()){
    cerr << "cannot open file. " << endl;
    return 1;
}
 Int_t n_cube = 16*6; //cube数*6面
 Int_t n = 12;        //カメラ3個*向き4方向

std::string saveName[n];
double xhole[n];
double yhole[n];
double radius[n];
double Esum[n];
double bump[n];
double xsize[n];
double ysize[n];
double dust1[n];
double dust2[n];
int icam[n];
int direction[n];

tree->Branch("xhole",  xhole,  "xhole[12]/D");
tree->Branch("yhole",  yhole,  "yhole[12]/D");
tree->Branch("radius", radius, "radius[12]/D");
tree->Branch("Esum",   Esum,   "Esum[12]/D");
tree->Branch("bump",   bump,   "bump[12]/D");
tree->Branch("xsize",  xsize,  "xsize[12]/D");
tree->Branch("ysize",  ysize,  "ysize[12]/D");
tree->Branch("icam",   icam,   "icam[12]/I");
tree->Branch("direction",direction,"direction[12]/I");

for(Int_t i=0; i<n_cube;i++){
    for(Int_t j=0; j<n/2;j++){
        

        fin >> saveName[2*j] >>  icam[2*j] >> direction[2*j] 
            >> xhole[2*j] >> yhole[2*j]
            >> radius[2*j] >> Esum[2*j] >> xsize[2*j] >> ysize[2*j]>> bump[2*j]
            >> dust1[2*j] >> dust2[2*j];
    
        fin >> saveName[2*j+1] >> icam[2*j+1]>> direction[2*j+1] 
            >>  yhole[2*j+1] >> xhole[2*j+1]
            >> radius[2*j+1] >> Esum[2*j+1] >> ysize[2*j+1] >> xsize[2*j+1]>> bump[2*j+1]
            >> dust1[2*j+1] >> dust2[2*j+1];
    }


    tree->Fill();
}
tree->Write();
fin.close();
file->Close();

}
