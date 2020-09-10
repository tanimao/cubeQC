#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <cmath>
// macro_correlation3 によって得たh_xhole[j],h_yhole[j]に対する補正を実行する。(_cor2)
// 直線フィッティングによる補正を実行(_cor3)
void macro_correlation0608(){

///学振用

TString dumpdate      = "0401";
TString histdate      = "0609";
TString readroot  = "_2.root";
TString selectroot= "_1rep.root";


TString file_readroot= dumpdate + readroot; 
TString file_selectroot= dumpdate + histdate + selectroot;


TFile *fin = new TFile(file_readroot, "read");
TTree *tree = (TTree*)fin->Get("tree");
gStyle->SetOptFit(1111);
TH1D* h2 = new TH1D("h2","xhole_cor3",100,100,500);


TString id_xhole[28][6];
TH1D* hid_xhole[28][6];
TString id_yhole[28][6];
TH1D* hid_yhole[28][6];

TString id_xholecor3[28][6];
TH1D* hid_xholecor3[28][6];
TString id_yholecor3[28][6];
TH1D* hid_yholecor3[28][6];
for (int i28=0; i28<28; i28++){
    for (int i6=0; i6<6; i6++){
        id_xhole[i28][i6] = "hid_xhole"+std::to_string(i28)+std::to_string(i6);
        hid_xhole[i28][i6]= new TH1D(id_xhole[i28][i6],"xhole",100,0.25,0.35);
        id_yhole[i28][i6] = "hid_yhole"+std::to_string(i28)+std::to_string(i6);
        hid_yhole[i28][i6]= new TH1D(id_yhole[i28][i6],"yhole",100,0.25,0.35);

        id_xholecor3[i28][i6] = "hid_xholecor3_"+std::to_string(i28)+std::to_string(i6);
        hid_xholecor3[i28][i6]= new TH1D(id_xholecor3[i28][i6],"xholecor3",100,0.25,0.35);
        id_yholecor3[i28][i6] = "hid_yholecor3_"+std::to_string(i28)+std::to_string(i6);
        hid_yholecor3[i28][i6]= new TH1D(id_yholecor3[i28][i6],"yholecor3",100,0.25,0.35);
    }
}
TH1D* hxholeDev = new TH1D("hxholeDev","xhole_Std_Dev",100,0, 0.01);
TH1D* hyholeDev = new TH1D("hyholeDev","yhole_Std_Dev",100,0, 0.01);
TH1D* hxholeMean = new TH1D("hxholeMean","xhole_Std_Mean",100,0.2, 0.35);
TH1D* hyholeMean = new TH1D("hyholeMean","yhole_Std_Mean",100,0.2, 0.35);
TH1D* hxholeDevcor3 = new TH1D("hxholeDevcor3","xhole_Std_Devcor3",100,0, 0.01);
TH1D* hyholeDevcor3 = new TH1D("hyholeDevcor3","yhole_Std_Devcor3",100,0, 0.01);
TH1D* hxholeMeancor3 = new TH1D("hxholeMeancor3","xhole_Std_Meancor3",100,0.2, 0.35);
TH1D* hyholeMeancor3 = new TH1D("hyholeMeancor3","yhole_Std_Meancor3",100,0.2, 0.35);

TH1D* hxholeRep = new TH1D("hxholeRep","xhole_Representative",100,0, 0.15);
TH1D* hyholeRep = new TH1D("hyholeRep","yhole_Representative",100,0, 0.15);

TH1D* hx1= new TH1D("hx1","xsize_cam1",100,640,690);
TH1D* hx2= new TH1D("hx2","xsize_cam2",100,640,690);
TH1D* hx3= new TH1D("hx3","xsize_cam3",100,640,690);

TH1D* hy1= new TH1D("hy1","ysize_cam1",100,640,690);
TH1D* hy2= new TH1D("hy2","ysize_cam2",100,640,690);
TH1D* hy3= new TH1D("hy3","ysize_cam3",100,640,690);

TH1D* hxhole1= new TH1D("hxhole1","xhole_cam1",100,100,500);
TH1D* hxhole2= new TH1D("hxhole2","xhole_cam2",100,100,500);
TH1D* hxhole3= new TH1D("hxhole3","xhole_cam3",100,100,500);

TH1D* hyhole1= new TH1D("hyhole1","yhole_cam1",100,100,500);
TH1D* hyhole2= new TH1D("hyhole2","yhole_cam2",100,100,500);
TH1D* hyhole3= new TH1D("hyhole3","yhole_cam3",100,100,500);


TH2D* h_shade_shine = new TH2D("h_shade_shine","shade_shine;shade;shine",100,0.25,0.35,100,0.25,0.35);
TH2D* h_shade_shine_cor2 = new TH2D("h_shade_shine_cor2","shade_shine;shade;shine",100,0.25,0.35,100,0.25,0.35);
TH2D* h_shade_shine_cor3 = new TH2D("h_shade_shine_cor3","shade_shine;shade;shine",100,0.25,0.35,100,0.25,0.35);
TString checkxhole12[12][6];
TH2D* h_xhole[12];
TString checkyhole12[12][6];
TH2D* h_yhole[12];
TH1D* h_xholesub[12];
TH1D* h_yholesub[12];

TH1D* h_xholesubcor[12];
TH1D* h_yholesubcor[12];
for (int check12=0; check12<12; check12++){
    checkxhole12[check12][0] = "xhole1_"+std::to_string(check12+1);
    checkxhole12[check12][1] = "xhole;img1;img"+std::to_string(check12+1);
    h_xhole[check12] = new TH2D(checkxhole12[check12][0],checkxhole12[check12][1],100,0.2,0.4,100,0.2,0.4);

    checkyhole12[check12][0] = "yhole1_"+std::to_string(check12+1);
    checkyhole12[check12][1] = "yhole;img1;img"+std::to_string(check12+1);
    h_yhole[check12] = new TH2D(checkyhole12[check12][0],checkyhole12[check12][1],100,0.2,0.4,100,0.2,0.4);    

    checkxhole12[check12][2] = "h_xholesub"+std::to_string(check12+1);
    checkxhole12[check12][3] = "xholesubtraciton;img1-img"+std::to_string(check12+1);
    h_xholesub[check12] = new TH1D(checkxhole12[check12][2],checkxhole12[check12][3], 100, -0.03,0.03);
    checkyhole12[check12][2] = "h_yholesub"+std::to_string(check12+1);
    checkyhole12[check12][3] = "yholesubtraciton;img1-img"+std::to_string(check12+1);   
    h_yholesub[check12] = new TH1D(checkyhole12[check12][2],checkyhole12[check12][3], 100, -0.03,0.03);
    
    checkxhole12[check12][4] = "h_xholesubcor_"+std::to_string(check12+1);
    checkxhole12[check12][5] = "xholesubtraciton_cor;img1-img"+std::to_string(check12+1);
    h_xholesubcor[check12] = new TH1D(checkxhole12[check12][4],checkxhole12[check12][5], 100, -0.03,0.03);
    checkyhole12[check12][4] = "h_yholesubcor_"+std::to_string(check12+1);
    checkyhole12[check12][5] = "yholesubtraciton_cor;img1-img"+std::to_string(check12+1);   
    h_yholesubcor[check12] = new TH1D(checkyhole12[check12][4],checkyhole12[check12][5], 100, -0.03,0.03);
}

TH2D* h_shade_shine1 = new TH2D("h_shade_shine1","shade_shine;shade;shine",100,0.25,0.35,1000,0.2,0.35);
TH2D* h_shade_shine2 = new TH2D("h_shade_shine2","shade_shine;shade;shine",100,0.25,0.35,1000,0.2,0.35);
TH2D* h_shade_shine3 = new TH2D("h_shade_shine3","shade_shine;shade;shine",100,0.25,0.35,1000,0.2,0.35);
TH2D* h_shade_shine1_cor2 = new TH2D("h_shade_shine1_cor2","shade_shine;shade;shine",100,0.25,0.35,100,0.25,0.35);
TH2D* h_shade_shine2_cor2 = new TH2D("h_shade_shine2_cor2","shade_shine;shade;shine",100,0.25,0.35,100,0.25,0.35);
TH2D* h_shade_shine3_cor2 = new TH2D("h_shade_shine3_cor2","shade_shine;shade;shine",100,0.25,0.35,100,0.25,0.35);

TH2D* h_shade_shine1_cor3 = new TH2D("h_shade_shine1_cor3","shade_shine;shade;shine",100,0.25,0.35,100,0.25,0.35);
TH2D* h_shade_shine2_cor3 = new TH2D("h_shade_shine2_cor3","shade_shine;shade;shine",100,0.25,0.35,100,0.25,0.35);
TH2D* h_shade_shine3_cor3 = new TH2D("h_shade_shine3_cor3","shade_shine;shade;shine",100,0.25,0.35,100,0.25,0.35);

TString id_xhole2D[28][6];
TH2D* hid_xhole2D[28][6];
for (int i28=0; i28<28; i28++){
    for (int i6=0; i6<6; i6++){
        id_xhole2D[i28][i6] = "hid_xhole2D"+std::to_string(i28)+std::to_string(i6);
        hid_xhole2D[i28][i6]= new TH2D(id_xhole2D[i28][i6],"xhole2D;shade(xhole/Mean(xsize));shine(xhole/Mean(xsize))",100,0.25,0.35, 100,0.25,0.35);
    }
}
TString id_yhole2D[28][6];
TH2D* hid_yhole2D[28][6];
for (int i28=0; i28<28; i28++){
    for (int i6=0; i6<6; i6++){
        id_yhole2D[i28][i6] = "hid_yhole2D"+std::to_string(i28)+std::to_string(i6);
        hid_yhole2D[i28][i6]= new TH2D(id_yhole2D[i28][i6],"yhole2D;shade(yhole/Mean(ysize));shine(yhole/Mean(ysize))",100,0.25,0.35, 100,0.25,0.35);
    }
}

Int_t n = 12;
Double_t radius[n];
Double_t xhole[n];
Double_t yhole[n];
Double_t Esum[n];
Double_t bump[n];
Double_t xsize[n];
Double_t ysize[n];
Double_t xholecor[n];
Double_t yholecor[n];
Double_t xholecor3[n];
Double_t yholecor3[n];
Int_t icam[n];
Int_t direction[n];
Double_t xholep0[28][6];
Double_t xholep1[28][6];
Double_t yholep0[28][6];
Double_t yholep1[28][6];

Double_t hid_xholeMean[28][6];
Double_t hid_yholeMean[28][6];
Double_t hid_xmax[28];
Double_t hid_ymax[28];
Double_t xsubtra[28];
Double_t ysubtra[28];

TString id_xholepol[28][6];
TF1* xpol1[28][6];
TString id_yholepol[28][6];
TF1* ypol1[28][6];
for (int i28=0; i28<28; i28++){
    for (int i6=0; i6<6; i6++){
        id_xholepol[i28][i6] = "id_xholepol"+std::to_string(i28)+std::to_string(i6);
        xpol1[i28][i6]= new TF1(id_xholepol[i28][i6],"[0]+x*[1]",0.2,0.4);

        id_yholepol[i28][i6] = "id_yholepol"+std::to_string(i28)+std::to_string(i6);
        ypol1[i28][i6]= new TF1(id_yholepol[i28][i6],"[0]+x*[1]",0.2,0.4);
    }
}


tree->SetBranchAddress("radius", radius);
tree->SetBranchAddress("xhole", xhole);
tree->SetBranchAddress("yhole", yhole);
tree->SetBranchAddress("xsize", xsize);
tree->SetBranchAddress("ysize", ysize);
tree->SetBranchAddress("Esum" , Esum );
tree->SetBranchAddress("bump" , bump );
tree->SetBranchAddress("icam",  icam );
tree->SetBranchAddress("direction",direction);


int nentries = tree->GetEntries();

TFile *fout = new TFile(file_selectroot, "recreate");
for ( int ientry = 0; ientry < nentries; ientry++ )
{
  tree->GetEntry( ientry );
    

    for (int inum=0; inum<n ; inum++){
    
        if( icam[inum] == 0 ){
            hx1->Fill(xsize[inum]);
            hy1->Fill(ysize[inum]);
        }else if(icam[inum] == 1){
            hx2->Fill(xsize[inum]);
            hy2->Fill(ysize[inum]);
        }else if(icam[inum] == 2){
            hx3->Fill(xsize[inum]);
            hy3->Fill(ysize[inum]);
        }    
     }



        double hx1Mean = hx1->GetMean();
        double hx2Mean = hx2->GetMean();
        double hx3Mean = hx3->GetMean();
        double hy1Mean = hy1->GetMean();
        double hy2Mean = hy2->GetMean();
        double hy3Mean = hy3->GetMean();

        double xholesub_mean[12];
        double yholesub_mean[12];

        double xholepol[12][2];
        double yholepol[12][2];
        
        xholesub_mean[0] = 0;
        xholesub_mean[1] = 7.97e-04;
        xholesub_mean[2] =-6.80e-03;
        xholesub_mean[3] =-8.50e-03;
        xholesub_mean[4] =-4.11e-03;
        xholesub_mean[5] =-1.38e-03;
        xholesub_mean[6] =-1.36e-03;
        xholesub_mean[7] =-4.32e-03; 
        xholesub_mean[8] =-3.60e-04;
        xholesub_mean[9] =-3.50e-03;
        xholesub_mean[10]=-5.07e-03;
        xholesub_mean[11]=-4.21e-04;
                         
        yholesub_mean[0] =0; 
        yholesub_mean[1] =7.81e-03; 
        yholesub_mean[2] =9.69e-03; 
        yholesub_mean[3] =1.71e-03; 
        yholesub_mean[4] =4.14e-03; 
        yholesub_mean[5] =4.50e-03; 
        yholesub_mean[6] =6.96e-03; 
        yholesub_mean[7] =6.66e-03; 
        yholesub_mean[8] =7.46e-03;
        yholesub_mean[9] =8.35e-03;
        yholesub_mean[10]=4.44e-03;
        yholesub_mean[11]=3.30e-03;

       xholepol[0][0] =   0.          ;
       xholepol[0][1] =   1.          ;

       yholepol[0][0] =   0.          ;
       yholepol[0][1] =   1.          ;
       
       xholepol[1][0] =   0.00459819  ; 
       xholepol[1][1] =     0.981188  ; 
                     
       yholepol[1][0] =   -0.0140855  ; 
       yholepol[1][1] =      1.02087  ; 
                     
       xholepol[2][0] =     0.044939  ; 
       xholepol[2][1] =     0.866894  ; 
                     
       yholepol[2][0] =   -0.0247102  ; 
       yholepol[2][1] =      1.05044  ; 
                     
       xholepol[3][0] =    0.0433587  ; 
       xholepol[3][1] =     0.878738  ; 
                     
       yholepol[3][0] =  0.000374197  ; 
       yholepol[3][1] =     0.992484  ; 
                     
       xholepol[4][0] =    0.0303134  ; 
       xholepol[4][1] =     0.908431  ; 
                     
       yholepol[4][0] =   0.00269006  ; 
       yholepol[4][1] =     0.976121  ; 
                     
       xholepol[5][0] =   0.00114458  ; 
       xholepol[5][1] =      1.00137  ; 
                     
       yholepol[5][0] =  -0.00785692  ; 
       yholepol[5][1] =      1.01092  ; 
                     
       xholepol[6][0] =   0.00148146  ; 
       xholepol[6][1] =     0.999732  ; 
                     
       yholepol[6][0] =   -0.0213255  ; 
       yholepol[6][1] =      1.04867  ; 
                     
       xholepol[7][0] =    0.0318278  ; 
       xholepol[7][1] =     0.904304  ; 
                     
       yholepol[7][0] =   -0.0223634  ; 
       yholepol[7][1] =      1.05296  ; 
                     
       xholepol[8][0] =  -0.00272114  ; 
       xholepol[8][1] =      1.01126  ; 
                     
       yholepol[8][0] =    -0.019677  ; 
       yholepol[8][1] =      1.04148  ; 
                     
       xholepol[9][0] =    0.0264552  ; 
       xholepol[9][1] =     0.919874  ; 
                     
       yholepol[9][0] =   -0.0232468  ; 
       yholepol[9][1] =      1.05064  ; 
                     
       xholepol[10][0] =    0.0357045 ; 
       xholepol[10][1] =     0.893129 ; 
                     
       yholepol[10][0] =  -0.00751501 ; 
       yholepol[10][1] =      1.00942 ; 
                     
       xholepol[11][0] =  -0.00329875 ; 
       xholepol[11][1] =      1.01302 ; 
                     
       yholepol[11][0] =  -0.00179705 ; 
       yholepol[11][1] =     0.994211 ; 
                     

        xholecor[0] = xholesub_mean[0] + xhole[0]/hx1Mean;
        xholecor[2] = xholesub_mean[2] + (xsize[2]-xhole[2])/hx1Mean;
        xholecor[1] = xholesub_mean[1] + xhole[1]/hx1Mean; 
        xholecor[3] = xholesub_mean[3] + (xsize[3]-xhole[3])/hx1Mean;
        xholecor[6] = xholesub_mean[6] + xhole[6]/hx2Mean; 
        xholecor[4] = xholesub_mean[4] + (xsize[4]-xhole[4])/hx2Mean;
        xholecor[5] = xholesub_mean[5] + xhole[5]/hx2Mean; 
        xholecor[7] = xholesub_mean[7] + (xsize[7]-xhole[7])/hx2Mean;
        xholecor[8] = xholesub_mean[8] + xhole[8]/hx3Mean; 
        xholecor[10] = xholesub_mean[10] + (xsize[10]-xhole[10])/hx3Mean;
        xholecor[11] = xholesub_mean[11] + xhole[11]/hx3Mean; 
        xholecor[9] = xholesub_mean[9] + (xsize[9]-xhole[9])/hx3Mean;

        yholecor[2] = yholesub_mean[2] + yhole[2]/hy1Mean; 
        yholecor[0] = yholesub_mean[0] + (ysize[0]-yhole[0])/hy1Mean;
        yholecor[1] = yholesub_mean[1] + yhole[1]/hy1Mean; 
        yholecor[3] = yholesub_mean[3] + (ysize[3]-yhole[3])/hy1Mean;
        yholecor[6] = yholesub_mean[6] + yhole[6]/hy2Mean; 
        yholecor[4] = yholesub_mean[4] + (ysize[4]-yhole[4])/hy2Mean;
        yholecor[7] = yholesub_mean[7] + yhole[7]/hy2Mean; 
        yholecor[5] = yholesub_mean[5] + (ysize[5]-yhole[5])/hy2Mean;
        yholecor[8] = yholesub_mean[8] + yhole[8]/hy3Mean; 
        yholecor[10] = yholesub_mean[10] + (ysize[10]-yhole[10])/hy3Mean;
        yholecor[9] = yholesub_mean[9] + yhole[9]/hy3Mean; 
        yholecor[11] = yholesub_mean[11] + (ysize[11]-yhole[11])/hy3Mean;

        xholecor3[0] =  ((xhole[0]/hx1Mean             )-xholepol[0][0])/xholepol[0][1];
        xholecor3[2] =  (((xsize[2]-xhole[2])/hx1Mean  )-xholepol[2][0])/xholepol[2][1];
        xholecor3[1] =  ((xhole[1]/hx1Mean             )-xholepol[1][0])/xholepol[1][1];                                  
        xholecor3[3] =  (((xsize[3]-xhole[3])/hx1Mean  )-xholepol[3][0])/xholepol[3][1];
        xholecor3[6] =  ((xhole[6]/hx2Mean             )-xholepol[6][0])/xholepol[6][1]; 
        xholecor3[4] =  (((xsize[4]-xhole[4])/hx2Mean  )-xholepol[4][0])/xholepol[4][1];
        xholecor3[5] =  ((xhole[5]/hx2Mean             )-xholepol[5][0])/xholepol[5][1]; 
        xholecor3[7] =  (((xsize[7]-xhole[7])/hx2Mean  )-xholepol[7][0])/xholepol[7][1];
        xholecor3[8] =  ((xhole[8]/hx3Mean             )-xholepol[8][0])/xholepol[8][1]; 
        xholecor3[10] = (((xsize[10]-xhole[10])/hx3Mean)-xholepol[10][0])/xholepol[10][1];
        xholecor3[11] = ((xhole[11]/hx3Mean            )-xholepol[11][0])/xholepol[11][1]; 
        xholecor3[9] =  (((xsize[9]-xhole[9])/hx3Mean  )-xholepol[9][0])/xholepol[9][1];

        yholecor3[2] =  ((yhole[2]/hy1Mean             )-yholepol[2][0])/yholepol[2][1]; 
        yholecor3[0] =  (((ysize[0]-yhole[0])/hy1Mean  )-yholepol[0][0])/yholepol[0][1];
        yholecor3[1] =  ((yhole[1]/hy1Mean             )-yholepol[1][0])/yholepol[1][1]; 
        yholecor3[3] =  (((ysize[3]-yhole[3])/hy1Mean  )-yholepol[3][0])/yholepol[3][1];
        yholecor3[6] =  ((yhole[6]/hy2Mean             )-yholepol[6][0])/yholepol[6][1]; 
        yholecor3[4] =  (((ysize[4]-yhole[4])/hy2Mean  )-yholepol[4][0])/yholepol[4][1];
        yholecor3[7] =  ((yhole[7]/hy2Mean             )-yholepol[7][0])/yholepol[7][1]; 
        yholecor3[5] =  (((ysize[5]-yhole[5])/hy2Mean  )-yholepol[5][0])/yholepol[5][1];
        yholecor3[8] =  ((yhole[8]/hy3Mean             )-yholepol[8][0])/yholepol[8][1]; 
        yholecor3[10] = (((ysize[10]-yhole[10])/hy3Mean)-yholepol[10][0])/yholepol[10][1];
        yholecor3[9] =  ((yhole[9]/hy3Mean             )-yholepol[9][0])/yholepol[9][1]; 
        yholecor3[11] = (((ysize[11]-yhole[11])/hy3Mean)-yholepol[11][0])/yholepol[11][1];




        for (int i12=0; i12<12; i12++){
            if(icam[i12]==0){
                if(direction[i12]==0 or direction[i12]==1){
                hid_xhole[ientry/6][ientry%6]->Fill(xhole[i12]/hx1Mean);
                }else{
                hid_xhole[ientry/6][ientry%6]->Fill((xsize[i12]-xhole[i12])/hx1Mean);
                }
                if(direction[i12]==0 or direction[i12]==3){
                hid_yhole[ientry/6][ientry%6]->Fill((ysize[i12]-yhole[i12])/hy1Mean);
                }else{
                hid_yhole[ientry/6][ientry%6]->Fill(yhole[i12]/hy1Mean);
                }
            }
            else if (icam[i12]==1){
                if(direction[i12]==2 or direction[i12]==3){
                hid_xhole[ientry/6][ientry%6]->Fill(xhole[i12]/hx1Mean);
                }else{
                hid_xhole[ientry/6][ientry%6]->Fill((xsize[i12]-xhole[i12])/hx1Mean);
                }
                if(direction[i12]==0 or direction[i12]==3){
                hid_yhole[ientry/6][ientry%6]->Fill((ysize[i12]-yhole[i12])/hy1Mean);
                }else{
                hid_yhole[ientry/6][ientry%6]->Fill(yhole[i12]/hy1Mean);
                }
            }
            else if (icam[i12]==2){
                if(direction[i12]==0 or direction[i12]==1){
                hid_xhole[ientry/6][ientry%6]->Fill(xhole[i12]/hx1Mean);
                }else{
                hid_xhole[ientry/6][ientry%6]->Fill((xsize[i12]-xhole[i12])/hx1Mean);
                }
                if(direction[i12]==1 or direction[i12]==2){
                hid_yhole[ientry/6][ientry%6]->Fill((ysize[i12]-yhole[i12])/hy1Mean);
                }else{
                hid_yhole[ientry/6][ientry%6]->Fill(yhole[i12]/hy1Mean);
                }
            }
        hid_xholecor3[ientry/6][ientry%6]->Fill(xholecor3[i12]);     
        hid_yholecor3[ientry/6][ientry%6]->Fill(yholecor3[i12]);     
        }
        hid_xhole2D[ientry/6][ientry%6]->Fill(xhole[0]/hx1Mean, (xsize[2]-xhole[2])/hx1Mean);
        hid_xhole2D[ientry/6][ientry%6]->Fill(xhole[1]/hx1Mean, (xsize[3]-xhole[3])/hx1Mean);
        hid_xhole2D[ientry/6][ientry%6]->Fill(xhole[6]/hx2Mean, (xsize[4]-xhole[4])/hx2Mean);
        hid_xhole2D[ientry/6][ientry%6]->Fill(xhole[5]/hx2Mean, (xsize[7]-xhole[7])/hx2Mean);
        hid_xhole2D[ientry/6][ientry%6]->Fill(xhole[8]/hx3Mean, (xsize[10]-xhole[10])/hx3Mean);
        hid_xhole2D[ientry/6][ientry%6]->Fill(xhole[11]/hx3Mean, (xsize[9]-xhole[9])/hx3Mean);
        
        hid_yhole2D[ientry/6][ientry%6]->Fill(yhole[2]/hy1Mean, (ysize[0]-yhole[0])/hy1Mean);
        hid_yhole2D[ientry/6][ientry%6]->Fill(yhole[1]/hy1Mean, (ysize[3]-yhole[3])/hy1Mean);
        hid_yhole2D[ientry/6][ientry%6]->Fill(yhole[6]/hy2Mean, (ysize[4]-yhole[4])/hy2Mean);
        hid_yhole2D[ientry/6][ientry%6]->Fill(yhole[7]/hy2Mean, (ysize[5]-yhole[5])/hy2Mean);
        hid_yhole2D[ientry/6][ientry%6]->Fill(yhole[8]/hy3Mean, (ysize[10]-yhole[10])/hy3Mean);
        hid_yhole2D[ientry/6][ientry%6]->Fill(yhole[9]/hy3Mean, (ysize[11]-yhole[11])/hy3Mean);

        hid_xhole2D[ientry/6][ientry%6]->SetMarkerStyle(6);
        hid_yhole2D[ientry/6][ientry%6]->SetMarkerStyle(6);

        hid_xhole2D[ientry/6][ientry%6]->Fit(xpol1[ientry/6][ientry%6]);
        std::cout << "xhole: "<< ientry/6 << ientry%6 << std::endl;
        xholep0[ientry/6][ientry%6] = xpol1[ientry/6][ientry%6]->GetParameter(0);
        xholep1[ientry/6][ientry%6] = xpol1[ientry/6][ientry%6]->GetParameter(1);


        hid_yhole2D[ientry/6][ientry%6]->Fit(ypol1[ientry/6][ientry%6]);
        std::cout << "yhole: "<< ientry/6 << ientry%6 << std::endl;
        yholep0[ientry/6][ientry%6] = ypol1[ientry/6][ientry%6]->GetParameter(0);
        yholep1[ientry/6][ientry%6] = ypol1[ientry/6][ientry%6]->GetParameter(1);
        




        h_shade_shine->Fill(xhole[0]/hx1Mean, (xsize[2]-xhole[2])/hx1Mean);
        h_shade_shine->Fill(xhole[1]/hx1Mean, (xsize[3]-xhole[3])/hx1Mean);
        h_shade_shine->Fill(xhole[6]/hx2Mean, (xsize[4]-xhole[4])/hx2Mean);
        h_shade_shine->Fill(xhole[5]/hx2Mean, (xsize[7]-xhole[7])/hx2Mean);
        h_shade_shine->Fill(xhole[8]/hx3Mean, (xsize[10]-xhole[10])/hx3Mean);
        h_shade_shine->Fill(xhole[11]/hx3Mean, (xsize[9]-xhole[9])/hx3Mean);
        
        h_shade_shine1->Fill(xhole[0]/hx1Mean, (xsize[2]-xhole[2])/hx1Mean);
        h_shade_shine1->Fill(xhole[1]/hx1Mean, (xsize[3]-xhole[3])/hx1Mean);
        h_shade_shine2->Fill(xhole[6]/hx2Mean, (xsize[4]-xhole[4])/hx2Mean);
        h_shade_shine2->Fill(xhole[5]/hx2Mean, (xsize[7]-xhole[7])/hx2Mean);
        h_shade_shine3->Fill(xhole[8]/hx3Mean, (xsize[10]-xhole[10])/hx3Mean);
        h_shade_shine3->Fill(xhole[11]/hx3Mean, (xsize[9]-xhole[9])/hx3Mean);
        
        h_shade_shine->Fill(yhole[2]/hy1Mean, (ysize[0]-yhole[0])/hy1Mean);
        h_shade_shine->Fill(yhole[1]/hy1Mean, (ysize[3]-yhole[3])/hy1Mean);
        h_shade_shine->Fill(yhole[6]/hy2Mean, (ysize[4]-yhole[4])/hy2Mean);
        h_shade_shine->Fill(yhole[7]/hy2Mean, (ysize[5]-yhole[5])/hy2Mean);
        h_shade_shine->Fill(yhole[8]/hy3Mean, (ysize[10]-yhole[10])/hy3Mean);
        h_shade_shine->Fill(yhole[9]/hy3Mean, (ysize[11]-yhole[11])/hy3Mean);

        h_shade_shine1->Fill(yhole[2]/hy1Mean, (ysize[0]-yhole[0])/hy1Mean);
        h_shade_shine1->Fill(yhole[1]/hy1Mean, (ysize[3]-yhole[3])/hy1Mean);
        h_shade_shine2->Fill(yhole[6]/hy2Mean, (ysize[4]-yhole[4])/hy2Mean);
        h_shade_shine2->Fill(yhole[7]/hy2Mean, (ysize[5]-yhole[5])/hy2Mean);
        h_shade_shine3->Fill(yhole[8]/hy3Mean, (ysize[10]-yhole[10])/hy3Mean);
        h_shade_shine3->Fill(yhole[9]/hy3Mean, (ysize[11]-yhole[11])/hy3Mean);
        
        h_shade_shine_cor2->Fill(xholecor[0], xholecor[2]);
        h_shade_shine_cor2->Fill(xholecor[1], xholecor[3]);
        h_shade_shine_cor2->Fill(xholecor[6], xholecor[4]);
        h_shade_shine_cor2->Fill(xholecor[5], xholecor[7]);
        h_shade_shine_cor2->Fill(xholecor[8], xholecor[10]);
        h_shade_shine_cor2->Fill(xholecor[11],xholecor[9]);
        
        h_shade_shine1_cor2->Fill(xholecor[0], xholecor[2]);
        h_shade_shine1_cor2->Fill(xholecor[1], xholecor[3]);
        h_shade_shine2_cor2->Fill(xholecor[6], xholecor[4]);
        h_shade_shine2_cor2->Fill(xholecor[5], xholecor[7]);
        h_shade_shine3_cor2->Fill(xholecor[8], xholecor[10]);
        h_shade_shine3_cor2->Fill(xholecor[11],xholecor[9]);
        
        h_shade_shine_cor2->Fill(yholecor[2], yholecor[0]);
        h_shade_shine_cor2->Fill(yholecor[1], yholecor[3]);
        h_shade_shine_cor2->Fill(yholecor[6], yholecor[4]);
        h_shade_shine_cor2->Fill(yholecor[7], yholecor[5]);
        h_shade_shine_cor2->Fill(yholecor[8], yholecor[10]);
        h_shade_shine_cor2->Fill(yholecor[9], yholecor[11]);

        h_shade_shine1_cor2->Fill(yholecor[2], yholecor[0]);
        h_shade_shine1_cor2->Fill(yholecor[1], yholecor[3]);
        h_shade_shine2_cor2->Fill(yholecor[6], yholecor[4]);
        h_shade_shine2_cor2->Fill(yholecor[7], yholecor[5]);
        h_shade_shine3_cor2->Fill(yholecor[8], yholecor[10]);
        h_shade_shine3_cor2->Fill(yholecor[9], yholecor[11]);
        
        h_shade_shine_cor3->Fill(xholecor3[0], xholecor3[2]);
        h_shade_shine_cor3->Fill(xholecor3[1], xholecor3[3]);
        h_shade_shine_cor3->Fill(xholecor3[6], xholecor3[4]);
        h_shade_shine_cor3->Fill(xholecor3[5], xholecor3[7]);
        h_shade_shine_cor3->Fill(xholecor3[8], xholecor3[10]);
        h_shade_shine_cor3->Fill(xholecor3[11],xholecor3[9]);
        
        h_shade_shine1_cor3->Fill(xholecor3[0], xholecor3[2]);
        h_shade_shine1_cor3->Fill(xholecor3[1], xholecor3[3]);
        h_shade_shine2_cor3->Fill(xholecor3[6], xholecor3[4]);
        h_shade_shine2_cor3->Fill(xholecor3[5], xholecor3[7]);
        h_shade_shine3_cor3->Fill(xholecor3[8], xholecor3[10]);
        h_shade_shine3_cor3->Fill(xholecor3[11],xholecor3[9]);
        
        h_shade_shine_cor3->Fill(yholecor3[2], yholecor3[0]);
        h_shade_shine_cor3->Fill(yholecor3[1], yholecor3[3]);
        h_shade_shine_cor3->Fill(yholecor3[6], yholecor3[4]);
        h_shade_shine_cor3->Fill(yholecor3[7], yholecor3[5]);
        h_shade_shine_cor3->Fill(yholecor3[8], yholecor3[10]);
        h_shade_shine_cor3->Fill(yholecor3[9], yholecor3[11]);

        h_shade_shine1_cor3->Fill(yholecor3[2], yholecor3[0]);
        h_shade_shine1_cor3->Fill(yholecor3[1], yholecor3[3]);
        h_shade_shine2_cor3->Fill(yholecor3[6], yholecor3[4]);
        h_shade_shine2_cor3->Fill(yholecor3[7], yholecor3[5]);
        h_shade_shine3_cor3->Fill(yholecor3[8], yholecor3[10]);
        h_shade_shine3_cor3->Fill(yholecor3[9], yholecor3[11]);
        

        h_xhole[0]->Fill(xhole[0]/hx1Mean, xhole[0]/hx1Mean);
        h_xhole[1]->Fill(xhole[0]/hx1Mean, xhole[1]/hx1Mean);
        h_xhole[2]->Fill(xhole[0]/hx1Mean, (xsize[2]-xhole[2])/hx1Mean);
        h_xhole[3]->Fill(xhole[0]/hx1Mean, (xsize[3]-xhole[3])/hx1Mean);
        h_xhole[4]->Fill(xhole[0]/hx1Mean, (xsize[4]-xhole[4])/hx2Mean);
        h_xhole[5]->Fill(xhole[0]/hx1Mean, xhole[5]/hx2Mean);
        h_xhole[6]->Fill(xhole[0]/hx1Mean, xhole[6]/hx2Mean);
        h_xhole[7]->Fill(xhole[0]/hx1Mean, (xsize[7]-xhole[7])/hx2Mean);
        h_xhole[8]->Fill(xhole[0]/hx1Mean, xhole[8]/hx3Mean);
        h_xhole[9]->Fill(xhole[0]/hx1Mean, (xsize[9]-xhole[9])/hx3Mean);
        h_xhole[10]->Fill(xhole[0]/hx1Mean, (xsize[10]-xhole[10])/hx3Mean);
        h_xhole[11]->Fill(xhole[0]/hx1Mean, xhole[11]/hx3Mean);

        h_yhole[0]->Fill((ysize[0]-yhole[0])/hy1Mean, (ysize[0]-yhole[0])/hy1Mean);
        h_yhole[1]->Fill((ysize[0]-yhole[0])/hy1Mean, yhole[1]/hy1Mean);
        h_yhole[2]->Fill((ysize[0]-yhole[0])/hy1Mean, yhole[2]/hy1Mean);
        h_yhole[3]->Fill((ysize[0]-yhole[0])/hy1Mean, (ysize[3]-yhole[3])/hy1Mean);
        h_yhole[4]->Fill((ysize[0]-yhole[0])/hy1Mean, (ysize[4]-yhole[4])/hy2Mean);
        h_yhole[5]->Fill((ysize[0]-yhole[0])/hy1Mean, (ysize[5]-yhole[5])/hy2Mean);
        h_yhole[6]->Fill((ysize[0]-yhole[0])/hy1Mean, yhole[6]/hy2Mean);
        h_yhole[7]->Fill((ysize[0]-yhole[0])/hy1Mean, yhole[7]/hy2Mean);
        h_yhole[8]->Fill((ysize[0]-yhole[0])/hy1Mean, yhole[8]/hy3Mean);
        h_yhole[9]->Fill((ysize[0]-yhole[0])/hy1Mean, yhole[9]/hy3Mean);
        h_yhole[10]->Fill((ysize[0]-yhole[0])/hy1Mean, (ysize[10]-yhole[10])/hy3Mean);
        h_yhole[11]->Fill((ysize[0]-yhole[0])/hy1Mean, (ysize[11]-yhole[11])/hy3Mean);

        h_xholesub[0]->Fill(xhole[0]/hx1Mean - xhole[0]/hx1Mean);
        h_xholesub[1]->Fill(xhole[0]/hx1Mean - xhole[1]/hx1Mean);
        h_xholesub[2]->Fill(xhole[0]/hx1Mean - (xsize[2]-xhole[2])/hx1Mean);
        h_xholesub[3]->Fill(xhole[0]/hx1Mean - (xsize[3]-xhole[3])/hx1Mean);
        h_xholesub[4]->Fill(xhole[0]/hx1Mean - (xsize[4]-xhole[4])/hx2Mean);
        h_xholesub[5]->Fill(xhole[0]/hx1Mean - xhole[5]/hx2Mean);
        h_xholesub[6]->Fill(xhole[0]/hx1Mean - xhole[6]/hx2Mean);
        h_xholesub[7]->Fill(xhole[0]/hx1Mean - (xsize[7]-xhole[7])/hx2Mean);
        h_xholesub[8]->Fill(xhole[0]/hx1Mean - xhole[8]/hx3Mean);
        h_xholesub[9]->Fill(xhole[0]/hx1Mean - (xsize[9]-xhole[9])/hx3Mean);
        h_xholesub[10]->Fill(xhole[0]/hx1Mean - (xsize[10]-xhole[10])/hx3Mean);
        h_xholesub[11]->Fill(xhole[0]/hx1Mean - xhole[11]/hx3Mean);

        h_yholesub[0]->Fill((ysize[0]-yhole[0])/hy1Mean - (ysize[0]-yhole[0])/hy1Mean);
        h_yholesub[1]->Fill((ysize[0]-yhole[0])/hy1Mean - yhole[1]/hy1Mean);
        h_yholesub[2]->Fill((ysize[0]-yhole[0])/hy1Mean - yhole[2]/hy1Mean);
        h_yholesub[3]->Fill((ysize[0]-yhole[0])/hy1Mean - (ysize[3]-yhole[3])/hy1Mean);
        h_yholesub[4]->Fill((ysize[0]-yhole[0])/hy1Mean - (ysize[4]-yhole[4])/hy2Mean);
        h_yholesub[5]->Fill((ysize[0]-yhole[0])/hy1Mean - (ysize[5]-yhole[5])/hy2Mean);
        h_yholesub[6]->Fill((ysize[0]-yhole[0])/hy1Mean - yhole[6]/hy2Mean);
        h_yholesub[7]->Fill((ysize[0]-yhole[0])/hy1Mean - yhole[7]/hy2Mean);
        h_yholesub[8]->Fill((ysize[0]-yhole[0])/hy1Mean - yhole[8]/hy3Mean);
        h_yholesub[9]->Fill((ysize[0]-yhole[0])/hy1Mean - yhole[9]/hy3Mean);
        h_yholesub[10]->Fill((ysize[0]-yhole[0])/hy1Mean - (ysize[10]-yhole[10])/hy3Mean);
        h_yholesub[11]->Fill((ysize[0]-yhole[0])/hy1Mean - (ysize[11]-yhole[11])/hy3Mean);

        h_xholesubcor[0]->Fill(xhole[0]/hx1Mean - xholecor[0]);
        h_xholesubcor[1]->Fill(xhole[0]/hx1Mean - xholecor[1]);
        h_xholesubcor[2]->Fill(xhole[0]/hx1Mean - xholecor[2]);
        h_xholesubcor[3]->Fill(xhole[0]/hx1Mean - xholecor[3]);
        h_xholesubcor[4]->Fill(xhole[0]/hx1Mean - xholecor[4]);
        h_xholesubcor[5]->Fill(xhole[0]/hx1Mean - xholecor[5]);
        h_xholesubcor[6]->Fill(xhole[0]/hx1Mean - xholecor[6]);
        h_xholesubcor[7]->Fill(xhole[0]/hx1Mean - xholecor[7]);
        h_xholesubcor[8]->Fill(xhole[0]/hx1Mean - xholecor[8]);
        h_xholesubcor[9]->Fill(xhole[0]/hx1Mean - xholecor[9]);
        h_xholesubcor[10]->Fill(xhole[0]/hx1Mean - xholecor[10]);
        h_xholesubcor[11]->Fill(xhole[0]/hx1Mean - xholecor[11]);

        h_yholesubcor[0]->Fill((ysize[0]-yhole[0])/hy1Mean - yholecor[0]);
        h_yholesubcor[1]->Fill((ysize[0]-yhole[0])/hy1Mean - yholecor[1]);
        h_yholesubcor[2]->Fill((ysize[0]-yhole[0])/hy1Mean - yholecor[2]);
        h_yholesubcor[3]->Fill((ysize[0]-yhole[0])/hy1Mean - yholecor[3]);
        h_yholesubcor[4]->Fill((ysize[0]-yhole[0])/hy1Mean - yholecor[4]);
        h_yholesubcor[5]->Fill((ysize[0]-yhole[0])/hy1Mean - yholecor[5]);
        h_yholesubcor[6]->Fill((ysize[0]-yhole[0])/hy1Mean - yholecor[6]);
        h_yholesubcor[7]->Fill((ysize[0]-yhole[0])/hy1Mean - yholecor[7]);
        h_yholesubcor[8]->Fill((ysize[0]-yhole[0])/hy1Mean - yholecor[8]);
        h_yholesubcor[9]->Fill((ysize[0]-yhole[0])/hy1Mean - yholecor[9]);
        h_yholesubcor[10]->Fill((ysize[0]-yhole[0])/hy1Mean - yholecor[10]);
        h_yholesubcor[11]->Fill((ysize[0]-yhole[0])/hy1Mean - yholecor[11]);


        h_shade_shine->SetMarkerStyle(6);    
        h_shade_shine1->SetMarkerStyle(6);    
        h_shade_shine2->SetMarkerStyle(6);    
        h_shade_shine3->SetMarkerStyle(6);    
        h_shade_shine_cor2->SetMarkerStyle(6);    
        h_shade_shine1_cor2->SetMarkerStyle(6);    
        h_shade_shine2_cor2->SetMarkerStyle(6);    
        h_shade_shine3_cor2->SetMarkerStyle(6);    
        h_shade_shine_cor3->SetMarkerStyle(6);    
        h_shade_shine1_cor3->SetMarkerStyle(6);    
        h_shade_shine2_cor3->SetMarkerStyle(6);    
        h_shade_shine3_cor3->SetMarkerStyle(6);    
        
        hid_xhole[ientry/6][ientry%6]->Write(); 
        hid_yhole[ientry/6][ientry%6]->Write(); 
        hid_xholecor3[ientry/6][ientry%6]->Write(); 
        hid_yholecor3[ientry/6][ientry%6]->Write(); 
        hxholeDev->Fill(hid_xhole[ientry/6][ientry%6]->GetStdDev());
        hyholeDev->Fill(hid_yhole[ientry/6][ientry%6]->GetStdDev());
        hxholeDevcor3->Fill(hid_xholecor3[ientry/6][ientry%6]->GetStdDev());
        hyholeDevcor3->Fill(hid_yholecor3[ientry/6][ientry%6]->GetStdDev());
        hid_xhole2D[ientry/6][ientry%6]->Write();
        hid_yhole2D[ientry/6][ientry%6]->Write();
        
        hxholeMean->Fill(hid_xhole[ientry/6][ientry%6]->GetMean());
        hyholeMean->Fill(hid_yhole[ientry/6][ientry%6]->GetMean());



        hid_xholeMean[ientry/6][ientry%6] = hid_xholecor3[ientry/6][ientry%6]->GetMean();
        hid_yholeMean[ientry/6][ientry%6] = hid_yholecor3[ientry/6][ientry%6]->GetMean();

        hxholeMeancor3->Fill(hid_xholeMean[ientry/6][ientry%6]);
        hyholeMeancor3->Fill(hid_yholeMean[ientry/6][ientry%6]);


}
        for(int roop28 = 0;roop28<28; roop28++){
            hid_xmax[roop28] = hid_xholeMean[roop28][0];
            hid_ymax[roop28] = hid_yholeMean[roop28][0];
            xsubtra[roop28]  = fabs( hid_xholeMean[roop28][0] - 0.286);
            ysubtra[roop28]  = fabs( hid_yholeMean[roop28][0] - 0.292);
    
            for(int decidemax = 1; decidemax<6; decidemax++){
                if(xsubtra[roop28] < fabs(hid_xholeMean[roop28][decidemax] - 0.286)){
                    xsubtra[roop28] = fabs(hid_xholeMean[roop28][decidemax]- 0.286);
                    hid_xmax[roop28] = hid_xholeMean[roop28][decidemax];}
                if(ysubtra[roop28] < fabs(hid_yholeMean[roop28][decidemax] - 0.292)){
                    ysubtra[roop28] = fabs(hid_yholeMean[roop28][decidemax]- 0.292);
                    hid_ymax[roop28] = hid_yholeMean[roop28][decidemax];}
            }
        
           hxholeRep ->Fill(xsubtra[roop28]);
           hyholeRep ->Fill(ysubtra[roop28]);
        }

        TString  xprint[12];
        TString  yprint[12];
        TCanvas * c2 = new TCanvas("c2","c2");
        for (int che11=0;che11<12;che11++){
            h_xhole[che11]->SetMarkerStyle(6);
            h_yhole[che11]->SetMarkerStyle(6);
            h_xhole[che11]->Write();
            h_yhole[che11]->Write();

           /* 
            h_xholesub[che11]->Fit("gaus","","",-0.025,0.025);
            xprint[che11] = "PDFs/h_xholesub"+std::to_string(che11)+".pdf";
            c2->Print(xprint[che11]);

            h_yholesub[che11]->Fit("gaus","","",-0.025,0.025);
            yprint[che11] = "PDFs/h_yholesub"+std::to_string(che11)+".pdf";
            c2->Print(yprint[che11]);
            h_xholesub[che11]->Write();
            h_yholesub[che11]->Write();
            */
            h_xholesubcor[che11]->Write();
            h_yholesubcor[che11]->Write();
        }

//tree->Write();
h_shade_shine->Write();
h_shade_shine1->Write();
h_shade_shine2->Write();
h_shade_shine3->Write();
h_shade_shine_cor2->Write();
h_shade_shine1_cor2->Write();
h_shade_shine2_cor2->Write();
h_shade_shine3_cor2->Write();
h_shade_shine_cor3->Write();
h_shade_shine1_cor3->Write();
h_shade_shine2_cor3->Write();
h_shade_shine3_cor3->Write();
hx1->Write();
hx2->Write();
hx3->Write();
hy1->Write();
hy2->Write();
hy3->Write();
hxholeDev->Write();
hyholeDev->Write();
hxholeDevcor3->Write();
hyholeDevcor3->Write();

hxholeMean->Write();
hyholeMean->Write();
hxholeMeancor3->Write();
hyholeMeancor3->Write();

hxholeRep->Write();
hyholeRep->Write();

fout->Close();




}
