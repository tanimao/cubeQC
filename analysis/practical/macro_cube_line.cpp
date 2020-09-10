#include <iostream>
#include <fstream>
#include <math.h>

void macro_cube_line(){

TFile *fin = new TFile("1108good1_th150.root", "read");
TTree *tree = (TTree*)fin->Get("tree");

std::ofstream ofile("../hist/1108cut_good1.txt");




TH1D* h1 = new TH1D("h1","radius",100,0,100);

TH1D* hcolw = new TH1D("hcolw","colw",1100,0,1100); 
TH1D* hcol = new TH1D("hcol","col",1100,0,1100); 
TH1D* hvote = new TH1D("hvote","vote",30,0,30); 

TH1D* h2 = new TH1D("h2","xhole",100,0,100); 
TH1D* h3 = new TH1D("h3","yhole",100,0,100); 
TH1D* h4 = new TH1D("h4","xsize",100,200,300); 
TH1D* h5 = new TH1D("h5","ysize",100,200,300); 
TH1D* hd = new TH1D("hd","distance",100,0,100); 

TH1D* hnorcolw = new TH1D("hnorcolw","norcolw",100,0,4); 
TH1D* hnorcol = new TH1D("hnorcol","norcol",100,0,1); 


Int_t n = 6;
Double_t radius[n];
Double_t colw[n];
Double_t col[n];
Double_t colall[n];
Double_t xhole[n];
Double_t yhole[n];
Int_t xsize[n];
Int_t ysize[n];
Double_t vote[n];
Double_t d1=0.;
Double_t d2=0.;
Double_t d3=0.;

Double_t dmax=0.;
Double_t norcolw=0.;
Double_t norcol=0.;

tree->SetBranchAddress("radius", radius);
tree->SetBranchAddress("colw",colw);
tree->SetBranchAddress("col",col);
tree->SetBranchAddress("colall",colall);
tree->SetBranchAddress("vote",vote);
tree->SetBranchAddress("xhole", xhole);
tree->SetBranchAddress("yhole", yhole);
tree->SetBranchAddress("xsize", xsize);
tree->SetBranchAddress("ysize", ysize);


int nentries = tree->GetEntries();

for ( int ientry = 0; ientry < nentries; ientry++ )
{
  tree->GetEntry( ientry );
  if ( true
      
    && xsize[0]>=230 && xsize[0]<=234 
    && xsize[1]>=230 && xsize[1]<=234 
    && xsize[2]>=230 && xsize[2]<=234 
    && xsize[3]>=230 && xsize[3]<=234 
    && xsize[4]>=230 && xsize[4]<=234 
    && xsize[5]>=230 && xsize[5]<=234 
    && ysize[0]>=230 && ysize[0]<=237
    && ysize[1]>=230 && ysize[1]<=237
    && ysize[2]>=230 && ysize[2]<=237
    && ysize[3]>=230 && ysize[3]<=237
    && ysize[4]>=230 && ysize[4]<=237
    && ysize[5]>=230 && ysize[5]<=237
    && xhole[0]>=63  && xhole[0]<=70 
    && xhole[1]>=63  && xhole[1]<=70 
    && xhole[2]>=63  && xhole[2]<=70 
    && xhole[3]>=63  && xhole[3]<=70 
    && xhole[4]>=63  && xhole[4]<=70 
    && xhole[5]>=63  && xhole[5]<=70 
    && yhole[0]>=63  && yhole[0]<=75 
    && yhole[1]>=63  && yhole[1]<=75 
    && yhole[2]>=63  && yhole[2]<=75 
    && yhole[3]>=63  && yhole[3]<=75 
    && yhole[4]>=63  && yhole[4]<=75 
    && yhole[5]>=63  && yhole[5]<=75
    

   /* 

    && radius[0]>=16 && radius[0]<=19.5 
    && radius[1]>=16 && radius[1]<=19.5 
    && radius[2]>=16 && radius[2]<=19.5 
    && radius[3]>=16 && radius[3]<=19.5 
    && radius[4]>=16 && radius[4]<=19.5 
    && radius[5]>=16 && radius[5]<=19.5
*/
    && col[0]/colall[0] <=0.4
    && col[1]/colall[1] <=0.4
    && col[2]/colall[2] <=0.4
    && col[3]/colall[3] <=0.4
    && col[4]/colall[4] <=0.4
    && col[5]/colall[5] <=0.4
/*
    && colw[0]/colall[0] <=1.5
    && colw[1]/colall[1] <=1.5
    && colw[2]/colall[2] <=1.5
    && colw[3]/colall[3] <=1.5
    && colw[4]/colall[4] <=1.5
    && colw[5]/colall[5] <=1.5
*/
      
                                 ){ 


    
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

    
    //if(norcol <= 0.42){
    //cout << ientry+1 << endl;
    for (int isurface=0; isurface<n ; isurface++){
    
        h1->Fill(radius[isurface]);
        hcol->Fill(col[isurface]);
        hvote->Fill(vote[isurface]);
        h2->Fill(xhole[isurface]);
        h3->Fill(yhole[isurface]);
        h4->Fill(xsize[isurface]);
        h5->Fill(ysize[isurface]);
        
        norcol = col[isurface]/colall[isurface];  
        norcolw = colw[isurface]/colall[isurface];      
            //cout << "entry_surface is :" << ientry+1 << "_" << isurface+1 << endl;
            hnorcol->Fill(norcol);
            hnorcolw->Fill(norcolw);
    
     }

    
    
    
    hd->Fill(dmax);
    
            ofile << ientry <<  endl;
            cout << "entry is :" << ientry+1  << endl;
    //}
  }
}

ofile.close();
TFile *fout = new TFile("1108good1_th150_select.root", "recreate");
//tree->Write();
h1->Write();
h2->Write();
h3->Write();
h4->Write();
h5->Write();
hcol->Write();
hcolw->Write();
hvote->Write();
hd->Write();
hnorcolw->Write();
hnorcol->Write();
fout->Close();




}
