#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>


void TTree_cube0420(){

TString filedate = "0610";
TString dumpdate = "0610";
TString makeroot = "_.root";
TString opentxt1 = "../../files/data";
TString opentxt2 = "good.txt";

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
 Int_t n_cube = 154; 
 Int_t n = 6;

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

tree->Branch("xhole",  xhole,  "xhole[6]/D");
tree->Branch("yhole",  yhole,  "yhole[6]/D");
tree->Branch("radius", radius, "radius[6]/D");
tree->Branch("Esum",   Esum,   "Esum[6]/D");
tree->Branch("bump",   bump,   "bump[6]/D");
tree->Branch("xsize",  xsize,  "xsize[6]/D");
tree->Branch("ysize",  ysize,  "ysize[6]/D");
tree->Branch("icam",   icam,   "icam[6]/I");
tree->Branch("direction",direction,"direction[6]/I");

for(Int_t i=0; i<n_cube;i++){
    for(Int_t j=0; j<n/3;j++){
        

        fin >> saveName[3*j] >>  icam[3*j] >> direction[3*j] 
            >> xhole[3*j] >> yhole[3*j]
            >> radius[3*j] >> Esum[3*j] >> xsize[3*j] >> ysize[3*j]>> bump[3*j]
            >> dust1[3*j] >> dust2[3*j];
    
        fin >> saveName[3*j+1] >> icam[3*j+1]>> direction[3*j+1] 
            >>  yhole[3*j+1] >> xhole[3*j+1]
            >> radius[3*j+1] >> Esum[3*j+1] >> ysize[3*j+1] >> xsize[3*j+1]>> bump[3*j+1]
            >> dust1[3*j+1] >> dust2[3*j+1];

        fin >> saveName[3*j+2] >>  icam[3*j+2] >> direction[3*j+2] 
            >> yhole[3*j+2] >> xhole[3*j+2]
            >> radius[3*j+2] >> Esum[3*j+2] >> ysize[3*j+2] >> xsize[3*j+2]>> bump[3*j+2]
            >> dust1[3*j+2] >> dust2[3*j+2];
    }


    tree->Fill();
}
tree->Write();
fin.close();
file->Close();

}
