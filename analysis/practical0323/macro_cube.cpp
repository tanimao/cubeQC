#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>

void macro_cube(){



TString dumpdate      = "0420";
TString histdate      = "0421";
TString readroot  = "_1.root";
TString selectroot= "_1select.root";
TString cuttxt1   = "../hist/";
TString cuttxt2    = "1cut.txt";


TString file_readroot= dumpdate + readroot; 
TString file_cut  = cuttxt1 + histdate + cuttxt2;
TString file_selectroot= dumpdate + histdate + selectroot;


TFile *fin = new TFile(file_readroot, "read");
TTree *tree = (TTree*)fin->Get("tree");

std::ofstream ofile(file_cut);




TH1D* h1 = new TH1D("h1","radius",100,0,100);
TH1D* h2 = new TH1D("h2","xhole",100,100,500); 
TH1D* h3 = new TH1D("h3","yhole",100,100,500); 
TH1D* h4 = new TH1D("h4","xsize",100,640,690); 
TH1D* h5 = new TH1D("h5","ysize",100,640,690); 
TH1D* hE = new TH1D("hE","Esum" ,100,0,100);
TH1D* hb = new TH1D("hb","bump" ,100,0,1);
TH1D* hd = new TH1D("hd","distance",100,0,100); 


TH1D* hist_shade = new TH1D("hist_shade","hole_shade",100,0.2,0.4);
TH1D* hist_shine = new TH1D("hist_shine","hole_shine",100,0.2,0.4);


Int_t n = 6;
Double_t radius[n];
Double_t xhole[n];
Double_t yhole[n];
Double_t Esum[n];
Double_t bump[n];
Double_t xsize[n];
Double_t ysize[n];
Double_t d1=0.;
Double_t d2=0.;
Double_t d3=0.;
Double_t shade=0.;
Double_t shine=0.;

Double_t dmax=0.;

tree->SetBranchAddress("radius", radius);
tree->SetBranchAddress("xhole", xhole);
tree->SetBranchAddress("yhole", yhole);
tree->SetBranchAddress("xsize", xsize);
tree->SetBranchAddress("ysize", ysize);
tree->SetBranchAddress("Esum" , Esum );
tree->SetBranchAddress("bump" , bump );

int nentries = tree->GetEntries();

for ( int ientry = 0; ientry < nentries; ientry++ )
{
  tree->GetEntry( ientry );
  if ( true
    
/*
    && xsize[0]>=324 && xsize[0]<=330 
    && xsize[1]>=324 && xsize[1]<=330 
    && xsize[2]>=324 && xsize[2]<=330 
    && xsize[3]>=324 && xsize[3]<=330 
    && xsize[4]>=324 && xsize[4]<=330 
    && xsize[5]>=324 && xsize[5]<=330 
    && ysize[0]>=321 && ysize[0]<=328
    && ysize[1]>=321 && ysize[1]<=328
    && ysize[2]>=321 && ysize[2]<=328
    && ysize[3]>=321 && ysize[3]<=328
    && ysize[4]>=321 && ysize[4]<=328
    && ysize[5]>=321 && ysize[5]<=328
    && xhole[0]>=89  && xhole[0]<=99
//    && xhole[1]>=89  && xhole[1]<=99
    && xhole[2]>=89  && xhole[2]<=99
//    && xhole[3]>=89  && xhole[3]<=99
    && xhole[4]>=89  && xhole[4]<=99
    && xhole[5]>=89  && xhole[5]<=99
    && yhole[0]>=90  && yhole[0]<=100
//    && yhole[1]>=90  && yhole[1]<=100
    && yhole[2]>=90  && yhole[2]<=100
//    && yhole[3]>=90  && yhole[3]<=100
    && yhole[4]>=90  && yhole[4]<=100
    && yhole[5]>=90  && yhole[5]<=100
  */    
                                 ){ 


    
    //cout << ientry+1 << endl;
    for (int inum=0; inum<n ; inum++){
    
        h1->Fill(radius[inum]);
        h2->Fill(xhole[inum]);
        h3->Fill(yhole[inum]);
        h4->Fill(xsize[inum]);
        h5->Fill(ysize[inum]);
        hE->Fill(Esum[inum]);
        hb->Fill(bump[inum]);
        

        if(xhole[inum]<300){
            shade = xhole[inum]/xsize[inum];
            hist_shade->Fill(shade);
        }else{
            shine = (xsize[inum]-xhole[inum])/xsize[inum];
            hist_shine->Fill(shine);
        }
        
        if(yhole[inum]<300){
            shade = yhole[inum]/ysize[inum];
            hist_shade->Fill(shade);
        }else{
            shine = (ysize[inum]-yhole[inum])/ysize[inum];
            hist_shine->Fill(shine);
        }
            //cout << "entry_surface is :" << ientry+1 << "_" << isurface+1 << endl;
    
     }

    
    
    
    
    }
}

TFile *fout = new TFile(file_selectroot, "recreate");
//tree->Write();
h1->Write();
h2->Write();
h3->Write();
h4->Write();
h5->Write();
hE->Write();
hb->Write();
hist_shade->Write();
hist_shine->Write();
fout->Close();




}
