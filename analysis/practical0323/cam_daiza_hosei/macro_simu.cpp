#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>

void macro_simu(){

TFile *fin     = new TFile("2009010905.root", "read");
TTree *tree    = (TTree*)fin->Get("tree");

TH1D* h1 = new TH1D("h1","radius;[mm];",100, 0.01554 * 45,  0.01554 * 55); 
TH1D* h2 =  new TH1D("h2","xhole;[mm];",100, 0.01554 * 140, 0.01554 * 220); 
TH1D* h3 =  new TH1D("h3","yhole;[mm];",100, 0.01554 * 140, 0.01554 * 220); 
TH1D* h4 =  new TH1D("h4","xsize;[mm];",100, 0.01554 * 640, 0.01554 * 680); 
TH1D* h5 =  new TH1D("h5","ysize;[mm];",100, 0.01554 * 640, 0.01554 * 680); 
TH1D* hb =  new TH1D("hb","bump",100,0,1000); 
TH1D* hE =  new TH1D("hE","Esum",100,0,1000); 



Int_t n = 6;
Double_t radius[n];
Double_t xhole[n];
Double_t yhole[n];
Double_t xsize[n];
Double_t ysize[n];
Double_t Esum[n];
Double_t bump[n];



tree->SetBranchAddress("radius", radius);
tree->SetBranchAddress("xhole", xhole);
tree->SetBranchAddress("yhole", yhole);
tree->SetBranchAddress("xsize", xsize);
tree->SetBranchAddress("ysize", ysize);
tree->SetBranchAddress("Esum", Esum);
tree->SetBranchAddress("bump", bump);




int nentries = tree->GetEntries();

for ( int ientry = 0; ientry < nentries; ientry++ )
{
    tree->GetEntry( ientry );


    
    for (int fill =0; fill<6; fill++){
    h1->Fill(0.01554*radius[fill]);
    h2->Fill(0.01554*xhole[fill]);
    h3->Fill(0.01554*yhole[fill]);
    h4->Fill(0.01554*xsize[fill]);
    h5->Fill(0.01554*ysize[fill]);
    hb->Fill(bump[fill]);
    hE->Fill(Esum[fill]);

    }
}

TFile *fout = new TFile("2009010905hist.root", "recreate");
h1->Write();
h2->Write();
h3->Write();
h4->Write();
h5->Write();
hb->Write();
hE->Write();



fout->Close();




}
