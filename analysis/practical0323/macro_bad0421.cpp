#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <cmath>
//macro_correlation4half のコピーより。
//６こ一組のデータに対して、今までの解析を応用する。
void macro_bad0421(){



TString dumpdate      = "0610";
TString histdate      = "0610";
TString readroot  = "_.root";
TString selectroot= "_good1rep.root";


TString file_readroot= dumpdate + readroot; 
TString file_selectroot= dumpdate + histdate + selectroot;


TFile *fin = new TFile(file_readroot, "read");
TTree *tree = (TTree*)fin->Get("tree");
gStyle->SetOptFit(1111);
TH1D* h2 = new TH1D("h2","xhole_cor3",100,100,500);




TH1D* hxhole1= new TH1D("hxhole1","xhole_cam1",100,100,500);
TH1D* hxhole2= new TH1D("hxhole2","xhole_cam2",100,100,500);
TH1D* hxhole3= new TH1D("hxhole3","xhole_cam3",100,100,500);

TH1D* hyhole1= new TH1D("hyhole1","yhole_cam1",100,100,500);
TH1D* hyhole2= new TH1D("hyhole2","yhole_cam2",100,100,500);
TH1D* hyhole3= new TH1D("hyhole3","yhole_cam3",100,100,500);



TH1D* hxholeB = new TH1D("hxholeB","xhole_BEFOREcor",100,0.2,0.35);
TH1D* hyholeB = new TH1D("hyholeB","yhole_BEFOREcor",100,0.2,0.35);

TH1D* hxsize = new TH1D("hxsize","xsize_cor",100,650,700);
TH1D* hysize = new TH1D("hysize","ysize_cor",100,650,700);
TH1D* hxhole = new TH1D("hxhole","xhole_cor",100,0.2,0.35);
TH1D* hyhole = new TH1D("hyhole","yhole_cor",100,0.2,0.35);

//6.8学振のヒストグラムのための追記 
TH1D* hxholeRep = new TH1D("hxholeRep","xhole_representative",100,0,0.15);
TH1D* hyholeRep = new TH1D("hyholeRep","yhole_representative",100,0,0.15);

TString checkxhole12[12][6];
TH2D* h_xhole[12];
TString checkyhole12[12][6];
TH2D* h_yhole[12];

TH1D* h_xholesubcor[12];
TH1D* h_yholesubcor[12];
for (int check12=0; check12<12; check12++){
    checkxhole12[check12][0] = "xhole1_"+std::to_string(check12+1);
    checkxhole12[check12][1] = "xhole;img1;img"+std::to_string(check12+1);
    h_xhole[check12] = new TH2D(checkxhole12[check12][0],checkxhole12[check12][1],100,0.2,0.4,100,0.2,0.4);

    checkyhole12[check12][0] = "yhole1_"+std::to_string(check12+1);
    checkyhole12[check12][1] = "yhole;img1;img"+std::to_string(check12+1);
    h_yhole[check12] = new TH2D(checkyhole12[check12][0],checkyhole12[check12][1],100,0.2,0.4,100,0.2,0.4);    

    
    checkxhole12[check12][4] = "h_xholesubcor_"+std::to_string(check12+1);
    checkxhole12[check12][5] = "xholesubtraciton_cor;img1-img"+std::to_string(check12+1);
    h_xholesubcor[check12] = new TH1D(checkxhole12[check12][4],checkxhole12[check12][5], 100, -0.03,0.03);
    checkyhole12[check12][4] = "h_yholesubcor_"+std::to_string(check12+1);
    checkyhole12[check12][5] = "yholesubtraciton_cor;img1-img"+std::to_string(check12+1);   
    h_yholesubcor[check12] = new TH1D(checkyhole12[check12][4],checkyhole12[check12][5], 100, -0.03,0.03);
}



Int_t n = 6;
Double_t radius[n];
Double_t xhole[n];
Double_t yhole[n];
Double_t xholeB[n];
Double_t yholeB[n];
Double_t Esum[n];
Double_t bump[n];
Double_t xsize[n];
Double_t ysize[n];
Double_t xholecor3[n];
Double_t yholecor3[n];
Int_t icam[n];
Int_t direction[n];
Double_t xholep0[14][6];
Double_t xholep1[14][6];
Double_t yholep0[14][6];
Double_t yholep1[14][6];

Double_t hid_xmax;
Double_t hid_ymax;
Double_t xsubtra;
Double_t ysubtra;


TString id_xholepol[14][6];
TF1* xpol1[14][6];
TString id_yholepol[14][6];
TF1* ypol1[14][6];
for (int i14=0; i14<14; i14++){
    for (int i6=0; i6<6; i6++){
        id_xholepol[i14][i6] = "id_xholepol"+std::to_string(i14)+std::to_string(i6);
        xpol1[i14][i6]= new TF1(id_xholepol[i14][i6],"[0]+x*[1]",0.2,0.4);

        id_yholepol[i14][i6] = "id_yholepol"+std::to_string(i14)+std::to_string(i6);
        ypol1[i14][i6]= new TF1(id_yholepol[i14][i6],"[0]+x*[1]",0.2,0.4);
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
    


//04200420_cali1cor.root の結果を使って補正をする。
//0610_.root の各meanを以下に代入しておく。(6/16)
        /*
        double hx1Mean = 663.6;
        double hx2Mean = 656.1;
        double hx3Mean = 664.6;
        double hy1Mean = 663.4;
        double hy2Mean = 655.9;
        double hy3Mean = 664.5;
        */
        
        double hx1Mean = 663.7;
        double hx2Mean = 657.8;
        double hx3Mean = 665.1;
        double hy1Mean = 666.1;
        double hy2Mean = 658.3;
        double hy3Mean = 665.2;

        double xholepol[12][2];
        double yholepol[12][2];

       xholepol[0][0] =   0.          ;
       xholepol[0][1] =   1.          ;

       yholepol[0][0] =   0.          ;
       yholepol[0][1] =   1.          ;
       
       xholepol[1][0] =   0.0032      ; 
       xholepol[1][1] =   0.987       ; 
                     
       yholepol[1][0] =   -0.0227     ; 
       yholepol[1][1] =   1.052       ; 
                     
       xholepol[2][0] =   0.0217      ; 
       xholepol[2][1] =   0.945       ; 
                     
       yholepol[2][0] =   -0.0168     ; 
       yholepol[2][1] =   1.025       ; 
                     
       xholepol[3][0] =   0.03773     ; 
       xholepol[3][1] =   0.898       ; 
                     
       yholepol[3][0] =   0.00273     ; 
       yholepol[3][1] =   0.983       ; 
                     
       xholepol[4][0] =   0.02342     ; 
       xholepol[4][1] =   0.930       ; 
                     
       yholepol[4][0] =   0.00742     ; 
       yholepol[4][1] =   0.959       ; 
                     
       xholepol[5][0] =   0.00091     ; 
       xholepol[5][1] =   1.003       ; 
                     
       yholepol[5][0] =   0.00691     ; 
       yholepol[5][1] =    0.959      ; 
                     
       xholepol[6][0] =   0.00012     ; 
       xholepol[6][1] =   1.007       ; 
                     
       yholepol[6][0] =   -0.0083     ; 
       yholepol[6][1] =   1.008       ; 
                     
       xholepol[7][0] =   0.02491     ; 
       xholepol[7][1] =   0.925       ; 
                     
       yholepol[7][0] =   -0.0105     ; 
       yholepol[7][1] =   1.017       ; 
                     
       xholepol[8][0] =   0.0         ; 
       xholepol[8][1] =   1.003       ; 
                     
       yholepol[8][0] =   -0.0192     ; 
       yholepol[8][1] =   1.044       ; 
                     
       xholepol[9][0] =   0.01241     ; 
       xholepol[9][1] =   0.965       ; 
                     
       yholepol[9][0] =   -0.0168     ; 
       yholepol[9][1] =   1.031       ; 
                     
       xholepol[10][0] =  0.01768     ; 
       xholepol[10][1] =  0.952       ; 
                     
       yholepol[10][0] =  0.00472     ; 
       yholepol[10][1] =  0.966       ; 
                     
       xholepol[11][0] =  0.00801      ; 
       xholepol[11][1] =  0.977       ; 
                     
       yholepol[11][0] =  0.02469     ; 
       yholepol[11][1] =  0.900       ; 
                     

        /*
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
        */

// [0],[3] がカメラ１、[1],[4] がカメラ3、[2],[5] がカメラ2
// [0],[3] は補正不要、[1],[4] は[11]の補正,[2],[5] は[5]の補正

        xholecor3[0] = xhole[0]/hx1Mean;
        xholecor3[3] = xhole[3]/hx1Mean;
        yholecor3[0] = (ysize[0]-yhole[0])/hy1Mean;
        yholecor3[3] = (ysize[3]-yhole[3])/hy1Mean;
        
        xholecor3[2] =  ((xhole[2]/hx2Mean             )-xholepol[5][0])/xholepol[5][1]; 
        xholecor3[5] =  ((xhole[5]/hx2Mean             )-xholepol[5][0])/xholepol[5][1]; 
        yholecor3[2] =  (((ysize[2]-yhole[2])/hy2Mean  )-yholepol[5][0])/yholepol[5][1];
        yholecor3[5] =  (((ysize[5]-yhole[5])/hy2Mean  )-yholepol[5][0])/yholepol[5][1];

        xholecor3[1] = ((xhole[1]/hx3Mean            )-xholepol[11][0])/xholepol[11][1]; 
        xholecor3[4] = ((xhole[4]/hx3Mean            )-xholepol[11][0])/xholepol[11][1]; 
        yholecor3[1] = (((ysize[1]-yhole[1])/hy3Mean)-yholepol[11][0])/yholepol[11][1];
        yholecor3[4] = (((ysize[4]-yhole[4])/hy3Mean)-yholepol[11][0])/yholepol[11][1];


        xholeB[0] = xhole[0]/hx1Mean; 
        xholeB[3] = xhole[3]/hx1Mean;
        yholeB[0] = (ysize[0]-yhole[0])/hy1Mean;
        yholeB[3] = (ysize[3]-yhole[3])/hy1Mean;

        xholeB[2] = xhole[2]/hx2Mean           ; 
        xholeB[5] = xhole[5]/hx2Mean           ; 
        yholeB[2] = (ysize[2]-yhole[2])/hy2Mean;
        yholeB[5] = (ysize[5]-yhole[5])/hy2Mean;

        xholeB[1] = xhole[1]/hx3Mean           ; 
        xholeB[4] = xhole[4]/hx3Mean           ; 
        yholeB[1] = (ysize[1]-yhole[1])/hy3Mean;
        yholeB[4] = (ysize[4]-yhole[4])/hy3Mean;




        hid_xmax = xholecor3[0];
        xsubtra  = fabs(xholecor3[0]-0.286);
        hid_ymax = yholecor3[0];
        ysubtra  = fabs(yholecor3[0]-0.292);



        for (int filli6=0; filli6<6; filli6++){
            hxhole->Fill(xholecor3[filli6]);
            hyhole->Fill(yholecor3[filli6]);
            hxholeB->Fill(xholeB[filli6]);
            hyholeB->Fill(yholeB[filli6]);


            if(xsubtra < fabs(xholecor3[filli6]-0.286)){
                hid_xmax = xholecor3[filli6];
                xsubtra  = fabs(xholecor3[filli6]-0.286);}
            
            if(ysubtra < fabs(yholecor3[filli6]-0.292)){
                hid_ymax = yholecor3[filli6];
                ysubtra  = fabs(yholecor3[filli6]-0.292);}
        
        }


        hxholeRep->Fill(xsubtra);
        hyholeRep->Fill(ysubtra);

        hxsize->Fill(hx1Mean*xsize[0]/hx1Mean);
        hxsize->Fill(hx1Mean*xsize[1]/hx3Mean);
        hxsize->Fill(hx1Mean*xsize[2]/hx2Mean);
        hxsize->Fill(hx1Mean*xsize[3]/hx1Mean);
        hxsize->Fill(hx1Mean*xsize[4]/hx3Mean);
        hxsize->Fill(hx1Mean*xsize[5]/hx2Mean);
        hysize->Fill(hx1Mean*ysize[0]/hy1Mean);
        hysize->Fill(hx1Mean*ysize[1]/hy3Mean);
        hysize->Fill(hx1Mean*ysize[2]/hy2Mean);
        hysize->Fill(hx1Mean*ysize[3]/hy1Mean);
        hysize->Fill(hx1Mean*ysize[4]/hy3Mean);
        hysize->Fill(hx1Mean*ysize[5]/hy2Mean);

            


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

}

hxsize->Write();
hysize->Write();
hxhole->Write();
hyhole->Write();
hxholeB->Write();
hyholeB->Write();

hxholeRep->Write();
hyholeRep->Write();

fout->Close();




}
