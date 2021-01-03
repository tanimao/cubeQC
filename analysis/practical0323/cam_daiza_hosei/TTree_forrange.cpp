#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>


void TTree_forrange(){

TString filedate = "201102cor";
TString dumpdate = "201102";
TString makeroot = ".root";
TString opentxt1 = "../../../files/data";
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
 Int_t n_cube = 576; //cube数
 Int_t n = 6;        //6面

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
int daiza[n];
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
tree->Branch("daiza",daiza,"daiza[6]/I");

for(Int_t i=0; i<n_cube;i++){
    for(Int_t j=0; j<n; j++){
        if (j==0 || j==1 || j==2){
        fin //>>  daiza[j] 
            >> icam[j] >> direction[j] 
            >> xhole[j] >> yhole[j]
            >> radius[j] >> Esum[j] 
            >> xsize[j] >> ysize[j] >> bump[j];
        }
        if (j==3 || j==4 || j==5){
        fin //>>  daiza[j] 
            >> icam[j] >> direction[j] 
            >> yhole[j] >> xhole[j]
            >> radius[j] >> Esum[j] 
            >> ysize[j] >> xsize[j] >> bump[j];
        }



        }
    tree->Fill();
}
        
/*
    for(Int_t j=0; j<n/2;j++){
        
        fin >>  icam[2*j] >> direction[2*j] 
            >> xhole[2*j] >> yhole[2*j]
            >> radius[2*j] >> Esum[2*j] 
            >> xsize[2*j] >> ysize[2*j]>> bump[2*j];
    
        fin >> icam[2*j+1]>> direction[2*j+1] 
            >>  yhole[2*j+1] >> xhole[2*j+1]
            >> radius[2*j+1] >> Esum[2*j+1] 
            >> ysize[2*j+1] >> xsize[2*j+1]>> bump[2*j+1];

    }
*/  
  


tree->Write();
fin.close();
file->Close();

}
