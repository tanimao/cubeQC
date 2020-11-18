#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>

#include <vector>
//#include "classCube_matsu_sukima.cc"
#include "classCube_hole.cc"

#include <stdlib.h>
#include <time.h>

#include <random>
#include <algorithm>

// root -l analysis.C




void analysis_hole1(TFile* fr, TFile* fin, TFile* fh,  int Nall, 
                      int hmax, int hmin, int smax, int smin)
{

//    gRandom->SetSeed(2);
    gRandom->SetSeed((unsigned int ) time(NULL));
//    srand(1);
//    srand((unsigned int) time(NULL));
//    //std::cout << "time : "<< (unsigned int) time(NULL) << std::endl; 
    // TH1F でパラメたの測定分布を読み込む
    TH1D  * h1  = (TH1D*)fr->Get("h1");  //radius
    TH3D * sizexyz = (TH3D*)fin->Get("sizexyz");
    TH2D * histhole0   = (TH2D*)fh->Get("hole0");
    TH2D * histhole1   = (TH2D*)fh->Get("hole1");
    TH2D * histhole2   = (TH2D*)fh->Get("hole2");
    TH2D * histhole3   = (TH2D*)fh->Get("hole3");
    TH2D * histhole4   = (TH2D*)fh->Get("hole4");
    TH2D * histhole5   = (TH2D*)fh->Get("hole5");
 
    // 読み込んだ分布より、GetRndom で値を取ってきて、
   // float sizehwd[3];
   // float hole14[2];
   // float hole25[2];
   // float hole36[2];
    
    Double_t sizehwd[3];
    Double_t hole0[2];
    Double_t hole1[2];
    Double_t hole2[2];
    Double_t hole3[2];
    Double_t hole4[2];
    Double_t hole5[2];
    Double_t r[6];
    
    int igood = 0;
    int cubemax = 10000;
    int unitnum = 50000;


    //穴位置の中央値を得てキューブを分類するためのヒストグラム
    TH1F * newhisthole14x = new TH1F("newhisthole14x","newhisthole14x",
                                     100, 140*0.01554, 220*0.01554);
    TH1F * newhisthole14y = new TH1F("newhisthole14y","newhisthole14y",
                                     100, 140*0.01554, 220*0.01554);

    TH1F * newhisthole25x = new TH1F("newhisthole25x","newhisthole25x",
                                     100, 140*0.01554, 220*0.01554);
    TH1F * newhisthole25y = new TH1F("newhisthole25y","newhisthole25y",
                                     100, 140*0.01554, 220*0.01554);

    //穴位置分布を確認するための2Dヒストグラム
    TH2F * hcenter1 = new  TH2F ("hcenter1", "hcenter1", 
                                    100, 4, 5, 100, 2.3, 3.3);
    TH2F * hcenter2 = new  TH2F ("hcenter2", "hcenter2", 
                                    100, 4, 5, 100, 7, 8);

   // キューブのパラメータを決定しながら、キューブを定義する

	//Cube *c = new Cube(1,1,1,1,1); 
   //Cube *cube[12000];
    std::vector < Cube* > cube;
 
    //16通りの分類
    std::vector < Cube* > cubeAA;
    std::vector < Cube* > cubeAB;
    std::vector < Cube* > cubeAC;
    std::vector < Cube* > cubeAD;
    std::vector < Cube* > cubeBA;
    std::vector < Cube* > cubeBB;
    std::vector < Cube* > cubeBC;
    std::vector < Cube* > cubeBD;
    std::vector < Cube* > cubeCA;
    std::vector < Cube* > cubeCB;
    std::vector < Cube* > cubeCC;
    std::vector < Cube* > cubeCD;
    std::vector < Cube* > cubeDA;
    std::vector < Cube* > cubeDB;
    std::vector < Cube* > cubeDC;
    std::vector < Cube* > cubeDD;


    


 
    double _sMean = 659.2; 
    //if文での参照用。macro_forrangeif.cppよりとってきた

    for (int icu = 0; icu<cubemax; icu++) {
        sizexyz->GetRandom3(sizehwd[0], sizehwd[1], sizehwd[2]);
        //sizexyz->GetRandom3(sizehwd[0], sizehwd[1], sizehwd[2]);
        //サイズごとに、参照するヒストグラムを変えることで、相関を表現
        histhole0->GetRandom2(hole0[1], hole0[0]);
        histhole1->GetRandom2(hole1[1], hole1[0]);
        histhole2->GetRandom2(hole2[1], hole2[0]);
        histhole3->GetRandom2(hole3[1], hole3[0]);
        histhole4->GetRandom2(hole4[1], hole4[0]);
        histhole5->GetRandom2(hole5[1], hole5[0]);

       //rは以前のままにしておく 
        for (int isu = 0; isu<6; isu++){
            r[isu]  = h1->GetRandom();

                    
        }
        if (
         //スキャン用の条件
        // /*
         649.5 + smin < sizehwd[0] && sizehwd[0] < 664.3 + smax &&
         649.5 + smin < sizehwd[1] && sizehwd[1] < 664.3 + smax &&
         649.5 + smin < sizehwd[2] && sizehwd[2] < 664.3 + smax &&

         162.5 + hmin < hole0[0]  && hole0[0]  < 199.5 + hmax &&
         162.5 + hmin < hole0[1]  && hole0[1]  < 199.5 + hmax &&
         162.5 + hmin < hole1[0]  && hole1[0]  < 199.5 + hmax &&
         162.5 + hmin < hole1[1]  && hole1[1]  < 199.5 + hmax &&
         162.5 + hmin < hole2[0]  && hole2[0]  < 199.5 + hmax &&
         162.5 + hmin < hole2[1]  && hole2[1]  < 199.5 + hmax &&

         162.5 + hmin < hole3[0]  && hole3[0]  < 199.5 + hmax &&
         162.5 + hmin < hole3[1]  && hole3[1]  < 199.5 + hmax &&
         162.5 + hmin < hole4[0]  && hole4[0]  < 199.5 + hmax &&
         162.5 + hmin < hole4[1]  && hole4[1]  < 199.5 + hmax &&
         162.5 + hmin < hole5[0]  && hole5[0]  < 199.5 + hmax &&
         162.5 + hmin < hole5[1]  && hole5[1]  < 199.5 + hmax &&

         47.8 < r[0] &&
         47.8 < r[1] &&
         47.8 < r[2] &&
         47.8 < r[3] &&
         47.8 < r[4] &&
         47.8 < r[5] &&
       //  */
         //10/13 現行の条件(以下)
         /*
             652+0.8-1 < sizehwd[0] && sizehwd[0] < 664+0.8-0.5 && 
             652+0.8-1 < sizehwd[1] && sizehwd[1] < 664+0.8-0.5 && 
             652+0.8-1 < sizehwd[2] && sizehwd[2] < 664+0.8-0.5 && 

            168+4.5 < hole14[0] && hole14[0] < 198+1.5 && 
            168+4.5 < hole14[1] && hole14[1] < 198+1.5 && 
            168+4.5 < hole25[0] && hole25[0] < 198+1.5 && 
            168+4.5 < hole25[1] && hole25[1] < 198+1.5 && 
            168+4.5 < hole36[0] && hole36[0] < 198+1.5 && 
            168+4.5 < hole36[1] && hole36[1] < 198+1.5 && 


            47.8  < r[0]  &&
            47.8  < r[1]  &&
            47.8  < r[2]  &&
            47.8  < r[3]  &&
            47.8  < r[4]  &&
            47.8  < r[5]  &&
        */
            1==1

            ){        
            igood += 1; 
            cube.push_back( new Cube(igood,
            //ピクセル数をミリメートルに変換
                   0.01554*sizehwd[0], 0.01554*sizehwd[1], 0.01554*sizehwd[2], 
                   0.01554*hole0[0], 0.01554*hole0[1],  
                   0.01554*hole1[0], 0.01554*hole1[1],  
                   0.01554*hole2[0], 0.01554*hole2[1],  
                   0.01554*hole3[0], 0.01554*hole3[1],  
                   0.01554*hole4[0], 0.01554*hole4[1],  
                   0.01554*hole5[0], 0.01554*hole5[1],  
                   0.01554*r[0], 0.01554*r[1], 0.01554*r[2], 
                   0.01554*r[3], 0.01554*r[4], 0.01554*r[5])); 

        //穴位置の中央値を得てキューブを分類するためのヒストグラムに
        //値をフィルする。

           //newhisthole14x->Fill(0.01554*hole4[0]); 
           //newhisthole14x->Fill(0.01554*hole1[0]); 
           newhisthole14x->Fill(0.01554*(hole1[0]+hole4[0])/2); 
           newhisthole14y->Fill(0.01554*(hole1[1]+hole4[1])/2); 
           newhisthole25x->Fill(0.01554*(hole2[0]+hole5[0])/2); 
           newhisthole25y->Fill(0.01554*(hole2[1]+hole5[1])/2); 


        //  id と parameter :  必要な parameter は自分で定義する
        //    cube[igood-1]->GetSurf1(parlist);
        }
//        if (parlist[0]<680){
//            cube.pop_back();
//        }
        //std::cout << "simulated cube : "<< icu+1 << std::endl;
        //std::cout << "good cube      : "<< cube.size() << std::endl;
        //std::cout << "***********************************" << std::endl;
        //std::cout << "***********************************" << std::endl;
    }    





   // selection cut かける
   //キューブを64個穴基準で並べる 
    float posxhx[8][8][6] = {0.};
    float posxhy[8][8][6] = {0.};
    float posxhz[8][8][6] = {0.};
    float pitch = 10.3;
    //float tan = 0.4/102.4;
    float tan = 0/102.4;
    int cannotx = 0;
    int cannoty = 0;
    int cannot  = 0;

    int CatNum[16]= {0};

    //ヒストグラムnewhistholeから中央値をとってくる
    
    Double_t xq[2];
    xq[0]=0.5; xq[1]=1;
    Double_t q14x[2], q14y[2], q25x[2], q25y[2]; 

    
    newhisthole14x->GetQuantiles(2, q14x, xq);
    newhisthole14y->GetQuantiles(2, q14y, xq);
    newhisthole25x->GetQuantiles(2, q25x, xq);
    newhisthole25y->GetQuantiles(2, q25y, xq);
    std::cout << "q14x, q14y, q25x, q25y :" 
              << q14x[0] << ", "<< q14y[0] << ", "
              << q25x[0] << ", "<< q25y[0] << std::endl; 
    
    float gethwd[3];
    float gethole1[2];
    float gethole4[2];
    float gethole2[2];
    float gethole5[2];
    float gethole0[2];
    float gethole3[2];

    float hxm14=0;
    float hym14=0;
    float hxm25=0;
    float hym25=0;

    for(int icubepre  =0; icubepre <igood; icubepre++){
        
        //穴位置の2Dヒストグラムをつくる
        FillCenter1(cube[icubepre], hcenter1);
        FillCenter2(cube[icubepre], hcenter2);
        //fill を済ませてfor文を一度抜ける
    }
        //2Dヒストグラムを4等分するような直線を得る
    float p1[2][2], p2[2][2];    
    GetPols(hcenter1, p1);
    GetPols(hcenter2, p2);
    std::cout <<"p1[0]: "<< p1[0][0] << ", " << p1[0][1] << ", " 
              <<"p1[1]: "<< p1[1][0] << ", " << p1[1][1] << std::endl;
    



    for(int icube = 0; icube < igood; icube++){
        cube[icube]-> GetSize (gethwd);
        cube[icube]-> GetHole1(gethole1);
        cube[icube]-> GetHole4(gethole4);
        cube[icube]-> GetHole2(gethole2);
        cube[icube]-> GetHole5(gethole5);
        cube[icube]-> GetHole0(gethole0);
        cube[icube]-> GetHole3(gethole3);


        //以下ではだめ。
        ////穴位置の両面での平均をだした。
        //hxm14 = (gethole1[0] + gethole4[0])/2;
        //hym14 = (gethole1[1] + gethole4[1])/2;
        //hxm25 = (gethole2[0] + gethole5[0])/2;
        //hym25 = (gethole2[1] + gethole5[1])/2;
        
        //14面について
        hxm14 = gethwd[2] - (gethole0[1] + gethole3[1])/2
                          - (gethole1[0] + gethole4[0])/2;
        hym14 = (gethole1[1] + gethole4[1])/2;

        hxm25 = gethwd[1] - (gethole0[0] + gethole3[0])/2
                          - (gethole2[1] + gethole5[1])/2;
        hym25 = gethwd[0] - (gethole2[0] + gethole5[0])/2;

        if       (hym14 <  p1[0][1]* hxm14 + p1[0][0] &&
                  hym14 <  p1[1][1]* hxm14 + p1[1][0]){
            //1面の分類はA
            if      (hym25 <  p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 <  p2[1][1]* hxm25 + p2[1][0]){
                CatNum[0]++;
                cubeAA.push_back(cube[icube]);}
            else if (hym25 <  p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 >= p2[1][1]* hxm25 + p2[1][0]){
                CatNum[1]++;
                cubeAB.push_back(cube[icube]);}
            else if (hym25 >= p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 >= p2[1][1]* hxm25 + p2[1][0]){
                CatNum[2]++;
                cubeAC.push_back(cube[icube]);}
            else if (hym25 >= p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 <  p2[1][1]* hxm25 + p2[1][0]){
                CatNum[3]++;
                cubeAD.push_back(cube[icube]);}

        }else if (hym14 <  p1[0][1]* hxm14 + p1[0][0] &&
                  hym14 >= p1[1][1]* hxm14 + p1[1][0]){
            //1面の分類はB
            if      (hym25 <  p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 <  p2[1][1]* hxm25 + p2[1][0]){
                CatNum[4]++;
                cubeBA.push_back(cube[icube]);}
            else if (hym25 <  p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 >= p2[1][1]* hxm25 + p2[1][0]){
                CatNum[5]++;
                cubeBB.push_back(cube[icube]);}
            else if (hym25 >= p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 >= p2[1][1]* hxm25 + p2[1][0]){
                CatNum[6]++;
                cubeBC.push_back(cube[icube]);}
            else if (hym25 >= p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 <  p2[1][1]* hxm25 + p2[1][0]){
                CatNum[7]++;
                cubeBD.push_back(cube[icube]);}

        }else if (hym14 >= p1[0][1]* hxm14 + p1[0][0] &&
                  hym14 >= p1[1][1]* hxm14 + p1[1][0]){
            //1面の分類はC
            if      (hym25 <  p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 <  p2[1][1]* hxm25 + p2[1][0]){
                CatNum[8]++;
                cubeCA.push_back(cube[icube]);}
            else if (hym25 <  p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 >= p2[1][1]* hxm25 + p2[1][0]){
                CatNum[9]++;
                cubeCB.push_back(cube[icube]);}
            else if (hym25 >= p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 >= p2[1][1]* hxm25 + p2[1][0]){
                CatNum[10]++;
                cubeCC.push_back(cube[icube]);}
            else if (hym25 >= p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 <  p2[1][1]* hxm25 + p2[1][0]){
                CatNum[11]++;
                cubeCD.push_back(cube[icube]);}
            
        }else if (hym14 >= p1[0][1]* hxm14 + p1[0][0] &&
                  hym14 <  p1[1][1]* hxm14 + p1[1][0]){
            //1面の分類はD
            if      (hym25 <  p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 <  p2[1][1]* hxm25 + p2[1][0]){
                CatNum[12]++;
                cubeDA.push_back(cube[icube]);}
            else if (hym25 <  p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 >= p2[1][1]* hxm25 + p2[1][0]){
                CatNum[13]++;
                cubeDB.push_back(cube[icube]);}
            else if (hym25 >= p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 >= p2[1][1]* hxm25 + p2[1][0]){
                CatNum[14]++;
                cubeDC.push_back(cube[icube]);}
            else if (hym25 >= p2[0][1]* hxm25 + p2[0][0] &&
                     hym25 <  p2[1][1]* hxm25 + p2[1][0]){
                CatNum[15]++;
                cubeDD.push_back(cube[icube]);}
        }
        

        //if文で分類
//        if (hxm14 >= q14x[0] && hym14 < q14y[0]){ 
//            //1面の分類はA
//            if      (hxm25 >= q25x[0] && hym25 <  q25y[0]){
//                CatNum[0]++;
//                cubeAA.push_back(cube[icube]);}
//            else if (hxm25 <  q25x[0] && hym25 <  q25y[0]){
//                CatNum[1]++;
//                cubeAB.push_back(cube[icube]);}
//            else if (hxm25 <  q25x[0] && hym25 >= q25y[0]){
//                CatNum[2]++;
//                cubeAC.push_back(cube[icube]);}
//            else if (hxm25 >= q25x[0] && hym25 >= q25y[0]){
//                CatNum[3]++;
//                cubeAD.push_back(cube[icube]);}
//        }
//        else if (hxm14 <  q14x[0] && hym14 <  q14y[0]){ 
//            //1面の分類はB
//            if      (hxm25 >= q25x[0] && hym25 <  q25y[0]){
//                CatNum[4]++;
//                cubeBA.push_back(cube[icube]);}
//            else if (hxm25 <  q25x[0] && hym25 <  q25y[0]){
//                CatNum[5]++;
//                cubeBB.push_back(cube[icube]);}
//            else if (hxm25 <  q25x[0] && hym25 >= q25y[0]){
//                CatNum[6]++;
//                cubeBC.push_back(cube[icube]);}
//            else if (hxm25 >= q25x[0] && hym25 >= q25y[0]){
//                CatNum[7]++;
//                cubeBD.push_back(cube[icube]);}
//        }
//        else if (hxm14 <  q14x[0] && hym14 >= q14y[0]){ 
//            //1面の分類はC
//            if      (hxm25 >= q25x[0] && hym25 <  q25y[0]){
//                CatNum[8]++;
//                cubeCA.push_back(cube[icube]);}
//            else if (hxm25 <  q25x[0] && hym25 <  q25y[0]){
//                CatNum[9]++;
//                cubeCB.push_back(cube[icube]);}
//            else if (hxm25 <  q25x[0] && hym25 >= q25y[0]){
//                CatNum[10]++;
//                cubeCC.push_back(cube[icube]);}
//            else if (hxm25 >= q25x[0] && hym25 >= q25y[0]){
//                CatNum[11]++;
//                cubeCD.push_back(cube[icube]);}
//        }
//        else if (hxm14 >= q14x[0] && hym14 >= q14y[0]){ 
//            //1面の分類はD
//            if      (hxm25 >= q25x[0] && hym25 <  q25y[0]){
//                CatNum[12]++;
//                cubeDA.push_back(cube[icube]);}
//            else if (hxm25 <  q25x[0] && hym25 <  q25y[0]){
//                CatNum[13]++;
//                cubeDB.push_back(cube[icube]);}
//            else if (hxm25 <  q25x[0] && hym25 >= q25y[0]){
//                CatNum[14]++;
//                cubeDC.push_back(cube[icube]);}
//            else if (hxm25 >= q25x[0] && hym25 >= q25y[0]){
//                CatNum[15]++;
//                cubeDD.push_back(cube[icube]);}
//        }
    }
    for (int icat = 0; icat <16; icat ++){
        std::cout << "Category " << icat +1 << ":" 
                  << CatNum[icat] << std::endl;
    }

        //std::cout << "cubeAA :" << cubeAA.size() << std::endl;
        //std::cout << "cubeAB :" << cubeAB.size() << std::endl;
        //std::cout << "cubeAC :" << cubeAC.size() << std::endl;
        //std::cout << "cubeAD :" << cubeAD.size() << std::endl;
//    const Int_t NRGBs = 5;    //色の区切りの数（区切り色　= RGB空間に打たれた点のさす色）
//    const Int_t NCont = 255;  //グラデーションの段数
// 
////グラデーションの色を配列で指定
//    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 }; 
//    //stopはカラーバーでの位置（比率）。つまり、区切りの色がくる場所。
//    //Red、Green,Blueは各区切り位置でのR,G,Bの値（区切り色を指定）
//    Double_t Red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 }; 
//    //RGBは一般的なRGBの値を255で割って規格化（？）している。
//    Double_t Green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 }; 
//    //縦に見る。カラーバーの位置0.00でのRGB=(0.00,0.00,0.51),
//    Double_t Blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 }; 
//    //位置0.34でのRGB=(0.00,0.81,1.00),のようになっている。
//    TColor::CreateGradientColorTable(NRGBs, stops, Red, Green, Blue, NCont);
//    //グラデーションを作る。勝手にgStyle->SetPalette()してくれる
//    gStyle->SetNumberContours(NCont);
    //gStyle->SetOptStat(0);


    std::ofstream fout("sizemax.txt" );
    TH1F * hdiffx = new TH1F ("hdiffx", 
          "differential of two hole centers",50, 0, 1);
    TH1F * hdiffy = new TH1F ("hdiffy", 
          "differential of two hole centers",50, 0, 1);
    TH2F * hpos = new TH2F ("hpos", 
          "distance between centers of holes; x;y", 
            22,0,22, 23,0,23);
    TH1F * h_over = new TH1F ("h_over", "h_over",10,0,10);
    Int_t num_over= 0;

    //キューブをシャッフルする。
    for (int shuff = 0; shuff <unitnum; shuff++){
        std::mt19937_64 get_rand_mt(shuff);
        //std::mt19937_64 get_rand_mt(0);
        std::shuffle(cube.begin(), cube.end(), get_rand_mt );
        //分類ごとにシャッフルする
        std::shuffle(cubeAA.begin(), cubeAA.end(), get_rand_mt);
        std::shuffle(cubeAB.begin(), cubeAB.end(), get_rand_mt);
        std::shuffle(cubeAC.begin(), cubeAC.end(), get_rand_mt);
        std::shuffle(cubeAD.begin(), cubeAD.end(), get_rand_mt);
        std::shuffle(cubeBA.begin(), cubeBA.end(), get_rand_mt);
        std::shuffle(cubeBB.begin(), cubeBB.end(), get_rand_mt);
        std::shuffle(cubeBC.begin(), cubeBC.end(), get_rand_mt);
        std::shuffle(cubeBD.begin(), cubeBD.end(), get_rand_mt);
        std::shuffle(cubeCA.begin(), cubeCA.end(), get_rand_mt);
        std::shuffle(cubeCB.begin(), cubeCB.end(), get_rand_mt);
        std::shuffle(cubeCC.begin(), cubeCC.end(), get_rand_mt);
        std::shuffle(cubeCD.begin(), cubeCD.end(), get_rand_mt);
        std::shuffle(cubeDA.begin(), cubeDA.end(), get_rand_mt);
        std::shuffle(cubeDB.begin(), cubeDB.end(), get_rand_mt);
        std::shuffle(cubeDC.begin(), cubeDC.end(), get_rand_mt);
        std::shuffle(cubeDD.begin(), cubeDD.end(), get_rand_mt);


    //8x8行列を、(4x4行列)x4だと思う
    for (int ky = 0; ky < 2; ky ++){
        for (int kx = 0; kx < 2; kx ++){

            //ArrangebyHole(cube[8*iarry + iarrx], 
            //          pitch*(iarrx+1), pitch*(iarry+1), 
            //          posxhx[iarry][iarrx], 
            //          posxhy[iarry][iarrx],
            //          posxhz[iarry][iarrx]);
                        
            ArrangebyHole(cubeAA[kx+2*ky], 
                      pitch*(1+4*kx), pitch*(1+4*ky), 
                      posxhx[4*ky][4*kx], 
                      posxhy[4*ky][4*kx],
                      posxhz[4*ky][4*kx]);
            ArrangebyHole(cubeAB[kx+2*ky], 
                      pitch*(1+1+4*kx), pitch*(1+4*ky), 
                      posxhx[4*ky][1+4*kx], 
                      posxhy[4*ky][1+4*kx],
                      posxhz[4*ky][1+4*kx]);
            ArrangebyHole(cubeAC[kx+2*ky], 
                      pitch*(1+2+4*kx), pitch*(1+4*ky), 
                      posxhx[4*ky][2+4*kx], 
                      posxhy[4*ky][2+4*kx],
                      posxhz[4*ky][2+4*kx]);
            ArrangebyHole(cubeAD[kx+2*ky], 
                      pitch*(1+3+4*kx), pitch*(1+4*ky), 
                      posxhx[4*ky][3+4*kx], 
                      posxhy[4*ky][3+4*kx],
                      posxhz[4*ky][3+4*kx]);
            ArrangebyHole(cubeBA[kx+2*ky], 
                      pitch*(1+4*kx), pitch*(1+1+4*ky), 
                      posxhx[1+4*ky][4*kx], 
                      posxhy[1+4*ky][4*kx],
                      posxhz[1+4*ky][4*kx]);
            ArrangebyHole(cubeBB[kx+2*ky], 
                      pitch*(1+1+4*kx), pitch*(1+1+4*ky), 
                      posxhx[1+4*ky][1+4*kx], 
                      posxhy[1+4*ky][1+4*kx],
                      posxhz[1+4*ky][1+4*kx]);
            ArrangebyHole(cubeBC[kx+2*ky], 
                      pitch*(1+2+4*kx), pitch*(1+1+4*ky), 
                      posxhx[1+4*ky][2+4*kx], 
                      posxhy[1+4*ky][2+4*kx],
                      posxhz[1+4*ky][2+4*kx]);
            ArrangebyHole(cubeBD[kx+2*ky], 
                      pitch*(1+3+4*kx), pitch*(1+1+4*ky), 
                      posxhx[1+4*ky][3+4*kx], 
                      posxhy[1+4*ky][3+4*kx],
                      posxhz[1+4*ky][3+4*kx]);
            ArrangebyHole(cubeCA[kx+2*ky], 
                      pitch*(1+4*kx), pitch*(1+2+4*ky), 
                      posxhx[2+4*ky][4*kx], 
                      posxhy[2+4*ky][4*kx],
                      posxhz[2+4*ky][4*kx]);
            ArrangebyHole(cubeCB[kx+2*ky], 
                      pitch*(1+1+4*kx), pitch*(1+2+4*ky), 
                      posxhx[2+4*ky][1+4*kx], 
                      posxhy[2+4*ky][1+4*kx],
                      posxhz[2+4*ky][1+4*kx]);
            ArrangebyHole(cubeCC[kx+2*ky], 
                      pitch*(1+2+4*kx), pitch*(1+2+4*ky), 
                      posxhx[2+4*ky][2+4*kx], 
                      posxhy[2+4*ky][2+4*kx],
                      posxhz[2+4*ky][2+4*kx]);
            ArrangebyHole(cubeCD[kx+2*ky], 
                      pitch*(1+3+4*kx), pitch*(1+2+4*ky), 
                      posxhx[2+4*ky][3+4*kx], 
                      posxhy[2+4*ky][3+4*kx],
                      posxhz[2+4*ky][3+4*kx]);
            ArrangebyHole(cubeDA[kx+2*ky], 
                      pitch*(1+4*kx), pitch*(1+3+4*ky), 
                      posxhx[3+4*ky][4*kx], 
                      posxhy[3+4*ky][4*kx],
                      posxhz[3+4*ky][4*kx]);
            ArrangebyHole(cubeDB[kx+2*ky], 
                      pitch*(1+1+4*kx), pitch*(1+3+4*ky), 
                      posxhx[3+4*ky][1+4*kx], 
                      posxhy[3+4*ky][1+4*kx],
                      posxhz[3+4*ky][1+4*kx]);
            ArrangebyHole(cubeDC[kx+2*ky], 
                      pitch*(1+2+4*kx), pitch*(1+3+4*ky), 
                      posxhx[3+4*ky][2+4*kx], 
                      posxhy[3+4*ky][2+4*kx],
                      posxhz[3+4*ky][2+4*kx]);
            ArrangebyHole(cubeDD[kx+2*ky], 
                      pitch*(1+3+4*kx), pitch*(1+3+4*ky), 
                      posxhx[3+4*ky][3+4*kx], 
                      posxhy[3+4*ky][3+4*kx],
                      posxhz[3+4*ky][3+4*kx]);
//            for (int i6 = 0; i6 <6 ; i6++){
//                cout << posxhx[iarry][iarrx][i6] << endl;
//                cout << posxhy[iarry][iarrx][i6] << endl;
//
//            }
//            RotateCube(cube[8*iarry + iarrx], 
//                      pitch*(iarrx+1), pitch*(iarry+1),
//                      posxhx[iarry][iarrx],
//                      posxhy[iarry][iarrx],
//                      tan);
            //RotateEachCube(pitch*(iarrx+1), pitch*(iarry+1),
            //          posxhx[iarry][iarrx],
            //          posxhy[iarry][iarrx]
            //          );

        }
    }
    
    TH1F * hdiffxSingle = new TH1F ("hdiffxSingle", 
            "differential of two hole centers",50, 0, 1);
    TH1F * hdiffySingle = new TH1F ("hdiffySingle", 
            "differential of two hole centers",50, 0, 1);
//    TH1F * hdiffown = new TH1F ("hdiffown", 
//          "differential of each side of hole ",50, -1, 1);
//    TH2F * nexthole = new TH2F ("nexthole", 
//          "points where next hole is", 50, -1, 1 , 50, -1, 1); 

    num_over = 0;
    cannotx = 0;
    cannoty = 0;
    //if (shuff==2747){
    FillDiffy( hdiffx, hdiffxSingle, num_over, hpos, 
               posxhx, posxhy, posxhz, cannoty, pitch,shuff);
    FillDiffx( hdiffy, hdiffySingle, num_over, hpos, 
               posxhx, posxhy, posxhz, cannotx, pitch);
    //}
//    checkdiff( hdiffown, posxhx, posxhy, posxhz, cannotx);
    
//    std::cout << "num_over : " << num_over << std::endl;

    //if (hdiffxSingle->Integral(25,50) > 0 || 
    //    hdiffySingle->Integral(25,50) > 0)
    if (hdiffxSingle->Integral(hdiffxSingle->GetXaxis()->FindBin(0.5),
                               hdiffxSingle->GetXaxis()->FindBin(1.)) > 0 || 
        hdiffySingle->Integral(hdiffySingle->GetXaxis()->FindBin(0.5),
                               hdiffySingle->GetXaxis()->FindBin(1.)) > 0){

        cannot ++;
    }
    hdiffxSingle->Delete();
    hdiffySingle->Delete();
//    hdiffown->Delete();
//    nexthole->Delete();
    //TCanvas  * cpos = new TCanvas("cpos", "cpos");
//    hpos->SetMarkerStyle(8);
    //hpos->Draw("colz text");
    h_over->Fill(num_over);

    if (num_over  >= 1 ) {
        std::cout << "num_over : " << num_over << ", set number: " 
                  << shuff << endl;
    }
    /*
    TCanvas * can1 = new TCanvas("can1", "can1");
    hdiffx->Draw();
    TCanvas * can2 = new TCanvas("can2", "can2");
    hdiffy->Draw();
    */

    int miss   = 0;
    int OutOfRange = 0;
    int yclear = 0;
    int xclear = 0;    
    int andclear = 0;

    
     
       // hogehoge
    ///**************************************************************






    ///縦に並べる。
        float hole[8]    = {0,0,0,0,0,0,0,0};
        float fibarea[8] = {0,0,0,0,0,0,0,0};
        float sizemax[2] =  {0,0};
        float sizediff = 0;
    
        //std::cout << "===array 1:===" << std::endl;
/*        CubeArrangey1(cube[0], cube[1], cube[2], cube[3],
                     cube[4], cube[5], cube[6], cube[7],
                     hole, fibarea, sizemax);
    //    //std::cout << hole[0] <<" "<< fibarea[0]<<" " << sizemax[0] << std::endl;
        //sizediff = 82.1 - sizemax[0];
        ////std::cout << "sizediff : "<< sizediff << std::endl;
    
    
    
    
    
        //std::cout << "===array 2:===" << std::endl;
        CubeArrangey2(cube[8],  cube[9],  cube[10], cube[11],
                     cube[12], cube[13], cube[14], cube[15],
                     hole, fibarea, sizemax);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemax[0] >= sizemax[1]){
        }
        else{
        sizemax[0] = sizemax[1];
        }
        
        //std::cout << "sizemax : "<< sizemax[0] << "\n" << std::endl;
    
    
    
    
    
        //std::cout << "===array 3:===" << std::endl;
        CubeArrangey2(cube[16], cube[17], cube[18], cube[19],
                     cube[20], cube[21], cube[22], cube[23],
                     hole, fibarea, sizemax);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemax[0] >= sizemax[1]){
        }
        else{
        sizemax[0] = sizemax[1];
        }
        
        //std::cout << "sizemax : "<< sizemax[0] << "\n" << std::endl;
    
    
    
    
    
        //std::cout << "===array 4:===" << std::endl;
        CubeArrangey2(cube[24], cube[25], cube[26], cube[27],
                     cube[28], cube[29], cube[30], cube[31],
                     hole, fibarea, sizemax);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemax[0] >= sizemax[1]){
        }
        else{
        sizemax[0] = sizemax[1];
        }
        
        //std::cout << "sizemax : "<< sizemax[0] << "\n" << std::endl;
    
    
        //std::cout << "===array 5:===" << std::endl;
        CubeArrangey2(cube[32], cube[33], cube[34], cube[35],
                     cube[36], cube[37], cube[38], cube[39],
                     hole, fibarea, sizemax);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemax[0] >= sizemax[1]){
        }
        else{
        sizemax[0] = sizemax[1];
        }
        
        //std::cout << "sizemax : "<< sizemax[0] << "\n" << std::endl;
    
    
        //std::cout << "===array 6:===" << std::endl;
        CubeArrangey2(cube[40], cube[41], cube[42], cube[43],
                     cube[44], cube[45], cube[46], cube[47],
                     hole, fibarea, sizemax);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemax[0] >= sizemax[1]){
        }
        else{
        sizemax[0] = sizemax[1];
        }
        
        //std::cout << "sizemax : "<< sizemax[0] << "\n" << std::endl;
    
    
        //std::cout << "===array 7:===" << std::endl;
        CubeArrangey2(cube[48], cube[49], cube[50], cube[51],
                     cube[52], cube[53], cube[54], cube[55],
                     hole, fibarea, sizemax);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemax[0] >= sizemax[1]){
        }
        else{
        sizemax[0] = sizemax[1];
        }
        
        //std::cout << "sizemax : "<< sizemax[0] << "\n" << std::endl;
    
    
        //std::cout << "===array 8:===" << std::endl;
        CubeArrangey2(cube[56], cube[57], cube[58], cube[59],
                     cube[60], cube[61], cube[62], cube[63],
                     hole, fibarea, sizemax);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemax[0] >= sizemax[1]){
        }
        else{
        sizemax[0] = sizemax[1];
        }
        
        //std::cout << "sizemax : "<< sizemax[0] << "\n" << std::endl;
    
    
    
    
    
    
        /////////////////////////////////////////////////////////////////////////////////
        ///横方向にも同様に並べる。
        float holex[8]    = {0,0,0,0,0,0,0,0};
        float fibareax[8] = {0,0,0,0,0,0,0,0};
        float sizemaxx[2] =  {0,0};
        float sizediffx = 0;
    
        //std::cout << "===array 1:===" << std::endl;
        CubeArrangex1(cube[0],  cube[8],  cube[16], cube[24],
                     cube[32], cube[40], cube[48], cube[56],
                     holex, fibareax, sizemaxx);
    
    
        //std::cout << "===array 2:===" << std::endl;
        CubeArrangex2(cube[1],  cube[9],  cube[17], cube[25],
                     cube[33], cube[41], cube[49], cube[57],
                     holex, fibareax, sizemaxx);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemaxx[0] >= sizemaxx[1]){
        }
        else{
        sizemaxx[0] = sizemaxx[1];
        }
        
        //std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
    
    
        //std::cout << "===array 3:===" << std::endl;
        CubeArrangex2(cube[2],  cube[10],  cube[18], cube[26],
                     cube[34], cube[42], cube[50], cube[58],
                     holex, fibareax, sizemaxx);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemaxx[0] >= sizemaxx[1]){
        }
        else{
        sizemaxx[0] = sizemaxx[1];
        }
        
        //std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
    
    
        //std::cout << "===array 4:===" << std::endl;
        CubeArrangex2(cube[3],  cube[11],  cube[19], cube[27],
                     cube[35], cube[43], cube[51], cube[59],
                     holex, fibareax, sizemaxx);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemaxx[0] >= sizemaxx[1]){
        }
        else{
        sizemaxx[0] = sizemaxx[1];
        }
        
        //std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
    
        //std::cout << "===array 5:===" << std::endl;
        CubeArrangex2(cube[4],  cube[12],  cube[20], cube[28],
                     cube[36], cube[44], cube[52], cube[60],
                     holex, fibareax, sizemaxx);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemaxx[0] >= sizemaxx[1]){
        }
        else{
        sizemaxx[0] = sizemaxx[1];
        }
        
        //std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
    
        //std::cout << "===array 6:===" << std::endl;
        CubeArrangex2(cube[5],  cube[13],  cube[21], cube[29],
                     cube[37], cube[45], cube[53], cube[61],
                     holex, fibareax, sizemaxx);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemaxx[0] >= sizemaxx[1]){
        }
        else{
        sizemaxx[0] = sizemaxx[1];
        }
        
        //std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
        //std::cout << "===array 7:===" << std::endl;
        CubeArrangex2(cube[6],  cube[14],  cube[22], cube[30],
                     cube[38], cube[46], cube[54], cube[62],
                     holex, fibareax, sizemaxx);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemaxx[0] >= sizemaxx[1]){
        }
        else{
        sizemaxx[0] = sizemaxx[1];
        }
        
        //std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
        //std::cout << "===array 8:===" << std::endl;
        CubeArrangex2(cube[7],  cube[15],  cube[23], cube[31],
                     cube[39], cube[47], cube[55], cube[63],
                     holex, fibareax, sizemaxx);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemaxx[0] >= sizemaxx[1]){
        }
        else{
        sizemaxx[0] = sizemaxx[1];
        }
  */      
        //std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
        //std::cout << "********************************************" << std::endl;
        //std::cout << "sizemax::  y: "<< sizemax[0] << ", x: "<< sizemaxx[0] << std::endl;
        //fout << sizemax[0] << "  " << sizemaxx[0] << std::endl;
        //std::cout << "********************************************" << std::endl;
        float widthrange = 82.3;
        float sizemaxx[1];
        sizemaxx[0] = 0;
        if (sizemax[0]==100 || sizemaxx[0]==100){
            miss += 1;
            //std::cout << "miss : " << miss << std::endl;

        }
        else{

            if (sizemax[0] <= widthrange){
                yclear += 1;
            }
            if (sizemaxx[0] <= widthrange){
                xclear += 1;
            }
            if (sizemax[0] <= widthrange && sizemaxx[0] <= widthrange){
                andclear += 1;
            }
            if (sizemax[0] > widthrange || sizemaxx[0] > widthrange){
                std::cout << "sizemax::  y: "<< sizemax[0] << ", x: "<< sizemaxx[0] << std::endl;
                OutOfRange += 1 ;
            }
            else{
            }
        }
   } 
    
        TCanvas * canvas1 = new TCanvas("canvas1", "canvas1");
        hdiffx->Draw();
        TCanvas * canvas2 = new TCanvas("canvas2", "canvas2");
        hdiffy->Draw();
        TCanvas * c_over  = new TCanvas("c_over", "c_over");
        h_over->Draw();
        TCanvas * c_center= new TCanvas("c_center", "c_center");
        hcenter1->Draw();
        TCanvas * c_pos   = new TCanvas("c_pos", "c_pos");
        hpos->Draw("colz text");
       // 残ったやつ取って並べて、
       // Getxxxxx の関数などを class 追加して、数値のばらつきを取ってきて計算したり。
     
       // hogehoge
       std::cout << "************************************************" << std::endl;
       std::cout << "simulated cube : "<< cubemax << std::endl;
       std::cout << "good cube      : "<< cube.size() << std::endl;
       std::cout << "good rate      : "<< (float) cube.size()*100/cubemax << "%" << std::endl;
       std::cout << "************************************************" << std::endl;
       std::cout << "tan      : " << tan    << std::endl; 
       std::cout << "cannot   : " << cannot << " /" << unitnum << ", " << (float) cannot*100/unitnum << "%" << std::endl;
   std::cout << "time : "<< (unsigned int) time(NULL) << std::endl; 


    //テキストファイルに出力
    std::ofstream ratetxt("good_clear_ela.txt", std::ios::app);
//    ratetxt << Nall << " " << (float) cube.size() * 100/cubemax
//                    << " " << (float) andclear * 100/unitnum << std::endl;

    ratetxt.close();

    fout.close();
}

