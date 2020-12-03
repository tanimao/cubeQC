#include <iostream>
#include <fstream>
#include <math.h>

void macro_cube(){

TFile *fin = new TFile("1010bad_edge.root", "read");
TTree *tree = (TTree*)fin->Get("tree");
/*
TCut cut1("cut1", "abs(xhole[0]-yhole[2])<=5");
TCut cut2("cut2", "abs(xhole[2]-yhole[0])<=5");
TCut cut3("cut3", "abs(xhole[1]-yhole[3])<=5");
TCut cut4("cut4", "abs(xhole[3]-yhole[1])<=5");
TCut cut5("cut5", "abs(xhole[4]-yhole[5])<=5");
TCut cut6("cut6", "abs(xhole[5]-yhole[4])<=5");
*/
//tree->Draw("xsize[0]>>h1(100,200,300)",cut1&&cut2&&cut3&&cut4&&cut5&&cut6);

TH1D* h1 = new TH1D("h1","radius",100,0,100); 
TH1D* h2 = new TH1D("h2","xhole",100,0,100); 
TH1D* h3 = new TH1D("h3","yhole",100,0,100); 
TH1D* h4 = new TH1D("h4","xsize",100,200,300); 
TH1D* h5 = new TH1D("h5","ysize",100,200,300); 
TH1D* hd = new TH1D("hd","distance",100,0,100); 

Int_t n = 6;
Double_t radius[n];
Double_t xhole[n];
Double_t yhole[n];
Int_t xsize[n];
Int_t ysize[n];
Double_t d1=0.;
Double_t d2=0.;
Double_t d3=0.;

Double_t dmax=0.;

tree->SetBranchAddress("radius", radius);
tree->SetBranchAddress("xhole", xhole);
tree->SetBranchAddress("yhole", yhole);
tree->SetBranchAddress("xsize", xsize);
tree->SetBranchAddress("ysize", ysize);


int nentries = tree->GetEntries();

for ( int ientry = 0; ientry < nentries; ientry++ )
{
  tree->GetEntry( ientry );
  if ( xsize[0]>=230 && xsize[0]<=237 
    && xsize[1]>=230 && xsize[1]<=237 
    && xsize[2]>=230 && xsize[2]<=237 
    && xsize[3]>=230 && xsize[3]<=237 
    && xsize[4]>=230 && xsize[4]<=237 
    && xsize[5]>=230 && xsize[5]<=237 
    && ysize[1]>=231 && ysize[1]<=240
    && ysize[2]>=231 && ysize[2]<=240
    && ysize[3]>=231 && ysize[3]<=240
    && ysize[4]>=231 && ysize[4]<=240
    && ysize[5]>=231 && ysize[5]<=240
    && xhole[0]>=64  && xhole[0]<=72 
    && xhole[1]>=64  && xhole[1]<=72 
    && xhole[2]>=64  && xhole[2]<=72 
    && xhole[3]>=64  && xhole[3]<=72 
    && xhole[4]>=64  && xhole[4]<=72 
    && xhole[5]>=64  && xhole[5]<=72 
    && yhole[0]>=61  && yhole[0]<=76 
    && yhole[1]>=61  && yhole[1]<=76 
    && yhole[2]>=61  && yhole[2]<=76 
    && yhole[3]>=61  && yhole[3]<=76 
    && yhole[4]>=61  && yhole[4]<=76 
    && yhole[5]>=61  && yhole[5]<=76 ){ 

    d1 = sqrt((xhole[0]-yhole[3])*(xhole[0]-yhole[3]) 
            + (xhole[3]-yhole[0])*(xhole[3]-yhole[0]));
    d2 = sqrt((xhole[1]-yhole[5])*(xhole[1]-yhole[5]) 
            + (xhole[5]-yhole[1])*(xhole[5]-yhole[1]));
    d3 = sqrt((xhole[2]-yhole[4])*(xhole[2]-yhole[4]) 
            + (xhole[4]-yhole[2])*(xhole[4]-yhole[2]));
    if (d1>=d2){
        if (d3>=d1){
            dmax = d3;
        }else{dmax = d1;}
    }else{
        if(d3>=d2){
            dmax = d3;
        }else{dmax = d2;}
    }

    
    if(dmax<10){

    for (int isurface=0; isurface<n ; isurface++){
    
        h1->Fill(radius[isurface]);
        h2->Fill(xhole[isurface]);
        h3->Fill(yhole[isurface]);
        h4->Fill(xsize[isurface]);
        h5->Fill(ysize[isurface]);
        }
    
    
    
    hd->Fill(dmax);
    }
  }
}

TFile *fout = new TFile("1010bad_edge_xholeyholeselect.root", "recreate");
h1->Write();
h2->Write();
h3->Write();
h4->Write();
h5->Write();
hd->Write();
fout->Close();




}
