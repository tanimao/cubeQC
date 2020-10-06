#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>

void macro_forrangeif(){

TFile *fin     = new TFile("201005corg.root", "read");
//TFile *finbad  = new TFile("0828bad0831cor.root","read");
TTree *tree    = (TTree*)fin->Get("tree");
//TTree *treebad = (TTree*)finbad->Get("tree");

TH1D* h1 = new TH1D("h1","radius",100,45,55); 
TH1D* h2 = new TH1D("h2","xhole_max",100,140,220); 
TH1D* h3 = new TH1D("h3","yhole_max",100,140,220); 
TH1D* h4 = new TH1D("h4","xsize_max",100,640,680); 
TH1D* h5 = new TH1D("h5","ysize_max",100,640,680); 
TH1D* hd = new TH1D("hd","distance",100,0,100);
TH1D* hb = new TH1D("hb","bump",100,0,1000); 
TH1D* hE = new TH1D("hE","Esum",1000,0,500); 

TH1D* h1all = new TH1D("h1all","radius",100,45,55); 
TH1D* h2all = new TH1D("h2all","xhole_max",100,140,220); 
TH1D* h3all = new TH1D("h3all","yhole_max",100,140,220); 
TH1D* h4all = new TH1D("h4all","xsize_max",100,640,680); 
TH1D* h5all = new TH1D("h5all","ysize_max",100,640,680); 
TH1D* hball = new TH1D("hball","bump",100,0,1000); 
TH1D* hEall = new TH1D("hEall","Esum",1000,0,500); 

TH1D* h1six = new TH1D("h1six","radius",100,45,55); 
TH1D* h2six = new TH1D("h2six","xhole_max",100,140,220); 
TH1D* h3six = new TH1D("h3six","yhole_max",100,140,220); 
TH1D* h4six = new TH1D("h4six","xsize_max",100,640,680); 
TH1D* h5six = new TH1D("h5six","ysize_max",100,640,680); 
TH1D* hdsix = new TH1D("hdsix","distance",100,0,100); 
TH1D* hbsix = new TH1D("hbsix","bump",100,0,1000); 
TH1D* hEsix = new TH1D("hEsix","Esum",1000,0,500); 

//TH1D* h1bad = new TH1D("h1bad","radius",100,40,60); 
//TH1D* h2bad = new TH1D("h2bad","xhole_max",100,150,220); 
//TH1D* h3bad = new TH1D("h3bad","yhole_max",100,150,220); 
//TH1D* h4bad = new TH1D("h4bad","xsize_max",100,600,700); 
//TH1D* h5bad = new TH1D("h5bad","ysize_max",100,600,700); 
//TH1D* hdbad = new TH1D("hdbad","distance",100,0,100); 
//TH1D* hbbad = new TH1D("hbbad","bump",100,0,1000); 
//TH1D* hEbad = new TH1D("hEbad","Esum",1000,0,500); 


TH1D* h1b = new TH1D("h1b","radius",100,45,55); 
TH1D* h2b = new TH1D("h2b","xhole_max",100,140,220); 
TH1D* h3b = new TH1D("h3b","yhole_max",100,140,220); 
TH1D* h4b = new TH1D("h4b","xsize_max",100,640,680); 
TH1D* h5b = new TH1D("h5b","ysize_max",100,640,680); 
TH1D* hbb = new TH1D("hbb","bump",100,0,1000); 
TH1D* hEb = new TH1D("hEb","Esum",1000,0,500); 

Int_t n = 6;
Double_t radius[n];
Double_t xhole[n];
Double_t yhole[n];
Double_t xsize[n];
Double_t ysize[n];
Double_t Esum[n];
Double_t bump[n];


Double_t radiusbad[n];
Double_t xholebad[n];
Double_t yholebad[n];
Double_t xsizebad[n];
Double_t ysizebad[n];
Double_t Esumbad[n];
Double_t bumpbad[n];


Double_t radiabs;
Double_t xholeabs;
Double_t yholeabs;
Double_t xsizeabs;
Double_t ysizeabs;

/*
///0827goodcor.rootから持ってきた平均値
Double_t rMean  = 49.39;
Double_t xsMean = 657.3;
Double_t ysMean = 656.5;
Double_t xhMean = 187.1;
Double_t yhMean = 190.8;
*/

///2009010905から持ってきた平均値
Double_t rMean  = 49.11;
Double_t xsMean = 659.2;
Double_t ysMean = 659.2;
Double_t xhMean = 185.8;
Double_t yhMean = 185.9;



Double_t rMax;
Double_t xsMax;
Double_t ysMax;
Double_t xhMax;
Double_t yhMax;
Double_t bMax;
Double_t EMax;

tree->SetBranchAddress("radius", radius);
tree->SetBranchAddress("xhole", xhole);
tree->SetBranchAddress("yhole", yhole);
tree->SetBranchAddress("xsize", xsize);
tree->SetBranchAddress("ysize", ysize);
tree->SetBranchAddress("Esum", Esum);
tree->SetBranchAddress("bump", bump);


//treebad->SetBranchAddress("radius", radiusbad);
//treebad->SetBranchAddress("xhole", xholebad);
//treebad->SetBranchAddress("yhole", yholebad);
//treebad->SetBranchAddress("xsize", xsizebad);
//treebad->SetBranchAddress("ysize", ysizebad);
//treebad->SetBranchAddress("Esum", Esumbad);
//treebad->SetBranchAddress("bump", bumpbad);



int nentries = tree->GetEntries();

for ( int ientry = 0; ientry < nentries; ientry++ )
{
    tree->GetEntry( ientry );
//    treebad->GetEntry( ientry );
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
    bMax = bump[0];
    EMax = Esum[0];

    
    for (int isurf = 0; isurf <6; isurf++){



        h1all->Fill(radius[isurf]);
        h2all->Fill( xhole[isurf]);
        h3all->Fill( yhole[isurf]);
        h4all->Fill( xsize[isurf]);
        h5all->Fill( ysize[isurf]);
        hball->Fill(  bump[isurf]);
        hEall->Fill(  Esum[isurf]);
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
        if (bMax <= bump[isurf]){
            
            bMax = bump[isurf];
            }
        if (EMax <= Esum[isurf]){
            
            EMax = Esum[isurf];
            }
        }


   if (  
///*
   47.8 < radius[0] &&
   47.8 < radius[1] &&
   47.8 < radius[2] &&
   47.8 < radius[3] &&
   47.8 < radius[4] &&
   47.8 < radius[5] &&
 
 168+4+0.5 < xhole[0] && xhole[0] < 198 -0.5+2 &&
 168+4+0.5 < xhole[1] && xhole[1] < 198 -0.5+2 &&
 168+4+0.5 < xhole[2] && xhole[2] < 198 -0.5+2 &&
 168+4+0.5 < xhole[3] && xhole[3] < 198 -0.5+2 &&
 168+4+0.5 < xhole[4] && xhole[4] < 198 -0.5+2 &&
 168+4+0.5 < xhole[5] && xhole[5] < 198 -0.5+2 &&

 168+4+0.5 < yhole[0] && yhole[0] < 198 -0.5+2 &&
 168+4+0.5 < yhole[1] && yhole[1] < 198 -0.5+2 &&
 168+4+0.5 < yhole[2] && yhole[2] < 198 -0.5+2 &&
 168+4+0.5 < yhole[3] && yhole[3] < 198 -0.5+2 &&
 168+4+0.5 < yhole[4] && yhole[4] < 198 -0.5+2 &&
 168+4+0.5 < yhole[5] && yhole[5] < 198 -0.5+2 &&
   
  651.8 < xsize[0] && xsize[0] < 664.8-0.5 &&
  651.8 < xsize[1] && xsize[1] < 664.8-0.5 &&
  651.8 < xsize[2] && xsize[2] < 664.8-0.5 &&
  651.8 < xsize[3] && xsize[3] < 664.8-0.5 &&
  651.8 < xsize[4] && xsize[4] < 664.8-0.5 &&
  651.8 < xsize[5] && xsize[5] < 664.8-0.5 &&
  
  651.8 < ysize[0] && ysize[0] < 664.8-0.5 &&
  651.8 < ysize[1] && ysize[1] < 664.8-0.5 &&
  651.8 < ysize[2] && ysize[2] < 664.8-0.5 &&
  651.8 < ysize[3] && ysize[3] < 664.8-0.5 &&
  651.8 < ysize[4] && ysize[4] < 664.8-0.5 &&
  651.8 < ysize[5] && ysize[5] < 664.8-0.5 &&
 
 Esum[0] < 200 &&
 Esum[1] < 200 &&
 Esum[2] < 200 &&
 Esum[3] < 200 &&
 Esum[4] < 200 &&
 Esum[5] < 200 &&
 
 bump[0] < 200 &&
 bump[1] < 200 &&
 bump[2] < 200 &&
 bump[3] < 200 &&
 bump[4] < 200 &&
 bump[5] < 200 &&
//*/  
    1==1)
 {

    h1->Fill(rMax);
    h2->Fill(xhMax);
    h3->Fill(yhMax);
    h4->Fill(xsMax);
    h5->Fill(ysMax);
    hb->Fill(bMax);
    hE->Fill(EMax);
    
    for (int fill =0; fill<6; fill++){
    h1six->Fill(radius[fill]);
    h2six->Fill(xhole[fill]);
    h3six->Fill(yhole[fill]);
    h4six->Fill(xsize[fill]);
    h5six->Fill(ysize[fill]);
    hbsix->Fill(bump[fill]);
    hEsix->Fill(Esum[fill]);

//    h1bad->Fill(radiusbad[fill]);
//    h2bad->Fill(xholebad[fill]);
//    h3bad->Fill(yholebad[fill]);
//    h4bad->Fill(xsizebad[fill]);
//    h5bad->Fill(ysizebad[fill]);
//    hbbad->Fill(bumpbad[fill]);
//    hEbad->Fill(Esumbad[fill]);
    }

    }
    else{
    h1b->Fill(rMax);
    h2b->Fill(xhMax);
    h3b->Fill(yhMax);
    h4b->Fill(xsMax);
    h5b->Fill(ysMax);
    hbb->Fill(bMax);
    hEb->Fill(EMax);
    }

}

TFile *fout = new TFile("201005cutg.root", "recreate");
h1->Write();
h2->Write();
h3->Write();
h4->Write();
h5->Write();
hb->Write();
hE->Write();

h1all->Write();
h2all->Write();
h3all->Write();
h4all->Write();
h5all->Write();
hball->Write();
hEall->Write();

h1six->Write();
h2six->Write();
h3six->Write();
h4six->Write();
h5six->Write();
hbsix->Write();
hEsix->Write();

//h1bad->Write();
//h2bad->Write();
//h3bad->Write();
//h4bad->Write();
//h5bad->Write();
//hbbad->Write();
//hEbad->Write();

h1b->Write();
h2b->Write();
h3b->Write();
h4b->Write();
h5b->Write();
hbb->Write();
hEb->Write();


fout->Close();




}
