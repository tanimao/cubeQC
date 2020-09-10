#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>

void macro_cube2(){



TString gorb = "good";
TString date1      = "1114";
TString date2      = "1115";
TString readroot  = "1_th150.root";
TString selectroot= "1_th150_select.root";
TString cuttxt1   = "../hist/";
TString cuttxt2    = "1cut.txt";


TString file_root1= date1 + gorb + readroot; 
TString file_cut  = cuttxt1 + date2 + gorb + cuttxt2;
TString file_root2= date2 + gorb + selectroot;


TFile *fin = new TFile(file_root1, "read");
TTree *tree = (TTree*)fin->Get("tree");

std::ofstream ofile(file_cut);




TH1D* h1 = new TH1D("h1","radius",100,0,100);

TH1D* hcolw = new TH1D("hcolw","colw",1100,0,1100); 
TH1D* hcol = new TH1D("hcol","col",1100,0,1100); 
TH1D* hvote = new TH1D("hvote","vote",30,0,30); 

TH1D* h2 = new TH1D("h2","xhole",100,50,150); 
TH1D* h3 = new TH1D("h3","yhole",100,50,150); 
TH1D* h4 = new TH1D("h4","xsize",100,300,400); 
TH1D* h5 = new TH1D("h5","ysize",100,300,400); 
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
    
/*

    && col[0]/colall[0] <=0.4
    && col[1]/colall[1] <=0.4
    && col[2]/colall[2] <=0.4
    && col[3]/colall[3] <=0.4
    && col[4]/colall[4] <=0.4
    && col[5]/colall[5] <=0.4
    && colw[0]/colall[0] <=1.5
    && colw[1]/colall[1] <=1.5
    && colw[2]/colall[2] <=1.5
    && colw[3]/colall[3] <=1.5
    && colw[4]/colall[4] <=1.5
    && colw[5]/colall[5] <=1.5
*/
      
                                 ){ 


    
    d1 = sqrt((xhole[0]-xhole[2])*(xhole[0]-xhole[2]) 
            + (yhole[0]-yhole[2])*(yhole[0]-yhole[2]));
    d2 = sqrt((xhole[1]-xhole[3])*(xhole[1]-xhole[3]) 
            + (yhole[1]-yhole[3])*(yhole[1]-yhole[3]));
    d3 = sqrt((xhole[4]-xhole[5])*(xhole[4]-xhole[5]) 
            + (yhole[4]-yhole[5])*(yhole[4]-yhole[5]));
    if (d1>=d2){
        if (d3>=d1){
            dmax = d3;
        }else{dmax = d1;}
    }else{
        if(d3>=d2){
            dmax = d3;
        }else{dmax = d2;}
    }

    
    if(dmax <= 12){
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
    }
  }
else {
    cout << "rejected cube is " << ientry+1 << endl;
}
}

ofile.close();
TFile *fout = new TFile(file_root2, "recreate");
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
