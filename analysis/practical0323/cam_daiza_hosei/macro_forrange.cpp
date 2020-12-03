#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>

void macro_forrange(){

TFile *fin = new TFile("0828badcor.root", "read");
TTree *tree = (TTree*)fin->Get("tree");

TH1D* h1 = new TH1D("h1","radius",100,20,80); 
TH1D* h2 = new TH1D("h2","xhole_max",100,130,230); 
TH1D* h3 = new TH1D("h3","yhole_max",100,130,230); 
TH1D* h4 = new TH1D("h4","xsize_max",100,600,700); 
TH1D* h5 = new TH1D("h5","ysize_max",100,600,700); 
TH1D* hd = new TH1D("hd","distance",100,0,100); 

Int_t n = 6;
Double_t radius[n];
Double_t xhole[n];
Double_t yhole[n];
Double_t xsize[n];
Double_t ysize[n];

Double_t radiabs;
Double_t xholeabs;
Double_t yholeabs;
Double_t xsizeabs;
Double_t ysizeabs;

///0827goodcor.rootから持ってきた平均値
Double_t rMean  = 49.39;
Double_t xsMean = 657.3;
Double_t ysMean = 656.5;
Double_t xhMean = 187.1;
Double_t yhMean = 190.8;

Double_t rMax;
Double_t xsMax;
Double_t ysMax;
Double_t xhMax;
Double_t yhMax;

tree->SetBranchAddress("radius", radius);
tree->SetBranchAddress("xhole", xhole);
tree->SetBranchAddress("yhole", yhole);
tree->SetBranchAddress("xsize", xsize);
tree->SetBranchAddress("ysize", ysize);


int nentries = tree->GetEntries();

for ( int ientry = 0; ientry < nentries; ientry++ )
{
    tree->GetEntry( ientry );
    //std::cout << xhole[1] << std::endl;

    //平均値からの距離maxをfillする
    radiabs  = fabs(radius[0]-rMean);
    xholeabs = fabs(xhole[0]-xhMean);
    yholeabs = fabs(yhole[0]-yhMean);
    xsizeabs = fabs(xsize[0]-xsMean);
    ysizeabs = fabs(ysize[0]-ysMean);

    rMax  = radius[0];
    xhMax = xhole[0];
    yhMax = yhole[0];
    xsMax = xsize[0];
    ysMax = ysize[0];

    
    for (int isurf = 0; isurf <6; isurf++){
        if (radiabs <= fabs(radius[isurf]-rMean)){
            radiabs  = fabs(radius[isurf]-rMean);
            rMax = radius[isurf];
            }
        if (xholeabs <= fabs(xhole[isurf]-xhMean)){
            xholeabs  = fabs(xhole[isurf]-xhMean);
            xhMax = xhole[isurf];
            }
        if (yholeabs <= fabs(yhole[isurf]-yhMean)){
            yholeabs  = fabs(yhole[isurf]-yhMean);
            yhMax = yhole[isurf];
            }
        if (xsizeabs <= fabs(xsize[isurf]-xsMean)){
            xsizeabs  = fabs(xsize[isurf]-xsMean);
            xsMax = xsize[isurf];
            }
        if (ysizeabs <= fabs(ysize[isurf]-ysMean)){
            ysizeabs  = fabs(ysize[isurf]-ysMean);
            ysMax = ysize[isurf];
            }
        }
    h1->Fill(rMax);
    h2->Fill(xhMax);
    h3->Fill(yhMax);
    h4->Fill(xsMax);
    h5->Fill(ysMax);

}

TFile *fout = new TFile("0828badcormax.root", "recreate");
h1->Write();
h2->Write();
h3->Write();
h4->Write();
h5->Write();
hd->Write();
fout->Close();




}
