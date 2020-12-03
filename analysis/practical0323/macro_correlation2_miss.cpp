#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>

void macro_correlation2_miss(){



TString dumpdate      = "0401";
TString histdate      = "0403";
TString readroot  = "_2.root";
TString selectroot= "miss_1correlation.root";
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
TString id_xsize[28][6];
TH1D* hid_xsize[28][6];
for (int i28=0; i28<28; i28++){
    for (int i6=0; i6<6; i6++){
        id_xsize[i28][i6] = "hid_xsize"+std::to_string(i28)+std::to_string(i6);
        hid_xsize[i28][i6]= new TH1D(id_xsize[i28][i6],"xsize",100,0.9,1.1);
    }
}
TH1D* hxDev = new TH1D("hxDev","xsize_Std_Dev",100,0, 0.01);


TString id_ysize[28][6];
TH1D* hid_ysize[28][6];
for (int i28=0; i28<28; i28++){
    for (int i6=0; i6<6; i6++){
        id_ysize[i28][i6] = "hid_ysize"+std::to_string(i28)+std::to_string(i6);
        hid_ysize[i28][i6]= new TH1D(id_ysize[i28][i6],"ysize",100,0.9,1.1);
    }
}
TH1D* hyDev = new TH1D("hyDev","ysize_Std_Dev",100,0, 0.01);

TString id_xhole[28][6];
TH1D* hid_xhole[28][6];
for (int i28=0; i28<28; i28++){
    for (int i6=0; i6<6; i6++){
        id_xhole[i28][i6] = "hid_xhole"+std::to_string(i28)+std::to_string(i6);
        hid_xhole[i28][i6]= new TH1D(id_xhole[i28][i6],"xhole",100,0.2,0.4);
    }
}
TH1D* hxholeDev = new TH1D("hxholeDev","xhole_Std_Dev",100,0, 0.01);

TString id_yhole[28][6];
TH1D* hid_yhole[28][6];
for (int i28=0; i28<28; i28++){
    for (int i6=0; i6<6; i6++){
        id_yhole[i28][i6] = "hid_yhole"+std::to_string(i28)+std::to_string(i6);
        hid_yhole[i28][i6]= new TH1D(id_yhole[i28][i6],"yhole",100,0.2,0.4);
    }
}
TH1D* hyholeDev = new TH1D("hyholeDev","yhole_Std_Dev",100,0, 0.01);

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


TH1D* hist_shade = new TH1D("hist_shade","hole_shade",100,0.2,0.4);
TH1D* hist_shine = new TH1D("hist_shine","hole_shine",100,0.2,0.4);
TH2D* h_shade_shine = new TH2D("h_shade_shine","shade_shine;shade;shine",1000,0,1,1000,0,1);
TH2D* h_shade_shine_cor = new TH2D("h_shade_shine_cor","shade_shine;shade;shine_cor",1000,0,1,1000,0,1);
TH2D* h_holecam12    = new TH2D("h_holecam12","cam12;cam1;cam2",100,0.2,0.4,100,0.2,0.4);
TH2D* h_holecam23    = new TH2D("h_holecam23","cam23;cam2;cam3",100,0.2,0.4,100,0.2,0.4);
TH2D* h_holecam13    = new TH2D("h_holecam13","cam13;cam1;cam3",100,0.2,0.4,100,0.2,0.4);


TH2D* h_sizecam12    = new TH2D("h_sizecam12","cam12;cam1;cam2",100,0.2,0.4,100,640,690);
TH2D* h_sizecam23    = new TH2D("h_sizecam23","cam23;cam2;cam3",100,0.2,0.4,100,640,690);
TH2D* h_sizecam13    = new TH2D("h_sizecam13","cam13;cam1;cam3",100,0.2,0.4,100,640,690);

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

TString id_xhole2Dcor[28][6];
TH2D* hid_xhole2Dcor[28][6];
for (int i28=0; i28<28; i28++){
    for (int i6=0; i6<6; i6++){
        id_xhole2Dcor[i28][i6] = "hid_xhole2Dcor"+std::to_string(i28)+std::to_string(i6);
        hid_xhole2Dcor[i28][i6]= new TH2D(id_xhole2Dcor[i28][i6],"xhole2Dcor;shade(xhole/Mean(xsize));shine(xhole/Mean(xsize))",100,0.25,0.35, 100,0.25,0.35);
    }
}
TString id_yhole2Dcor[28][6];
TH2D* hid_yhole2Dcor[28][6];
for (int i28=0; i28<28; i28++){
    for (int i6=0; i6<6; i6++){
        id_yhole2Dcor[i28][i6] = "hid_yhole2Dcor"+std::to_string(i28)+std::to_string(i6);
        hid_yhole2Dcor[i28][i6]= new TH2D(id_yhole2Dcor[i28][i6],"yhole2Dcor;shade(yhole/Mean(ysize));shine(yhole/Mean(ysize))",100,0.25,0.35, 100,0.25,0.35);
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
Double_t xholerate[n];
Double_t yholerate[n];
Int_t icam[n];
Int_t direction[n];
Double_t xholep0[28][6];
Double_t xholep1[28][6];
Double_t yholep0[28][6];
Double_t yholep1[28][6];

TString id_xholepol[28][6];
TF1* xpol1[28][6];
for (int i28=0; i28<28; i28++){
    for (int i6=0; i6<6; i6++){
        id_xholepol[i28][i6] = "id_xholepol"+std::to_string(i28)+std::to_string(i6);
        xpol1[i28][i6]= new TF1(id_xholepol[i28][i6],"[0]+x*[1]",0.2,0.4);
    }
}
TString id_yholepol[28][6];
TF1* ypol1[28][6];
for (int i28=0; i28<28; i28++){
    for (int i6=0; i6<6; i6++){
        id_yholepol[i28][i6] = "id_yholepol"+std::to_string(i28)+std::to_string(i6);
        ypol1[i28][i6]= new TF1(id_yholepol[i28][i6],"[0]+x*[1]",0.2,0.4);
    }
}


Double_t shade=0.;
Double_t shine=0.;

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
    
        h1->Fill(radius[inum]);
        h2->Fill(xhole[inum]);
        h3->Fill(yhole[inum]);
        h4->Fill(xsize[inum]);
        h5->Fill(ysize[inum]);
        hE->Fill(Esum[inum]);
        hb->Fill(bump[inum]);
        

    
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



    /*
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
    */
        double hx1Mean = hx1->GetMean();
        double hx2Mean = hx2->GetMean();
        double hx3Mean = hx3->GetMean();
        double hy1Mean = hy1->GetMean();
        double hy2Mean = hy2->GetMean();
        double hy3Mean = hy3->GetMean();
        for (int i12=0; i12<12; i12++){
            if(icam[i12]==0){
            hid_xsize[ientry/6][ientry%6]->Fill(xsize[i12]/hx1Mean);
            hid_ysize[ientry/6][ientry%6]->Fill(ysize[i12]/hy1Mean);
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
            hid_xsize[ientry/6][ientry%6]->Fill(xsize[i12]/(hx2->GetMean()));
            hid_ysize[ientry/6][ientry%6]->Fill(ysize[i12]/(hy2->GetMean()));
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
            hid_xsize[ientry/6][ientry%6]->Fill(xsize[i12]/(hx3->GetMean()));
            hid_ysize[ientry/6][ientry%6]->Fill(ysize[i12]/(hy3->GetMean()));
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
        



        hid_xhole2Dcor[ientry/6][ientry%6]->Fill(xhole[0]/hx1Mean, (((xsize[2]-xhole[2])/hx1Mean)-xholep0[ientry/6][ientry%6])/xholep1[ientry/6][ientry%6]);
        hid_xhole2Dcor[ientry/6][ientry%6]->Fill(xhole[1]/hx1Mean, (((xsize[3]-xhole[3])/hx1Mean  )-xholep0[ientry/6][ientry%6])/xholep1[ientry/6][ientry%6]);
        hid_xhole2Dcor[ientry/6][ientry%6]->Fill(xhole[6]/hx2Mean, (((xsize[4]-xhole[4])/hx2Mean  )-xholep0[ientry/6][ientry%6])/xholep1[ientry/6][ientry%6]);
        hid_xhole2Dcor[ientry/6][ientry%6]->Fill(xhole[5]/hx2Mean, (((xsize[7]-xhole[7])/hx2Mean  )-xholep0[ientry/6][ientry%6])/xholep1[ientry/6][ientry%6]);
        hid_xhole2Dcor[ientry/6][ientry%6]->Fill(xhole[8]/hx3Mean, (((xsize[10]-xhole[10])/hx3Mean)-xholep0[ientry/6][ientry%6])/xholep1[ientry/6][ientry%6]);
        hid_xhole2Dcor[ientry/6][ientry%6]->Fill(xhole[11]/hx3Mean,(((xsize[9]-xhole[9])/hx3Mean  )-xholep0[ientry/6][ientry%6])/xholep1[ientry/6][ientry%6]);
        
        hid_yhole2Dcor[ientry/6][ientry%6]->Fill(yhole[2]/hy1Mean, (((ysize[0]-yhole[0])/hy1Mean  )-yholep0[ientry/6][ientry%6])/yholep1[ientry/6][ientry%6]);
        hid_yhole2Dcor[ientry/6][ientry%6]->Fill(yhole[1]/hy1Mean, (((ysize[3]-yhole[3])/hy1Mean  )-yholep0[ientry/6][ientry%6])/yholep1[ientry/6][ientry%6]);
        hid_yhole2Dcor[ientry/6][ientry%6]->Fill(yhole[6]/hy2Mean, (((ysize[4]-yhole[4])/hy2Mean  )-yholep0[ientry/6][ientry%6])/yholep1[ientry/6][ientry%6]);
        hid_yhole2Dcor[ientry/6][ientry%6]->Fill(yhole[7]/hy2Mean, (((ysize[5]-yhole[5])/hy2Mean  )-yholep0[ientry/6][ientry%6])/yholep1[ientry/6][ientry%6]);
        hid_yhole2Dcor[ientry/6][ientry%6]->Fill(yhole[8]/hy3Mean, (((ysize[10]-yhole[10])/hy3Mean)-yholep0[ientry/6][ientry%6])/yholep1[ientry/6][ientry%6]);
        hid_yhole2Dcor[ientry/6][ientry%6]->Fill(yhole[9]/hy3Mean, (((ysize[11]-yhole[11])/hy3Mean)-yholep0[ientry/6][ientry%6])/yholep1[ientry/6][ientry%6]);

        hid_xhole2Dcor[ientry/6][ientry%6]->SetMarkerStyle(6);
        hid_yhole2Dcor[ientry/6][ientry%6]->SetMarkerStyle(6);
        h_shade_shine_cor->Fill(xhole[0]/hx1Mean, (((xsize[2]-xhole[2])/hx1Mean)-xholep0[ientry/6][ientry%6])/xholep1[ientry/6][ientry%6]);
        h_shade_shine_cor->Fill(xhole[1]/hx1Mean, (((xsize[3]-xhole[3])/hx1Mean  )-xholep0[ientry/6][ientry%6])/xholep1[ientry/6][ientry%6]);
        h_shade_shine_cor->Fill(xhole[6]/hx2Mean, (((xsize[4]-xhole[4])/hx2Mean  )-xholep0[ientry/6][ientry%6])/xholep1[ientry/6][ientry%6]);
        h_shade_shine_cor->Fill(xhole[5]/hx2Mean, (((xsize[7]-xhole[7])/hx2Mean  )-xholep0[ientry/6][ientry%6])/xholep1[ientry/6][ientry%6]);
        h_shade_shine_cor->Fill(xhole[8]/hx3Mean, (((xsize[10]-xhole[10])/hx3Mean)-xholep0[ientry/6][ientry%6])/xholep1[ientry/6][ientry%6]);
        h_shade_shine_cor->Fill(xhole[11]/hx3Mean,(((xsize[9]-xhole[9])/hx3Mean  )-xholep0[ientry/6][ientry%6])/xholep1[ientry/6][ientry%6]);
         
        h_shade_shine_cor->Fill(yhole[2]/hy1Mean, (((ysize[0]-yhole[0])/hy1Mean  )-yholep0[ientry/6][ientry%6])/yholep1[ientry/6][ientry%6]);
        h_shade_shine_cor->Fill(yhole[1]/hy1Mean, (((ysize[3]-yhole[3])/hy1Mean  )-yholep0[ientry/6][ientry%6])/yholep1[ientry/6][ientry%6]);
        h_shade_shine_cor->Fill(yhole[6]/hy2Mean, (((ysize[4]-yhole[4])/hy2Mean  )-yholep0[ientry/6][ientry%6])/yholep1[ientry/6][ientry%6]);
        h_shade_shine_cor->Fill(yhole[7]/hy2Mean, (((ysize[5]-yhole[5])/hy2Mean  )-yholep0[ientry/6][ientry%6])/yholep1[ientry/6][ientry%6]);
        h_shade_shine_cor->Fill(yhole[8]/hy3Mean, (((ysize[10]-yhole[10])/hy3Mean)-yholep0[ientry/6][ientry%6])/yholep1[ientry/6][ientry%6]);
        h_shade_shine_cor->Fill(yhole[9]/hy3Mean, (((ysize[11]-yhole[11])/hy3Mean)-yholep0[ientry/6][ientry%6])/yholep1[ientry/6][ientry%6]);

        h_shade_shine->Fill(xhole[0]/hx1Mean, (xsize[2]-xhole[2])/hx1Mean);
        h_shade_shine->Fill(xhole[1]/hx1Mean, (xsize[3]-xhole[3])/hx1Mean);
        h_shade_shine->Fill(xhole[6]/hx2Mean, (xsize[4]-xhole[4])/hx2Mean);
        h_shade_shine->Fill(xhole[5]/hx2Mean, (xsize[7]-xhole[7])/hx2Mean);
        h_shade_shine->Fill(xhole[8]/hx3Mean, (xsize[10]-xhole[10])/hx3Mean);
        h_shade_shine->Fill(xhole[11]/hx3Mean, (xsize[9]-xhole[9])/hx3Mean);
        
        h_shade_shine->Fill(yhole[2]/hy1Mean, (ysize[0]-yhole[0])/hy1Mean);
        h_shade_shine->Fill(yhole[1]/hy1Mean, (ysize[3]-yhole[3])/hy1Mean);
        h_shade_shine->Fill(yhole[6]/hy2Mean, (ysize[4]-yhole[4])/hy2Mean);
        h_shade_shine->Fill(yhole[7]/hy2Mean, (ysize[5]-yhole[5])/hy2Mean);
        h_shade_shine->Fill(yhole[8]/hy3Mean, (ysize[10]-yhole[10])/hy3Mean);
        h_shade_shine->Fill(yhole[9]/hy3Mean, (ysize[11]-yhole[11])/hy3Mean);

        h_shade_shine->SetMarkerStyle(6);    
        h_shade_shine_cor->SetMarkerStyle(6);    
        hid_xsize[ientry/6][ientry%6]->Write(); 
        hid_ysize[ientry/6][ientry%6]->Write(); 
        hxDev->Fill(hid_xsize[ientry/6][ientry%6]->GetStdDev());
        hyDev->Fill(hid_ysize[ientry/6][ientry%6]->GetStdDev());
        hid_xhole[ientry/6][ientry%6]->Write(); 
        hid_yhole[ientry/6][ientry%6]->Write(); 
        hxholeDev->Fill(hid_xhole[ientry/6][ientry%6]->GetStdDev());
        hyholeDev->Fill(hid_yhole[ientry/6][ientry%6]->GetStdDev());
        hid_xhole2D[ientry/6][ientry%6]->Write();
        hid_yhole2D[ientry/6][ientry%6]->Write();
        hid_xhole2Dcor[ientry/6][ientry%6]->Write();
        hid_yhole2Dcor[ientry/6][ientry%6]->Write();
        



}

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
hxDev->Write();
hyDev->Write();
hxholeDev->Write();
hyholeDev->Write();

hist_shade->Write();
hist_shine->Write();
fout->Close();




}
