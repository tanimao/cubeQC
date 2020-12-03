#include <iostream>
#include <fstream>
#include <math.h>

void macro_col(){

TString date = "1114";
TString gorb = "bad";
TString prefolder = "../";
TString readroot  = "1hist1.root";
TString makeroot  = "1hist1_selected.root";

TString file_readroot = prefolder + date + gorb + readroot ;
TString file_makeroot = prefolder + date + gorb + makeroot ;

TFile *fin = new TFile(file_readroot, "read");
TTree *tree = (TTree*)fin->Get("tree");




TH1D* hcolw = new TH1D("hcolw","colw",1100,0,1100); 
TH1D* hcol = new TH1D("hcol","col",1100,0,1100); 

TH1D* hnorcolw = new TH1D("hnorcolw","norcolw",100,0,4); 
TH1D* hnorcol = new TH1D("hnorcol","norcol",100,0,1); 


Int_t n = 6;
Double_t colw[n];
Double_t col[n];
Double_t colall[n];

Double_t norcolw=0.;
Double_t norcol=0.;

tree->SetBranchAddress("colw",colw);
tree->SetBranchAddress("col",col);
tree->SetBranchAddress("colall",colall);


int nentries = tree->GetEntries();

for ( int ientry = 0; ientry < nentries; ientry++ )
{
  tree->GetEntry( ientry );
  if ( true 

    && col[0]/colall[0] <0.52
    && col[1]/colall[1] <0.52
    && col[2]/colall[2] <0.52
    && col[3]/colall[3] <0.52
    && col[4]/colall[4] <0.52
    && col[5]/colall[5] <0.52
   /* 
    && colw[0]/colall[0] <=0.85
    && colw[1]/colall[1] <=0.85
    && colw[2]/colall[2] <=0.85
    && colw[3]/colall[3] <=0.85
    && colw[4]/colall[4] <=0.85
    && colw[5]/colall[5] <=0.85
  */
                               ){ 


    
    for (int isurface=0; isurface<n ; isurface++){
    
        hcol->Fill(col[isurface]);
        hcolw->Fill(colw[isurface]);
        norcol = col[isurface]/colall[isurface];  
        norcolw = colw[isurface]/colall[isurface];      
            hnorcol->Fill(norcol);
            hnorcolw->Fill(norcolw);
        
    }

//        cout << "survived cube is " << ientry << endl;
  }
else{
    cout << "rejected cube is " << ientry << endl;
}
    
    
    
    
}

TFile *fout = new TFile(file_makeroot , "recreate");
//tree->Write();
hcol->Write();
hcolw->Write();
hnorcolw->Write();
hnorcol->Write();
fout->Close();




}
