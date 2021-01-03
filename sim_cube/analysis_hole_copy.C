#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>

#include <vector>
#include "classCube_hole_copy.cc"

#include <stdlib.h>
#include <time.h>

#include <random>
#include <algorithm>

// root -l analysis.C




void analysis_hole1(TFile* fr, TFile* fin, TFile* fh,  int Nall, 
                      int hmax, int hmin, int smax, int smin)
{

    gRandom->SetSeed(2);
//    gRandom->SetSeed((unsigned int ) time(NULL));
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
    
    int cubemax = 10000;//つくるキューブの数
    int unitnum = 5000;//つくる8x8セットの数

    TH2F * h_decideTop = new TH2F("h_decideTop","h_decideTop",
                                     100, 140*0.01554, 220*0.01554,
                                     100, 140*0.01554, 220*0.01554);
    TH1F * h_decideTopx0 = new TH1F("h_decideTopx0","h_decideTopx0",
                                     100, 140*0.01554, 220*0.01554);
    TH1F * h_decideTopd = new TH1F("h_decideTopd","h_decideTopd",
                                     100, 0*0.01554, 50*0.01554);
    TH1F * h_decideTopdmin = new TH1F("h_decideTopdmin","h_decideTopdmin",
                                     100, 0*0.01554, 50*0.01554);

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
    //フィット直線に沿った穴位置分布を確認するための2Dヒストグラム
    TH2F * hcenterXY1 = new  TH2F ("hcenterXY1", "hcenterXY1", 
                                    100, -0.5, 0.5, 100, -0.5, 0.5);
    TH2F * hcenterXY2 = new  TH2F ("hcenterXY2", "hcenterXY2", 
                                    100, -0.5, 0.5, 100, -0.5, 0.5);
    TH1F * hcenterX1 = new TH1F ("hcenterX1", "hcenterX1", 100, -0.5, 0.5);
    TH1F * hcenterY1 = new TH1F ("hcenterY1", "hcenterY1", 100, -0.5, 0.5);
    TH1F * hcenterX2 = new TH1F ("hcenterX2", "hcenterX2", 100, -0.5, 0.5);
    TH1F * hcenterY2 = new TH1F ("hcenterY2", "hcenterY2", 100, -0.5, 0.5);
//    TH2F * hcenterXYXY1 = new  TH2F ("hcenterXYXY1", "hcenterXYXY1", 
//                                    100, -0.5, 0.5, 100, -0.5, 0.5);
//    TH2F * hcenterXYXY2 = new  TH2F ("hcenterXYXY2", "hcenterXYXY2", 
//                                    100, -0.5, 0.5, 100, -0.5, 0.5);

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


    Cube *cubeSizeCheck[64];
    


 
    double _sMean = 659.2; 
    //if文での参照用。macro_forrangeif.cppよりとってきた

    for (int icu = 0; icu<cubemax; icu++) {
        sizexyz->GetRandom3(sizehwd[0], sizehwd[1], sizehwd[2]);
        //sizexyz->GetRandom3(sizehwd[0], sizehwd[1], sizehwd[2]);
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
         /*
//         649.5 + smin < sizehwd[0] && sizehwd[0] < 664.3 + smax &&
//         649.5 + smin < sizehwd[1] && sizehwd[1] < 664.3 + smax &&
//         649.5 + smin < sizehwd[2] && sizehwd[2] < 664.3 + smax &&

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
         
         649.5  < sizehwd[0] && sizehwd[0] < 664.1  &&
         649.5  < sizehwd[1] && sizehwd[1] < 664.1  &&
         649.5  < sizehwd[2] && sizehwd[2] < 664.1  &&

         47.8 < r[0] &&
         47.8 < r[1] &&
         47.8 < r[2] &&
         47.8 < r[3] &&
         47.8 < r[4] &&
         47.8 < r[5] &&
         */
            1==1

            ){        
            igood += 1; 
            //ベクタにキューブを追加する
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

           //穴位置の平均を取ってくる。
           h_decideTop->Fill(0.01554*(hole0[0]+hole3[0])/2, 
                             0.01554*(hole0[1]+hole3[1])/2);
           h_decideTop->Fill(0.01554*(hole1[0]+hole4[0])/2, 
                             0.01554*(hole1[1]+hole4[1])/2);
           h_decideTop->Fill(0.01554*(hole2[0]+hole5[0])/2, 
                             0.01554*(hole2[1]+hole5[1])/2);
           h_decideTopx0->Fill(0.01554*(hole0[0]+hole3[0])/2); 

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
    float pitch = 10.39;
    //float tan = 0.4/102.4;
    float tan = 0/102.4;
    int cannotx = 0;
    int cannoty = 0;
    int cannot  = 0;

    int CatNum[16]= {};




    //この辺りで"穴の位置が最も平均に近いもの"が天面に来るように、
    //キューブの向きを変えておく。
    float xhMean = h_decideTop->GetMean(1);
    float yhMean = h_decideTop->GetMean(2);
    float hwdicube[3];
    for (int icubeDir = 0; icubeDir < igood; icubeDir++){
        
        ChangeCubeDirection(cube[icubeDir], xhMean, yhMean, h_decideTopd, h_decideTopdmin);
        cube[icubeDir]->GetSize(hwdicube);
//        std::cout << "after (h,w,d): (" << hwdicube[0] <<", "<<hwdicube[1] <<", "
//                  << hwdicube[2] << ")" << std::endl;
    }



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
    
    float center1mean1 = hcenter1->GetMean(1);
    float center1mean2 = hcenter1->GetMean(2);
    float center2mean1 = hcenter2->GetMean(1);
    float center2mean2 = hcenter2->GetMean(2);
    float p1_tan = p1[0][1];
    float p2_tan = p2[0][1];
    int iInside = 0;
    //フィットした直線に沿った座標軸で2Dヒストグラムをつくる
    for(int icubeXY = 0; icubeXY < igood; icubeXY++){
        FillCenterXY1(cube[icubeXY], hcenterXY1, hcenterX1, hcenterY1, 
                      center1mean1, center1mean2, p1_tan);
        FillCenterXY2(cube[icubeXY], hcenterXY2, hcenterX2, hcenterY2,
                      center2mean1, center2mean2, p2_tan);
    }
    //ヒストグラムhcenterX1などから中央値をとってくる
    Double_t qX1[2], qY1[2], qX2[2], qY2[2]; 
    
    hcenterX1->GetQuantiles(2, qX1, xq);
    hcenterY1->GetQuantiles(2, qY1, xq);
    hcenterX2->GetQuantiles(2, qX2, xq);
    hcenterY2->GetQuantiles(2, qY2, xq);
    std::cout << "qX1, qY1, qX2, qY2 :" 
              << qX1[0] << ", "<< qY1[0] << ", "
              << qX2[0] << ", "<< qY2[0] << std::endl; 
    
    float SDevX1, SDevY1, SDevX2, SDevY2;
    SDevX1 = hcenterX1->GetStdDev();
    SDevY1 = hcenterY1->GetStdDev();
    SDevX2 = hcenterX2->GetStdDev();
    SDevY2 = hcenterY2->GetStdDev();

//    float q1[2][2], q2[2][2];    
//    GetPols(hcenter1, q1);
//    GetPols(hcenter2, q2);
//    float q1_tan = q1[0][1];
//    float q2_tan = q2[0][1];
//    for(int icubeXYXY = 0; icubeXYXY < igood; icubeXYXY++){
//        FillCenterXYXY1(cube[icubeXYXY], hcenterXYXY1, 0, 0, q1_tan, center1mean1, center1mean2, p1_tan);
//        FillCenterXYXY2(cube[icubeXYXY], hcenterXYXY2, 0, 0, q2_tan, center2mean1, center2mean2, p2_tan);
//    }



////////////////////////////////////////////////////
//楕円でカットをかける。さらに４領域に分類する。
///*
    for(int icube = 0; icube < igood; icube++){
        //cube[icube]の穴位置(X,Y)を求めておく。
        float X1 = 0;
        float Y1 = 0;
        float X2 = 0;
        float Y2 = 0;
        GetEllipse1(cube[icube], center1mean1, center1mean2, p1_tan, X1, Y1);
        GetEllipse2(cube[icube], center2mean1, center2mean2, p2_tan, X2, Y2);

       if (
           EllipseCut1(cube[icube], SDevX1*2.3, SDevY1*3, 
                      center1mean1, center1mean2, p1_tan) == 1 &&
           EllipseCut2(cube[icube], SDevX2*2.3, SDevY2*3,
                      center2mean1, center2mean2, p2_tan) == 1 &&
           //Y2 < -0.22*X2 && 
           //Y2 > 0.48*X2 && 
           //X2 < 0 && 
           1==1){
           iInside ++;
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
    }
//*/
    for (int icat = 0; icat <16; icat ++){
        //std::cout << "Category " << icat +1 << ":" 
          //        << CatNum[icat] << std::endl;
    }

        //std::cout << "cubeAA :" << cubeAA.size() << std::endl;
        //std::cout << "cubeAB :" << cubeAB.size() << std::endl;
        //std::cout << "cubeAC :" << cubeAC.size() << std::endl;
        //std::cout << "cubeAD :" << cubeAD.size() << std::endl;
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
    float checkhwd[64][3];
    float checkhole0[64][2];
    float checkhole3[64][2];
    int OverPitch     = 0;
    int OverPitch_each= 0;
    int OverPitch_set = 0;
    TH1F * h_overPitch = new TH1F ("h_overPitch", "h_overPitch", 100,10,11);

//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
    //キューブをシャッフルする。
    //シャッフルして隣り合うやつとの大きさをみる。
    //さらに、隣り合うやつとの穴の位置のずれをみる。
///*
    for (int shuff = 0; shuff <unitnum; shuff++){
        //std::mt19937_64 get_rand_mt(shuff);
        std::mt19937_64 get_rand_mt(0);
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

        //隣り合うやつの大きさをみる
        for (int i = 0; i < 64; i++){
            for (int j = 0; j < 3 ; j++){
                checkhwd[i][j]  = 0.;
                if (j < 2){
                checkhole0[i][j] = 0.;
                checkhole3[i][j] = 0.;
                }
            }
        }
        for (int isize = 0; isize < 4; isize ++){

            cubeSizeCheck[16*isize]    = cubeAA[isize];
            cubeSizeCheck[16*isize+1]  = cubeAB[isize];
            cubeSizeCheck[16*isize+2]  = cubeAC[isize];
            cubeSizeCheck[16*isize+3]  = cubeAD[isize];
            cubeSizeCheck[16*isize+4]  = cubeBA[isize];
            cubeSizeCheck[16*isize+5]  = cubeBB[isize];
            cubeSizeCheck[16*isize+6]  = cubeBC[isize];
            cubeSizeCheck[16*isize+7]  = cubeBD[isize];
            cubeSizeCheck[16*isize+8]  = cubeCA[isize];
            cubeSizeCheck[16*isize+9]  = cubeCB[isize];
            cubeSizeCheck[16*isize+10] = cubeCC[isize];
            cubeSizeCheck[16*isize+11] = cubeCD[isize];
            cubeSizeCheck[16*isize+12] = cubeDA[isize];
            cubeSizeCheck[16*isize+13] = cubeDB[isize];
            cubeSizeCheck[16*isize+14] = cubeDC[isize];
            cubeSizeCheck[16*isize+15] = cubeDD[isize];
        }
        //各キューブの大きさを得る
        for (int isize2 = 0; isize2 < 64 ; isize2 ++){
            cubeSizeCheck[isize2]->GetSize (checkhwd[isize2] );
            cubeSizeCheck[isize2]->GetHole0(checkhole0[isize2]);
            cubeSizeCheck[isize2]->GetHole3(checkhole3[isize2]);
        }
        OverPitch_each = 0;
        //隣り合うやつの大きさを調べる
        //右と下の一行ずつは一旦無視する
        for (int ix = 0; ix < 7; ix ++){
            for(int iy = 0; iy < 7; iy ++){
                h_overPitch->Fill(
                    ((checkhole0[8*iy+ ix   ][0]+checkhole3[8*iy+ ix   ][0])/2 
                   + (checkhwd[  8*iy+(ix+1)][1] 
                   - (checkhole0[8*iy+(ix+1)][0]+checkhole3[8*iy+(ix+1)][0])/2)));

                h_overPitch->Fill(
                    ((checkhwd[  8* iy   +ix][2] 
                   - (checkhole0[8* iy   +ix][1]+checkhole3[8* iy   +ix][1])/2)
                   + (checkhole0[8*(iy+1)+ix][1]+checkhole3[8*(iy+1)+ix][1])/2)); 

                if (((checkhole0[8*iy+ ix   ][0]+checkhole3[8*iy+ ix   ][0])/2 
                   + (checkhwd[  8*iy+(ix+1)][1] 
                   - (checkhole0[8*iy+(ix+1)][0]+checkhole3[8*iy+(ix+1)][0])/2)) 
                     > pitch ||
                    ((checkhwd[  8* iy   +ix][2] 
                   - (checkhole0[8* iy   +ix][1]+checkhole3[8* iy   +ix][1])/2)
                   + (checkhole0[8*(iy+1)+ix][1]+checkhole3[8*(iy+1)+ix][1])/2) 
                     > pitch){
                    
//                        std::cout << 
//                            (checkhole0[8*iy+ ix   ][0]+checkhole3[8*iy+ ix   ][0])/2 <<
//                    " + " << checkhwd[  8*iy+(ix+1)][1] << 
//                    " - " <<(checkhole0[8*iy+(ix+1)][0]+checkhole3[8*iy+(ix+1)][0])/2 << " = " << std::endl;
//                        std::cout <<
//                            (checkhole0[8*iy+ ix   ][0]+checkhole3[8*iy+ ix   ][0])/2 
//                          + (checkhwd[  8*iy+(ix+1)][1] 
//                          - (checkhole0[8*iy+(ix+1)][0]+checkhole3[8*iy+(ix+1)][0])/2)
//                                  << std::endl; 
                        OverPitch ++;
                        OverPitch_each ++;
                }
            }
        }   
        //右の一行(ix = 7)
        for (int iy = 0; iy < 7; iy ++){
                h_overPitch->Fill(
                 (checkhwd[  8*iy     +7][2] 
               - (checkhole0[8*iy     +7][1]+ checkhole3[8*iy +    7][1])/2) 
               + (checkhole0[8*(iy+1) +7][1]+ checkhole3[8*(iy+1) +7][1])/2);

            if (((checkhwd[  8*iy     +7][2] 
               - (checkhole0[8*iy     +7][1]+ checkhole3[8*iy +    7][1])/2) 
               + (checkhole0[8*(iy+1) +7][1]+ checkhole3[8*(iy+1) +7][1])/2) > pitch){
                OverPitch ++;
                OverPitch_each ++;
            }
        }
        //下の一行(iy = 7)
        for (int ix = 0; ix <7; ix ++){
                h_overPitch->Fill(
                 (checkhole0[8*7+ ix   ][0]+checkhole3[8*7 + ix   ][0])/2 
               + (checkhwd[  8*7+(ix+1)][1] 
               - (checkhole0[8*7+(ix+1)][0]+checkhole3[8*7 +(ix+1)][0])/2));

            if (((checkhole0[8*7+ ix   ][0]+checkhole3[8*7 + ix   ][0])/2 
               + (checkhwd[  8*7+(ix+1)][1] 
               - (checkhole0[8*7+(ix+1)][0]+checkhole3[8*7 +(ix+1)][0])/2)) > pitch){

                OverPitch ++;
                OverPitch_each ++;
            }
        }
            


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
            //std::cout << "num_over : " << num_over << ", set number: " 
            //          << shuff << endl;
        }
//        TCanvas * can1 = new TCanvas("can1", "can1");
//        hdiffx->Draw();
//        TCanvas * can2 = new TCanvas("can2", "can2");
//        hdiffy->Draw();
    
    
        
         
           // hogehoge
    
    
    
    
    
        
        
        
            if (OverPitch_each > 0){
                OverPitch_set ++;
            }
            
   } 

//*/  
        TEllipse * e = new TEllipse(0,0,SDevX2*1, SDevY2*1);
        TCanvas * canvas1 = new TCanvas("canvas1", "canvas1");
        hdiffx->Draw();
        TCanvas * canvas2 = new TCanvas("canvas2", "canvas2");
        hdiffy->Draw();
        TCanvas * c_over  = new TCanvas("c_over", "c_over");
        h_over->Draw();
        TCanvas * c_center= new TCanvas("c_center", "c_center");
        hcenter2->Draw();
        TCanvas * c_centerXY= new TCanvas("c_centerXY", "c_centerXY");
        hcenterXY2->Draw();
        e->Draw("same");
        TCanvas* c_decide = new TCanvas("c_decide", "c_decide");
        h_decideTopd->Draw();
        TCanvas* c_decidemin = new TCanvas("c_decidemin", "c_decidemin");
        h_decideTopdmin->Draw();
//        TCanvas * c_centerXYXY= new TCanvas("c_centerXYXY", "c_centerXYXY");
//        hcenterXYXY2->Draw();
        TCanvas * c_pos   = new TCanvas("c_pos", "c_pos");
        hpos->Draw("colz text");
        TCanvas * c_overPitch = new TCanvas("c_overPitch", "c_overPitch");
        h_overPitch->Draw();
       // 残ったやつ取って並べて、
       // Getxxxxx の関数などを class 追加して、数値のばらつきを取ってきて計算したり。
     
       // hogehoge
       std::cout << "************************************************" << std::endl;
       std::cout << "simulated cube : "<< cubemax << std::endl;
       std::cout << "good cube      : "<< cube.size() << std::endl;
       std::cout << "good rate      : "<< (float) cube.size()*100/cubemax << "%" << std::endl;
       std::cout << "************************************************" << std::endl;
       std::cout << "tan      : " << tan    << std::endl; 
       std::cout << "cannot   : " << cannot << " /" << unitnum 
                 << ", " << (float) cannot*100/unitnum << "%" << std::endl;
       std::cout << "iInside : " << iInside << " /" << cube.size() 
                 << ", " << (float) iInside * 100 / cube.size() << "%" << std::endl;
       std::cout << "pitch : " << pitch  << std::endl; 

       std::cout << "OverPitch : " << OverPitch << " /(" << unitnum << "*(49+14))" 
                 << ", " << (float) OverPitch * 100 / (unitnum * (49+14)) << "%" << std::endl;
       std::cout << "OverPitch_set : " << OverPitch_set << " /" << unitnum  
                 << ", " << (float) OverPitch_set * 100 / unitnum  << "%" << std::endl;
       std::cout << "time : "<< (unsigned int) time(NULL) << std::endl; 
       std::cout << "************************************************" << std::endl;


    //テキストファイルに出力
    std::ofstream ratetxt("good_clear_ela.txt", std::ios::app);
//    ratetxt << Nall << " " << (float) cube.size() * 100/cubemax
//                    << " " << (float) andclear * 100/unitnum << std::endl;

    ratetxt.close();

    fout.close();
}

void analysis_hole_copy()
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

