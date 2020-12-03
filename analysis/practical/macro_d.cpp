#include <iostream>
#include <fstream>
#include <math.h>

void macro_d(){

TFile *fin = new TFile("bad0925.root", "read");
TTree *tree = (TTree*)fin->Get("tree");

//TCut cut1("cut1", "abs(xhole[0]-yhole[2])<=5");
//TCut cut2("cut2", "abs(xhole[2]-yhole[0])<=5");
//TCut cut3("cut3", "abs(xhole[1]-yhole[3])<=5");
//TCut cut4("cut4", "abs(xhole[3]-yhole[1])<=5");
//TCut cut5("cut5", "abs(xhole[4]-yhole[5])<=5");
//TCut cut6("cut6", "abs(xhole[5]-yhole[4])<=5");
//tree->Draw("xsize[0]>>h1(100,200,300)",cut1&&cut2&&cut3&&cut4&&cut5&&cut6);

TH1D* h1 = new TH1D("h1","radius",100,0,100); 
TH1D* h2 = new TH1D("h2","xhole",100,0,100); 
TH1D* h3 = new TH1D("h3","yhole",100,0,100); 
TH1D* h4 = new TH1D("h4","xsize",100,200,300); 
TH1D* h5 = new TH1D("h5","ysize",100,200,300); 
TH1D* hd = new TH1D("hd","distance",200,0,200); 

Int_t n = 6;
Int_t radius[n];
Int_t xhole[n];
Int_t yhole[n];
Int_t xsize[n];
Int_t ysize[n];
Double_t d1=0.;
Double_t d2=0.;
Double_t d3=0.;

Double_t d12_max=0.;
Double_t d123_max=0.;

tree->SetBranchAddress("radius", radius);
tree->SetBranchAddress("xhole", xhole);
tree->SetBranchAddress("yhole", yhole);
tree->SetBranchAddress("xsize", xsize);
tree->SetBranchAddress("ysize", ysize);


int nentries = tree->GetEntries();

for ( int ientry = 0; ientry < nentries; ientry++ )
{
    tree->GetEntry( ientry );
    for (int isurface=0; isurface<n ; isurface++){
    h1->Fill(radius[isurface]);
    h2->Fill(xhole[isurface]);
    h3->Fill(yhole[isurface]);
    h4->Fill(xsize[isurface]);
    h5->Fill(ysize[isurface]);
    }
    
    d1 = sqrt((xhole[0]-yhole[2])*(xhole[0]-yhole[2]) 
            + (xhole[2]-yhole[0])*(xhole[2]-yhole[0]));
    d2 = sqrt((xhole[1]-yhole[3])*(xhole[1]-yhole[3]) 
            + (xhole[3]-yhole[1])*(xhole[3]-yhole[1]));
    d1 = sqrt((xhole[4]-yhole[5])*(xhole[4]-yhole[5]) 
            + (xhole[5]-yhole[4])*(xhole[5]-yhole[4]));
    if(d1 >= d2 ){
            d12_max = d1;
        }else {
            d12_max = d2;
        }
    if(d3 >= d12_max){
            d123_max = d3;
        }else{
            d123_max = d12_max;
        }
    
    hd->Fill(d123_max);
}

TFile *fout = new TFile("distance_bad.root", "recreate");
h1->Write();
h2->Write();
h3->Write();
h4->Write();
h5->Write();
hd->Write();
fout->Close();




}