void analysis_hole()
{


    TFile * fr = new TFile("201007hist.root", "read");//半径だけはここから持ってくる
    TFile * fin = new TFile("hist_correlation1007.root", "read");//大きさと穴の位置は相関を持たせる
    TFile * fh = new TFile ("201102hist.root", "read"); //穴はここから

    int Nall = 0;
    int hmin = 0;
    int hmax = 0;
    int smin = 0;
    int smax = 0;

//    for (int ismin = 0; ismin < 2+1; ismin++){
//        for (int ismax = 0; ismax < 5+1; ismax++){
//            for (int ihmin = 0; ihmin < 5+1; ihmin++){
//                for (int ihmax = 0; ihmax < 5+1; ihmax++){
//                    std::cout << "\nsize min = 649.5 + " << ismin << std::endl;
//                    std::cout << "size max = 664.3 + " << ismax << std::endl;
//                    std::cout << "hole min = 162.5 + " << ihmin << std::endl;
//                    std::cout << "hole max = 199.5 + " << ihmax << std::endl;

                    Nall = 1;//Nall +1 ;
                    hmax =  3;// ihmax ;
                    hmin =  2*3;// 2*ihmin ;
                    smax =  3;// ismax ;
                    smin =  0;// ismin ;
                    analysis_hole1(fr, fin, fh, Nall, hmax, hmin, smax, smin);
//                }
//            }
//        }
//    }
}

