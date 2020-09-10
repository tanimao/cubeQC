#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>

void macro_correlation(){



TString dumpdate      = "0326";
TString histdate      = "0327";
TString readroot  = "_1.root";
TString selectroot= "_1correlation.root";
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

TH1D* hx1= new TH1D("hx1","xsize_cam1",100,640,690);
TH1D* hx2= new TH1D("hx2","xsize_cam2",100,640,690);
TH1D* hx3= new TH1D("hx3","xsize_cam3",100,640,690);

TH1D* hy1= new TH1D("hy1","ysize_cam1",100,640,690);
TH1D* hy2= new TH1D("hy2","ysize_cam2",100,640,690);
TH1D* hy3= new TH1D("hy3","ysize_cam3",100,640,690);


TH1D* hist_shade = new TH1D("hist_shade","hole_shade",100,0.2,0.4);
TH1D* hist_shine = new TH1D("hist_shine","hole_shine",100,0.2,0.4);
TH2D* h_shade_shine = new TH2D("h_shade_shine","shade_shine;shade;shine",100,0.2,0.4,100,0.2,0.4);
TH2D* h_shade_shine_cor = new TH2D("h_shade_shine_cor","shade_shine;shade;shine_cor",100,0.2,0.4,100,0.2,0.4);
TH2D* h_holecam12    = new TH2D("h_holecam12","cam12;cam1;cam2",100,0.2,0.4,100,0.2,0.4);
TH2D* h_holecam23    = new TH2D("h_holecam23","cam23;cam2;cam3",100,0.2,0.4,100,0.2,0.4);
TH2D* h_holecam13    = new TH2D("h_holecam13","cam13;cam1;cam3",100,0.2,0.4,100,0.2,0.4);


TH2D* h_sizecam12    = new TH2D("h_sizecam12","cam12;cam1;cam2",100,0.2,0.4,100,640,690);
TH2D* h_sizecam23    = new TH2D("h_sizecam23","cam23;cam2;cam3",100,0.2,0.4,100,640,690);
TH2D* h_sizecam13    = new TH2D("h_sizecam13","cam13;cam1;cam3",100,0.2,0.4,100,640,690);

Int_t n = 12;
Double_t radius[n];
Double_t xhole[n];
Double_t yhole[n];
Double_t Esum[n];
Double_t bump[n];
Double_t xsize[n];
Double_t ysize[n];
Double_t xholerate[n];
Double_t yholerate[n];

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

    xholerate[0] = xhole[0]/xsize[0];
    xholerate[1] = xhole[1]/xsize[1];
    xholerate[2] = (((xsize[2]-xhole[2])/xsize[2])-0.016)/0.95;
    xholerate[3] = (((xsize[3]-xhole[3])/xsize[3])-0.016)/0.95;

    xholerate[4] = (((xsize[4]-xhole[4])/xsize[4])-0.016)/0.95;
    xholerate[5] = xhole[5]/xsize[5];
    xholerate[6] = xhole[6]/xsize[6];
    xholerate[7] = (((xsize[7]-xhole[7])/xsize[7])-0.016)/0.95;

    xholerate[8] = xhole[8]/xsize[8];
    xholerate[9] = (((xsize[9]-xhole[9])/xsize[9])-0.016)/0.95;
    xholerate[10] = (((xsize[10]-xhole[10])/xsize[10])-0.016)/0.95;
    xholerate[11] = xhole[11]/xsize[11];


    yholerate[0] = (((ysize[0]-yhole[0])/ysize[0])-0.016)/0.95;
    yholerate[1] = yhole[1]/ysize[1];
    yholerate[2] = yhole[2]/ysize[2];
    yholerate[3] = (((ysize[3]-yhole[3])/ysize[3])-0.016)/0.95;
    
    yholerate[4] = (((ysize[4]-yhole[4])/ysize[4])-0.016)/0.95;
    yholerate[5] = (((ysize[5]-yhole[5])/ysize[5])-0.016)/0.95;
    yholerate[6] = yhole[6]/ysize[6];
    yholerate[7] = yhole[7]/ysize[7];

    yholerate[8] = yhole[8]/ysize[8];
    yholerate[9] = yhole[9]/ysize[9];
    yholerate[10] = (((ysize[10]-yhole[10])/ysize[10])-0.016)/0.95;
    yholerate[11] = (((ysize[11]-yhole[11])/ysize[11])-0.016)/0.95;

    h_shade_shine->Fill(xhole[0]/xsize[0], (xsize[2]-xhole[2])/xsize[2]);
    h_shade_shine->Fill(xhole[1]/xsize[1], (xsize[3]-xhole[3])/xsize[3]);
    h_shade_shine->Fill(xhole[6]/xsize[6], (xsize[4]-xhole[4])/xsize[4]);
    h_shade_shine->Fill(xhole[5]/xsize[5], (xsize[7]-xhole[7])/xsize[7]);
    h_shade_shine->Fill(xhole[8]/xsize[8], (xsize[10]-xhole[10])/xsize[10]);
    h_shade_shine->Fill(xhole[11]/xsize[11], (xsize[9]-xhole[9])/xsize[9]);
    
    h_shade_shine_cor->Fill(xhole[0]/xsize[0],   (((xsize[2]-xhole[2])/xsize[2]   )-0.016)/0.95);
    h_shade_shine_cor->Fill(xhole[1]/xsize[1],   (((xsize[3]-xhole[3])/xsize[3]   )-0.016)/0.95);
    h_shade_shine_cor->Fill(xhole[6]/xsize[6],   (((xsize[4]-xhole[4])/xsize[4]   )-0.016)/0.95);
    h_shade_shine_cor->Fill(xhole[5]/xsize[5],   (((xsize[7]-xhole[7])/xsize[7]   )-0.016)/0.95);
    h_shade_shine_cor->Fill(xhole[8]/xsize[8],   (((xsize[10]-xhole[10])/xsize[10])-0.016)/0.95);
    h_shade_shine_cor->Fill(xhole[11]/xsize[11], (((xsize[9]-xhole[9])/xsize[9]   )-0.016)/0.95);
    
    h_shade_shine->Fill(yhole[1]/ysize[1], (ysize[3]-yhole[3])/ysize[3]);
    h_shade_shine->Fill(yhole[2]/ysize[2], (ysize[0]-yhole[0])/ysize[0]);
    h_shade_shine->Fill(yhole[6]/ysize[6], (ysize[4]-yhole[4])/ysize[4]);
    h_shade_shine->Fill(yhole[7]/ysize[7], (ysize[5]-yhole[5])/ysize[5]);
    h_shade_shine->Fill(yhole[8]/ysize[8], (ysize[10]-yhole[10])/ysize[10]);
    h_shade_shine->Fill(yhole[9]/ysize[9], (ysize[11]-yhole[11])/ysize[11]);
    
    h_shade_shine_cor->Fill(yhole[1]/ysize[1], (((ysize[3]-yhole[3])/ysize[3]   )-0.016)/0.95);
    h_shade_shine_cor->Fill(yhole[2]/ysize[2], (((ysize[0]-yhole[0])/ysize[0]   )-0.016)/0.95);
    h_shade_shine_cor->Fill(yhole[6]/ysize[6], (((ysize[4]-yhole[4])/ysize[4]   )-0.016)/0.95);
    h_shade_shine_cor->Fill(yhole[7]/ysize[7], (((ysize[5]-yhole[5])/ysize[5]   )-0.016)/0.95);
    h_shade_shine_cor->Fill(yhole[8]/ysize[8], (((ysize[10]-yhole[10])/ysize[10])-0.016)/0.95);
    h_shade_shine_cor->Fill(yhole[9]/ysize[9], (((ysize[11]-yhole[11])/ysize[11])-0.016)/0.95);

    h_holecam12->Fill(xholerate[0], xholerate[4]);
    h_holecam12->Fill(xholerate[1], xholerate[5]);
    h_holecam12->Fill(xholerate[2], xholerate[6]);
    h_holecam12->Fill(xholerate[3], xholerate[7]);
    h_holecam12->Fill(yholerate[0], yholerate[4]);
    h_holecam12->Fill(yholerate[1], yholerate[5]);
    h_holecam12->Fill(yholerate[2], yholerate[6]);
    h_holecam12->Fill(yholerate[3], yholerate[7]);


    h_holecam23->Fill(xholerate[4], xholerate[8]);
    h_holecam23->Fill(xholerate[5], xholerate[9]);
    h_holecam23->Fill(xholerate[6], xholerate[10]);
    h_holecam23->Fill(xholerate[7], xholerate[11]);
    h_holecam23->Fill(yholerate[4], yholerate[8]);
    h_holecam23->Fill(yholerate[5], yholerate[9]);
    h_holecam23->Fill(yholerate[6], yholerate[10]);
    h_holecam23->Fill(yholerate[7], yholerate[11]);


    h_holecam13->Fill(xholerate[0], xholerate[8]);
    h_holecam13->Fill(xholerate[1], xholerate[9]);
    h_holecam13->Fill(xholerate[2], xholerate[10]);
    h_holecam13->Fill(xholerate[3], xholerate[11]);
    h_holecam13->Fill(yholerate[0], yholerate[8]);
    h_holecam13->Fill(yholerate[1], yholerate[9]);
    h_holecam13->Fill(yholerate[2], yholerate[10]);
    h_holecam13->Fill(yholerate[3], yholerate[11]);

    for(int icam=0;icam<4;icam++){
        hx1->Fill(xsize[icam]);
        hy1->Fill(ysize[icam]);
        
        hx2->Fill(xsize[icam+4]);
        hy2->Fill(ysize[icam+4]);
        
        hx3->Fill(xsize[icam+8]);
        hy3->Fill(ysize[icam+8]);

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
h_shade_shine->Write();
h_shade_shine_cor->Write();
h_holecam12->Write();
h_holecam23->Write();
h_holecam13->Write();
hx1->Write();
hx2->Write();
hx3->Write();
hy1->Write();
hy2->Write();
hy3->Write();

hist_shade->Write();
hist_shine->Write();
fout->Close();




}
