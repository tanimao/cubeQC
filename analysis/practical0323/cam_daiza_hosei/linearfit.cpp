#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>

void linearfit(){



TString dumpdate      = "0823";
TString histdate      = "0825";
TString daiza         = "daiza3";
TString readroot  = ".root";
TString selectroot= "linearfit.root";


TString file_stdroot = "0821daiza2.root"; ///基準となるカメラ・台座の組をもつrootファイルを読み込む。
TString file_readroot= dumpdate + daiza + readroot; 
TString file_selectroot= dumpdate + histdate + daiza + selectroot;


TFile *fin    = new TFile(file_readroot, "read");
TTree *tree   = (TTree*)fin->Get("tree");
gStyle->SetOptFit(1111);


///基準ファイルのツリーを読み出す。
TFile *finstd = new TFile(file_stdroot, "read");
TTree *treestd= (TTree*)finstd->Get("tree");


//ヒストグラムの作成////////////////////////////////
////////////////////////////////////////////////////
TH1D* h1 = new TH1D("h1","radius",100,0,100);

TH1D* h2 = new TH1D("h2","xhole",100,100,500); 
TH1D* h3 = new TH1D("h3","yhole",100,100,500); 
TH1D* h4 = new TH1D("h4","xsize",100,650,720); 
TH1D* h5 = new TH1D("h5","ysize",100,650,720); 
TH1D* hE = new TH1D("hE","Esum" ,100,0,100);
TH1D* hb = new TH1D("hb","bump" ,100,0,1);
TH1D* hd = new TH1D("hd","distance",100,0,100); 
TString id_xsize[16][6];
TH1D* hid_xsize[16][6];
for (int i16=0; i16<16; i16++){
    for (int i6=0; i6<6; i6++){
        id_xsize[i16][i6] = "hid_xsize"+std::to_string(i16)+std::to_string(i6);
        hid_xsize[i16][i6]= new TH1D(id_xsize[i16][i6],"xsize",100,0.9,1.1);
    }
}
TH1D* hxDev = new TH1D("hxDev","xsize_Std_Dev",100,0, 0.01);


TString id_ysize[16][6];
TH1D* hid_ysize[16][6];
for (int i16=0; i16<16; i16++){
    for (int i6=0; i6<6; i6++){
        id_ysize[i16][i6] = "hid_ysize"+std::to_string(i16)+std::to_string(i6);
        hid_ysize[i16][i6]= new TH1D(id_ysize[i16][i6],"ysize",100,0.9,1.1);
    }
}
TH1D* hyDev = new TH1D("hyDev","ysize_Std_Dev",100,0, 0.01);

TString id_xhole[16][6];
TH1D* hid_xhole[16][6];
for (int i16=0; i16<16; i16++){
    for (int i6=0; i6<6; i6++){
        id_xhole[i16][i6] = "hid_xhole"+std::to_string(i16)+std::to_string(i6);
        hid_xhole[i16][i6]= new TH1D(id_xhole[i16][i6],"xhole",100,0.2,0.4);
    }
}

TString id_yhole[16][6];
TH1D* hid_yhole[16][6];
for (int i16=0; i16<16; i16++){
    for (int i6=0; i6<6; i6++){
        id_yhole[i16][i6] = "hid_yhole"+std::to_string(i16)+std::to_string(i6);
        hid_yhole[i16][i6]= new TH1D(id_yhole[i16][i6],"yhole",100,0.2,0.4);
    }
}
TH1D* hxholeDev = new TH1D("hxholeDev","xhole_Std_Dev",100,0, 0.02);
TH1D* hyholeDev = new TH1D("hyholeDev","yhole_Std_Dev",100,0, 0.02);
TH1D* hxholeDevcamcor = new TH1D("hxholeDevcamcor","xhole_Std_Dev_camcor",100,0, 0.02);
TH1D* hyholeDevcamcor = new TH1D("hyholeDevcamcor","yhole_Std_Dev_camcor",100,0, 0.02);

TH1D* hxholeMeancamcor = new TH1D("hxholeMeancamcor","xhole_Std_Meancamcor",100,0.2, 0.35);
TH1D* hyholeMeancamcor = new TH1D("hyholeMeancamcor","yhole_Std_Meancamcor",100,0.2, 0.35);



TH1D* hx1= new TH1D("hx1","xsize_cam1",100,650,720);
TH1D* hx2= new TH1D("hx2","xsize_cam2",100,650,720);
TH1D* hx3= new TH1D("hx3","xsize_cam3",100,650,720);

TH1D* hy1= new TH1D("hy1","ysize_cam1",100,650,720);
TH1D* hy2= new TH1D("hy2","ysize_cam2",100,650,720);
TH1D* hy3= new TH1D("hy3","ysize_cam3",100,650,720);

///基準のhx1Meanstd などを取得するためのヒストグラム
TH1D* hx1std= new TH1D("hx1std","xsize_cam1",100,650,720);
TH1D* hx2std= new TH1D("hx2std","xsize_cam2",100,650,720);
TH1D* hx3std= new TH1D("hx3std","xsize_cam3",100,650,720);

TH1D* hy1std= new TH1D("hy1std","ysize_cam1",100,650,720);
TH1D* hy2std= new TH1D("hy2std","ysize_cam2",100,650,720);
TH1D* hy3std= new TH1D("hy3std","ysize_cam3",100,650,720);




TH1D* hxhole1= new TH1D("hxhole1","xhole_cam1",100,100,500);
TH1D* hxhole2= new TH1D("hxhole2","xhole_cam2",100,100,500);
TH1D* hxhole3= new TH1D("hxhole3","xhole_cam3",100,100,500);

TH1D* hyhole1= new TH1D("hyhole1","yhole_cam1",100,100,500);
TH1D* hyhole2= new TH1D("hyhole2","yhole_cam2",100,100,500);
TH1D* hyhole3= new TH1D("hyhole3","yhole_cam3",100,100,500);

TH1D* hrad = new TH1D("hrad","radius",100,0.05,0.1);

TString checkxhole12[12][4];
TH2D* h_xhole[12];
TString checkyhole12[12][4];
TH2D* h_yhole[12];
TH1D* h_xholesub[12];
TH1D* h_yholesub[12];

TF1 * xp[12];
TF1 * yp[12];

TString id_xp[12];
TString id_yp[12];



///h_xhole[12], h_yhole[12] が補正のために最も大切なヒストグラム。
for (int check12=0; check12<12; check12++){
    checkxhole12[check12][0] = "xhole1_"+std::to_string(check12+1);
    checkxhole12[check12][1] = "xhole;daiza2cam2_1;img"+std::to_string(check12+1);
    h_xhole[check12] = new TH2D(checkxhole12[check12][0],checkxhole12[check12][1],100,0.2,0.4,100,0.2,0.4);
    id_xp[check12] = "id_xholepol"+std::to_string(check12);
    xp[check12]= new TF1(id_xp[check12],"[0]+x*[1]",0.2,0.4);

    checkyhole12[check12][0] = "yhole1_"+std::to_string(check12+1);
    checkyhole12[check12][1] = "yhole;daiza2cam2_1;img"+std::to_string(check12+1);
    h_yhole[check12] = new TH2D(checkyhole12[check12][0],checkyhole12[check12][1],100,0.2,0.4,100,0.2,0.4);    
    id_yp[check12] = "id_yholepol"+std::to_string(check12);
    yp[check12]= new TF1(id_yp[check12],"[0]+x*[1]",0.2,0.4);

    checkxhole12[check12][2] = "h_xholesub"+std::to_string(check12+1);
    checkxhole12[check12][3] = "xholesubtraciton;img1-img"+std::to_string(check12+1);
    h_xholesub[check12] = new TH1D(checkxhole12[check12][2],checkxhole12[check12][3], 100, -0.03,0.03);
    checkyhole12[check12][2] = "h_yholesub"+std::to_string(check12+1);
    checkyhole12[check12][3] = "yholesubtraciton;img1-img"+std::to_string(check12+1);   
    h_yholesub[check12] = new TH1D(checkyhole12[check12][2],checkyhole12[check12][3], 100, -0.03,0.03);
    
}


//ヒストグラム作成ここまで//////////////////////////////
////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
//パラメータ定義////////////////////////////////////////
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
Double_t xholep0[16][6];
Double_t xholep1[16][6];
Double_t yholep0[16][6];
Double_t yholep1[16][6];


///基準ツリーの変数
Double_t std_radius[n];
Double_t std_xhole[n];
Double_t std_yhole[n];
Double_t std_Esum[n];
Double_t std_bump[n];
Double_t std_xsize[n];
Double_t std_ysize[n];
Double_t std_xholerate[n];
Double_t std_yholerate[n];
Int_t std_icam[n];
Int_t std_direction[n];

////////////////////////////////////////////////////////
//フィット用の一次関数の定義////////////////////////////
TString id_xholepol[16][6];
TF1* xpol1[16][6];
TString id_yholepol[16][6];
TF1* ypol1[16][6];
for (int i16=0; i16<16; i16++){
    for (int i6=0; i6<6; i6++){
        id_xholepol[i16][i6] = "id_xholepol"+std::to_string(i16)+std::to_string(i6);
        xpol1[i16][i6]= new TF1(id_xholepol[i16][i6],"[0]+x*[1]",0.2,0.4);

        id_yholepol[i16][i6] = "id_yholepol"+std::to_string(i16)+std::to_string(i6);
        ypol1[i16][i6]= new TF1(id_yholepol[i16][i6],"[0]+x*[1]",0.2,0.4);
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


treestd->SetBranchAddress("radius", std_radius);
treestd->SetBranchAddress("xhole", std_xhole);
treestd->SetBranchAddress("yhole", std_yhole);
treestd->SetBranchAddress("xsize", std_xsize);
treestd->SetBranchAddress("ysize", std_ysize);
treestd->SetBranchAddress("Esum" , std_Esum );
treestd->SetBranchAddress("bump" , std_bump );
treestd->SetBranchAddress("icam",  std_icam );
treestd->SetBranchAddress("direction",std_direction);






/////////////////////////////////////////////////////////
//ここからツリーの読み込みを行う。///////////////////////


int nentries = tree->GetEntries();

TFile *fout = new TFile(file_selectroot, "recreate");
for ( int ientry = 0; ientry < nentries; ientry++ )
{
  tree->   GetEntry( ientry );
  treestd->GetEntry( ientry );    

    for (int inum=0; inum<n ; inum++){
        


        //基本のパラメータのFill
        h1->Fill(radius[inum]);
        h2->Fill(xhole[inum]);
        h3->Fill(yhole[inum]);
        h4->Fill(xsize[inum]);
        h5->Fill(ysize[inum]);
        hE->Fill(Esum[inum]);
        hb->Fill(bump[inum]);
        

        //カメラごとのサイズのFill
        if( icam[inum] == 1 ){
            hx1->Fill(xsize[inum]);
            hy1->Fill(ysize[inum]);
        }else if(icam[inum] == 2){
            hx2->Fill(xsize[inum]);
            hy2->Fill(ysize[inum]);
        }else if(icam[inum] == 3){
            hx3->Fill(xsize[inum]);
            hy3->Fill(ysize[inum]);
        }    



        //基準hx1Meanstdの取得のためのヒストグラム
        if( std_icam[inum] == 1 ){
            hx1std->Fill(std_xsize[inum]);
            hy1std->Fill(std_ysize[inum]);
        }else if(std_icam[inum] == 2){
            hx2std->Fill(std_xsize[inum]);
            hy2std->Fill(std_ysize[inum]);
        }else if(std_icam[inum] == 3){
            hx3std->Fill(std_xsize[inum]);
            hy3std->Fill(std_ysize[inum]);
        }
    }
}
 
        //カメラごとのサイズ平均を得る。

        //これだとループが回るごとに異なる平均値を使うことになってしまう。
        //一度ループを閉じて平均値を求める。
        double hx1Mean = hx1->GetMean();
        double hx2Mean = hx2->GetMean();
        double hx3Mean = hx3->GetMean();
        double hy1Mean = hy1->GetMean();
        double hy2Mean = hy2->GetMean();
        double hy3Mean = hy3->GetMean();
    
        ///基準のやつの平均を取得する
        double hx1Meanstd = hx1std->GetMean();
        double hx2Meanstd = hx2std->GetMean();
        double hx3Meanstd = hx3std->GetMean();
        double hy1Meanstd = hy1std->GetMean();
        double hy2Meanstd = hy2std->GetMean();
        double hy3Meanstd = hy3std->GetMean();



        std::cout << "hx1Mean : " << hx1Mean << std::endl;
        std::cout << "hx2Mean : " << hx2Mean << std::endl;
        std::cout << "hx1Meanstd : "<<hx1Meanstd << std::endl;
        std::cout << "hx2Meanstd : "<<hx2Meanstd << std::endl;
        //カメラごとに平均で規格化した、穴位置のFill

        //多分、ientry/6 = キューブの番号、　ientry%6 = 面の番号
        //かな。どちらも0から始まる。



//ここからループ再開
for ( int ientry2 = 0; ientry2 < nentries; ientry2++ )
{
  tree->GetEntry( ientry2 );
  treestd->GetEntry( ientry2 );
        
        for (int i12=0; i12<12; i12++){
            if(icam[i12]==1){
                hid_xsize[ientry2/6][ientry2%6]->Fill(xsize[i12]/hx1Mean);
                hid_ysize[ientry2/6][ientry2%6]->Fill(ysize[i12]/hy1Mean);
                hid_xhole[ientry2/6][ientry2%6]->Fill(xhole[i12]/hx1Mean);
                hid_yhole[ientry2/6][ientry2%6]->Fill(yhole[i12]/hy1Mean);
                hrad->Fill(radius[i12] /((hx1Mean+hy1Mean)/2));
                }
            //以下、なぜかhx1Mean とかhy1Meanで割っている。本当はカメラIDに合わせてhx2Mean などで割るべきでは？
            else if (icam[i12]==2){
                hid_xsize[ientry2/6][ientry2%6]->Fill(xsize[i12]/(hx2->GetMean()));
                hid_ysize[ientry2/6][ientry2%6]->Fill(ysize[i12]/(hy2->GetMean()));
                hid_xhole[ientry2/6][ientry2%6]->Fill(xhole[i12]/hx2Mean);
                hid_yhole[ientry2/6][ientry2%6]->Fill(yhole[i12]/hy2Mean);
                hrad->Fill(radius[i12] /((hx2Mean+hy2Mean)/2));
                }
            else if (icam[i12]==3){
                hid_xsize[ientry2/6][ientry2%6]->Fill(xsize[i12]/(hx3->GetMean()));
                hid_ysize[ientry2/6][ientry2%6]->Fill(ysize[i12]/(hy3->GetMean()));
                hid_xhole[ientry2/6][ientry2%6]->Fill(xhole[i12]/hx3Mean);
                hid_yhole[ientry2/6][ientry2%6]->Fill(yhole[i12]/hy3Mean);
                hrad->Fill(radius[i12] /((hx3Mean+hy3Mean)/2));
            }
            
        }


        //穴位置の定義が前回と違って、近い辺からの距離に統一されている。
        //daiza2のカメラ2、向き1を基準に使ってみる
        h_xhole[0] ->Fill(std_xhole[5]/hx2Meanstd, xhole[0]/hx1Mean);
        h_xhole[1] ->Fill(std_xhole[5]/hx2Meanstd, xhole[1]/hx1Mean);
        h_xhole[2] ->Fill(std_xhole[5]/hx2Meanstd, xhole[2]/hx1Mean);
        h_xhole[3] ->Fill(std_xhole[5]/hx2Meanstd, xhole[3]/hx1Mean);
        h_xhole[4] ->Fill(std_xhole[5]/hx2Meanstd, xhole[4]/hx2Mean);
        h_xhole[5] ->Fill(std_xhole[5]/hx2Meanstd, xhole[5]/hx2Mean);
        h_xhole[6] ->Fill(std_xhole[5]/hx2Meanstd, xhole[6]/hx2Mean);
        h_xhole[7] ->Fill(std_xhole[5]/hx2Meanstd, xhole[7]/hx2Mean);
        h_xhole[8] ->Fill(std_xhole[5]/hx2Meanstd, xhole[8]/hx3Mean);
        h_xhole[9] ->Fill(std_xhole[5]/hx2Meanstd, xhole[9]/hx3Mean);
        h_xhole[10]->Fill(std_xhole[5]/hx2Meanstd, xhole[10]/hx3Mean);
        h_xhole[11]->Fill(std_xhole[5]/hx2Meanstd, xhole[11]/hx3Mean);

        h_yhole[0] ->Fill(std_yhole[5]/hy2Meanstd, yhole[0]/hy1Mean);
        h_yhole[1] ->Fill(std_yhole[5]/hy2Meanstd, yhole[1]/hy1Mean);
        h_yhole[2] ->Fill(std_yhole[5]/hy2Meanstd, yhole[2]/hy1Mean);
        h_yhole[3] ->Fill(std_yhole[5]/hy2Meanstd, yhole[3]/hy1Mean);
        h_yhole[4] ->Fill(std_yhole[5]/hy2Meanstd, yhole[4]/hy2Mean);
        h_yhole[5] ->Fill(std_yhole[5]/hy2Meanstd, yhole[5]/hy2Mean);
        h_yhole[6] ->Fill(std_yhole[5]/hy2Meanstd, yhole[6]/hy2Mean);
        h_yhole[7] ->Fill(std_yhole[5]/hy2Meanstd, yhole[7]/hy2Mean);
        h_yhole[8] ->Fill(std_yhole[5]/hy2Meanstd, yhole[8]/hy3Mean);
        h_yhole[9] ->Fill(std_yhole[5]/hy2Meanstd, yhole[9]/hy3Mean);
        h_yhole[10]->Fill(std_yhole[5]/hy2Meanstd, yhole[10]/hy3Mean);
        h_yhole[11]->Fill(std_yhole[5]/hy2Meanstd, yhole[11]/hy3Mean);
/*
        h_xhole[0] ->Fill(xhole[5]/hx2Mean, xhole[0]/hx1Mean);
        h_xhole[1] ->Fill(xhole[5]/hx2Mean, xhole[1]/hx1Mean);
        h_xhole[2] ->Fill(xhole[5]/hx2Mean, xhole[2]/hx1Mean);
        h_xhole[3] ->Fill(xhole[5]/hx2Mean, xhole[3]/hx1Mean);
        h_xhole[4] ->Fill(xhole[5]/hx2Mean, xhole[4]/hx2Mean);
        h_xhole[5] ->Fill(xhole[5]/hx2Mean, xhole[5]/hx2Mean);
        h_xhole[6] ->Fill(xhole[5]/hx2Mean, xhole[6]/hx2Mean);
        h_xhole[7] ->Fill(xhole[5]/hx2Mean, xhole[7]/hx2Mean);
        h_xhole[8] ->Fill(xhole[5]/hx2Mean, xhole[8]/hx3Mean);
        h_xhole[9] ->Fill(xhole[5]/hx2Mean, xhole[9]/hx3Mean);
        h_xhole[10]->Fill(xhole[5]/hx2Mean, xhole[10]/hx3Mean);
        h_xhole[11]->Fill(xhole[5]/hx2Mean, xhole[11]/hx3Mean);

        h_yhole[0] ->Fill(yhole[5]/hy2Mean, yhole[0]/hy1Mean);
        h_yhole[1] ->Fill(yhole[5]/hy2Mean, yhole[1]/hy1Mean);
        h_yhole[2] ->Fill(yhole[5]/hy2Mean, yhole[2]/hy1Mean);
        h_yhole[3] ->Fill(yhole[5]/hy2Mean, yhole[3]/hy1Mean);
        h_yhole[4] ->Fill(yhole[5]/hy2Mean, yhole[4]/hy2Mean);
        h_yhole[5] ->Fill(yhole[5]/hy2Mean, yhole[5]/hy2Mean);
        h_yhole[6] ->Fill(yhole[5]/hy2Mean, yhole[6]/hy2Mean);
        h_yhole[7] ->Fill(yhole[5]/hy2Mean, yhole[7]/hy2Mean);
        h_yhole[8] ->Fill(yhole[5]/hy2Mean, yhole[8]/hy3Mean);
        h_yhole[9] ->Fill(yhole[5]/hy2Mean, yhole[9]/hy3Mean);
        h_yhole[10]->Fill(yhole[5]/hy2Mean, yhole[10]/hy3Mean);
        h_yhole[11]->Fill(yhole[5]/hy2Mean, yhole[11]/hy3Mean);

*/



        hid_xsize[ientry2/6][ientry2%6]->Write(); 
        hid_ysize[ientry2/6][ientry2%6]->Write(); 
        hxDev->Fill(hid_xsize[ientry2/6][ientry2%6]->GetStdDev());
        hyDev->Fill(hid_ysize[ientry2/6][ientry2%6]->GetStdDev());
        hid_xhole[ientry2/6][ientry2%6]->Write(); 
        hid_yhole[ientry2/6][ientry2%6]->Write(); 
        hxholeDev->Fill(hid_xhole[ientry2/6][ientry2%6]->GetStdDev());
        hyholeDev->Fill(hid_yhole[ientry2/6][ientry2%6]->GetStdDev());



}
        TString  xprint[12];
        TString  yprint[12];
        double  xhole12p[12][4];
        double  yhole12p[12][4];

        TCanvas * c2 = new TCanvas("c2","c2");
        for (int che11=0;che11<12;che11++){
           
            //補正用の一次関数、それでフィット
            
             
            h_xhole[che11]->Fit(xp[che11],"","",0.2,0.33);
            std::cout << "h_xhole:"<< che11 << std::endl;            
            h_yhole[che11]->Fit(yp[che11],"","",0.2,0.33);
            std::cout << "h_yhole:"<< che11 << std::endl;            
            h_xhole[che11]->SetMarkerStyle(7);
            h_yhole[che11]->SetMarkerStyle(7);
            h_xhole[che11]->Write();
            h_yhole[che11]->Write();
            
            //補正用の一次関数のパラメータ。これを使って、ここ以下に補正の式を書く。
            xhole12p[che11][0] = xp[che11]->GetParameter(0);
            yhole12p[che11][0] = yp[che11]->GetParameter(0);
            xhole12p[che11][1] = xp[che11]->GetParameter(1);
            yhole12p[che11][1] = yp[che11]->GetParameter(1);
            xhole12p[che11][2] = xp[che11]->GetParError(0);
            yhole12p[che11][2] = yp[che11]->GetParError(0);
            xhole12p[che11][3] = xp[che11]->GetParError(1);
            yhole12p[che11][3] = yp[che11]->GetParError(1);

            xp[che11]->Write();
            yp[che11]->Write();
            
        }
///カメラに関する補正後のヒストグラム。
TString id_xholecamcor[16][6];
TH1D* hid_xholecamcor[16][6];
TString id_yholecamcor[16][6];
TH1D* hid_yholecamcor[16][6];
for (int i16=0; i16<16; i16++){
    for (int i6=0; i6<6; i6++){
        id_xholecamcor[i16][i6] = "hid_xholecamcor_"+std::to_string(i16)+std::to_string(i6);
        hid_xholecamcor[i16][i6]= new TH1D(id_xholecamcor[i16][i6],"xholecamcor",100,0.2,0.4);
        id_yholecamcor[i16][i6] = "hid_yholecamcor_"+std::to_string(i16)+std::to_string(i6);
        hid_yholecamcor[i16][i6]= new TH1D(id_yholecamcor[i16][i6],"yholecamcor",100,0.2,0.4);
    }
}
// n = 12。
Double_t xholecamcor[n];
Double_t yholecamcor[n];

///またエントリで回す。
for ( int ientry3 = 0; ientry3 < nentries; ientry3 ++)
{
  tree->GetEntry( ientry3 );
xholecamcor[0] = ((xhole[0]/hx1Mean) - xhole12p[0][0])/xhole12p[0][1];
xholecamcor[1] = ((xhole[1]/hx1Mean) - xhole12p[1][0])/xhole12p[1][1];
xholecamcor[2] = ((xhole[2]/hx1Mean) - xhole12p[2][0])/xhole12p[2][1];
xholecamcor[3] = ((xhole[3]/hx1Mean) - xhole12p[3][0])/xhole12p[3][1];
xholecamcor[4] = ((xhole[4]/hx2Mean) - xhole12p[4][0])/xhole12p[4][1];
xholecamcor[5] = ((xhole[5]/hx2Mean) - xhole12p[5][0])/xhole12p[5][1];
xholecamcor[6] = ((xhole[6]/hx2Mean) - xhole12p[6][0])/xhole12p[6][1];
xholecamcor[7] = ((xhole[7]/hx2Mean) - xhole12p[7][0])/xhole12p[7][1];
xholecamcor[8] = ((xhole[8]/hx3Mean) - xhole12p[8][0])/xhole12p[8][1];
xholecamcor[9] = ((xhole[9]/hx3Mean) - xhole12p[9][0])/xhole12p[9][1];
xholecamcor[10] = ((xhole[10]/hx3Mean) - xhole12p[10][0])/xhole12p[10][1];
xholecamcor[11] = ((xhole[11]/hx3Mean) - xhole12p[11][0])/xhole12p[11][1];


yholecamcor[0] = ((yhole[0]/hy1Mean) - yhole12p[0][0])/yhole12p[0][1];
yholecamcor[1] = ((yhole[1]/hy1Mean) - yhole12p[1][0])/yhole12p[1][1];
yholecamcor[2] = ((yhole[2]/hy1Mean) - yhole12p[2][0])/yhole12p[2][1];
yholecamcor[3] = ((yhole[3]/hy1Mean) - yhole12p[3][0])/yhole12p[3][1];
yholecamcor[4] = ((yhole[4]/hy2Mean) - yhole12p[4][0])/yhole12p[4][1];
yholecamcor[5] = ((yhole[5]/hy2Mean) - yhole12p[5][0])/yhole12p[5][1];
yholecamcor[6] = ((yhole[6]/hy2Mean) - yhole12p[6][0])/yhole12p[6][1];
yholecamcor[7] = ((yhole[7]/hy2Mean) - yhole12p[7][0])/yhole12p[7][1];
yholecamcor[8] = ((yhole[8]/hy3Mean) - yhole12p[8][0])/yhole12p[8][1];
yholecamcor[9] = ((yhole[9]/hy3Mean) - yhole12p[9][0])/yhole12p[9][1];
yholecamcor[10] = ((yhole[10]/hy3Mean) - yhole12p[10][0])/yhole12p[10][1];
yholecamcor[11] = ((yhole[11]/hy3Mean) - yhole12p[11][0])/yhole12p[11][1];

/*
for (int i12=0; i12<12; i12++){
    hid_xholecamcor[ientry3/6][ientry3%6]->Fill(xholecamcor[i12]);
    hid_yholecamcor[ientry3/6][ientry3%6]->Fill(yholecamcor[i12]);
    }
*/

hid_xholecamcor[ientry3/6][ientry3%6]->Fill(xholecamcor[0]);
hid_xholecamcor[ientry3/6][ientry3%6]->Fill(xholecamcor[1]);
hid_xholecamcor[ientry3/6][ientry3%6]->Fill(xholecamcor[2]);
hid_xholecamcor[ientry3/6][ientry3%6]->Fill(xholecamcor[3]);
hid_xholecamcor[ientry3/6][ientry3%6]->Fill(xholecamcor[4]);
hid_xholecamcor[ientry3/6][ientry3%6]->Fill(xholecamcor[5]);
hid_xholecamcor[ientry3/6][ientry3%6]->Fill(xholecamcor[6]);
hid_xholecamcor[ientry3/6][ientry3%6]->Fill(xholecamcor[7]);
hid_xholecamcor[ientry3/6][ientry3%6]->Fill(xholecamcor[8]);
hid_xholecamcor[ientry3/6][ientry3%6]->Fill(xholecamcor[9]);
hid_xholecamcor[ientry3/6][ientry3%6]->Fill(xholecamcor[10]);
hid_xholecamcor[ientry3/6][ientry3%6]->Fill(xholecamcor[11]);


hid_yholecamcor[ientry3/6][ientry3%6]->Fill(yholecamcor[0]);
hid_yholecamcor[ientry3/6][ientry3%6]->Fill(yholecamcor[1]);
hid_yholecamcor[ientry3/6][ientry3%6]->Fill(yholecamcor[2]);
hid_yholecamcor[ientry3/6][ientry3%6]->Fill(yholecamcor[3]);
hid_yholecamcor[ientry3/6][ientry3%6]->Fill(yholecamcor[4]);
hid_yholecamcor[ientry3/6][ientry3%6]->Fill(yholecamcor[5]);
hid_yholecamcor[ientry3/6][ientry3%6]->Fill(yholecamcor[6]);
hid_yholecamcor[ientry3/6][ientry3%6]->Fill(yholecamcor[7]);
hid_yholecamcor[ientry3/6][ientry3%6]->Fill(yholecamcor[8]);
hid_yholecamcor[ientry3/6][ientry3%6]->Fill(yholecamcor[9]);
hid_yholecamcor[ientry3/6][ientry3%6]->Fill(yholecamcor[10]);
hid_yholecamcor[ientry3/6][ientry3%6]->Fill(yholecamcor[11]);

hid_xholecamcor[ientry3/6][ientry3%6]->Write();
hid_yholecamcor[ientry3/6][ientry3%6]->Write();


hxholeDevcamcor->Fill(hid_xholecamcor[ientry3/6][ientry3%6]->GetStdDev());
hyholeDevcamcor->Fill(hid_yholecamcor[ientry3/6][ientry3%6]->GetStdDev());
hxholeMeancamcor->Fill(hid_xholecamcor[ientry3/6][ientry3%6]->GetMean());
hyholeMeancamcor->Fill(hid_yholecamcor[ientry3/6][ientry3%6]->GetMean());


}


//tree->Write();
h1->Write();
h2->Write();
h3->Write();
h4->Write();
h5->Write();
hE->Write();
hb->Write();
hrad->Write();

hx1->Write();
hx2->Write();
hx3->Write();
hy1->Write();
hy2->Write();
hy3->Write();

hx1std->Write();
hx2std->Write();
hx3std->Write();
hy1std->Write();
hy2std->Write();
hy3std->Write();
hxDev->Write();
hyDev->Write();
hxholeDev->Write();
hyholeDev->Write();
hxholeDevcamcor->Write();
hyholeDevcamcor->Write();
hxholeMeancamcor->Write();
hyholeMeancamcor->Write();
gStyle->SetOptFit(1111);
fout->Close();



}

