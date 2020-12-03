#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>

void macro_simu(){

TFile *fin     = new TFile("201007corg.root", "read");
TTree *tree    = (TTree*)fin->Get("tree");

TFile *finb     = new TFile("0828bad0831cor0911.root", "read");
TTree *treeb    = (TTree*)finb->Get("tree");



TH1D* h1 = new TH1D("h1","radius;[mm];",100, 0.01554 * 45,  0.01554 * 55); 
TH1D* h2 =  new TH1D("h2","xhole;[mm];",100, 0.01554 * 140, 0.01554 * 220); 
TH1D* h3 =  new TH1D("h3","yhole;[mm];",100, 0.01554 * 140, 0.01554 * 220); 
TH1D* h4 =  new TH1D("h4","xsize;[mm];",100, 0.01554 * 640, 0.01554 * 680); 
TH1D* h5 =  new TH1D("h5","ysize;[mm];",100, 0.01554 * 640, 0.01554 * 680); 
TH1D* hb =  new TH1D("hb","bump",100,0,1000); 
TH1D* hE =  new TH1D("hE","Esum",100,0,1000); 

TH1D* h1b =  new TH1D("h1b","radius;[mm];",100, 0.01554 * 45,  0.01554 * 55); 
TH1D* h2b =  new TH1D("h2b","xhole;[mm];",100, 0.01554 * 140, 0.01554 * 220); 
TH1D* h3b =  new TH1D("h3b","yhole;[mm];",100, 0.01554 * 140, 0.01554 * 220); 
TH1D* h4b =  new TH1D("h4b","xsize;[mm];",100, 0.01554 * 640, 0.01554 * 680); 
TH1D* h5b =  new TH1D("h5b","ysize;[mm];",100, 0.01554 * 640, 0.01554 * 680); 

//H1D* h1 = new TH1D("h1","radius",100,  45,   55); 
//H1D* h2 =  new TH1D("h2","xhole",100,  140,  220); 
//H1D* h3 =  new TH1D("h3","yhole",100,  140,  220); 
//H1D* h4 =  new TH1D("h4","xsize",100,  640,  680); 
//H1D* h5 =  new TH1D("h5","ysize",100,  640,  680); 


Int_t n = 6;
Double_t radius[n];
Double_t xhole[n];
Double_t yhole[n];
Double_t xsize[n];
Double_t ysize[n];
Double_t Esum[n];
Double_t bump[n];


Double_t radiusb[n];
Double_t xholeb[n];
Double_t yholeb[n];
Double_t xsizeb[n];
Double_t ysizeb[n];
Double_t Esumb[n];
Double_t bumpb[n];

tree->SetBranchAddress("radius", radius);
tree->SetBranchAddress("xhole", xhole);
tree->SetBranchAddress("yhole", yhole);
tree->SetBranchAddress("xsize", xsize);
tree->SetBranchAddress("ysize", ysize);
tree->SetBranchAddress("Esum", Esum);
tree->SetBranchAddress("bump", bump);

treeb->SetBranchAddress("radius", radiusb);
treeb->SetBranchAddress("xhole", xholeb);
treeb->SetBranchAddress("yhole", yholeb);
treeb->SetBranchAddress("xsize", xsizeb);
treeb->SetBranchAddress("ysize", ysizeb);
treeb->SetBranchAddress("Esum", Esumb);
treeb->SetBranchAddress("bump", bumpb);



int nentries = tree->GetEntries();

for ( int ientry = 0; ientry < nentries; ientry++ )
{
    tree->GetEntry( ientry );
    treeb->GetEntry( ientry );


    
    for (int fill =0; fill<6; fill++){
   //h1->Fill(radius[fill]);
   //h2->Fill(xhole[fill]);
   //h3->Fill(yhole[fill]);
   //h4->Fill(xsize[fill]);
   //h5->Fill(ysize[fill]);
    hb->Fill(bump[fill]);
    hE->Fill(Esum[fill]);
    
    h1->Fill(0.01554*radius[fill]);
    h2->Fill(0.01554*xhole[fill]);
    h3->Fill(0.01554*yhole[fill]);
    h4->Fill(0.01554*xsize[fill]);
    h5->Fill(0.01554*ysize[fill]);

    h1b->Fill(0.01554*radiusb[fill]);
    h2b->Fill(0.01554*xholeb[fill]);
    h3b->Fill(0.01554*yholeb[fill]);
    h4b->Fill(0.01554*xsizeb[fill]);
    h5b->Fill(0.01554*ysizeb[fill]);

    }


}

h1b->Scale((h1->GetEntries())/(h1b->GetEntries()));
h2b->Scale((h2->GetEntries())/(h2b->GetEntries()));
h3b->Scale((h3->GetEntries())/(h3b->GetEntries()));
h4b->Scale((h4->GetEntries())/(h4b->GetEntries()));
h5b->Scale((h5->GetEntries())/(h5b->GetEntries()));


TFile *fout = new TFile("201007hist.root", "recreate");
h1->Write();
h2->Write();
h3->Write();
h4->Write();
h5->Write();
hb->Write();
hE->Write();

h1b->Write();
h2b->Write();
h3b->Write();
h4b->Write();
h5b->Write();


fout->Close();




}
