#include <iostream>
#include <fstream>
#include <math.h>

void macro_distanceCheck(){

TFile *fin = new TFile("distanceCheck.root","read");
TTree *tree = (TTree*)fin->Get("tree");

TH1D* h1 = new TH1D("h1", "radius",100,0,100);
TH1D* h2 = new TH1D("h2", "xhole",100,0,100);
TH1D* h3 = new TH1D("h3", "yhole",100,0,100);
TH1D* h4 = new TH1D("h4", "xsize",100,200,300);
TH1D* h5 = new TH1D("h5", "ysize",100,200,300);

Int_t n = 5;
Double_t radius[n];
Double_t xhole[n];
Double_t yhole[n];
Int_t xsize[n];
Int_t ysize[n];
int surfacenum[n];

tree->SetBranchAddress("radius", radius);
tree->SetBranchAddress("xhole", xhole);
tree->SetBranchAddress("yhole", yhole);
tree->SetBranchAddress("xsize", xsize);
tree->SetBranchAddress("ysize", ysize);

TGraph *gr = new TGraph(40);
TGraph *gr2 = new TGraph(40);
int i = 0;
int nentries = tree->GetEntries();

for (int ientry = 0 ; ientry < nentries; ientry++){
    tree->GetEntry(ientry);
    for (int isurface=0; isurface < n; isurface++){
        h1->Fill(radius[isurface]);
        h2->Fill(xhole[isurface]);
        h3->Fill(yhole[isurface]);
        h4->Fill(xsize[isurface]);
        h5->Fill(ysize[isurface]);
        surfacenum[isurface] = isurface;  
        gr->SetPoint(i, i, xsize[isurface]);        
        gr2->SetPoint(i, i, xhole[isurface]/xsize[isurface]);
        i +=1;
    }
}
//TGraph *gr = new TGraph(n, surfacenum, xsize);
gr->SetMarkerStyle(8);
gr2->SetMarkerStyle(8);
TFile *fout = new TFile("distanceCheck_hist.root","recreate");
h1->Write(); 
h2->Write(); 
h3->Write(); 
h4->Write(); 
h5->Write();
gr->Write();
gr2->Write();
tree->Write();

fout->Close();


} 

