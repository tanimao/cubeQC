
#include <iostream>



#include <fstream>
#include <math.h>
#include <cmath>

#include <vector>
#include "classCube_hole.cc"

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
    int cubemax = 100000;
    int unitnum = 10000;

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


    //向かい合う穴位置のズレを記録するヒストグラム
    TH1F * fdhxy = new TH1F ("fdhxy", "facing sqrt(delta(xh)^2+delta(yh)^2); dhxy[mm]",
                             100, 0, 1);


//    TH2F * hcenterXYXY1 = new  TH2F ("hcenterXYXY1", "hcenterXYXY1", 
//                                    100, -0.5, 0.5, 100, -0.5, 0.5);
//    TH2F * hcenterXYXY2 = new  TH2F ("hcenterXYXY2", "hcenterXYXY2", 
//                                    100, -0.5, 0.5, 100, -0.5, 0.5);

   // キューブのパラメータを決定しながら、キューブを定義する

	//Cube *c = new Cube(1,1,1,1,1); 
   //Cube *cube[12000];
    std::vector < Cube* > cube;
 
    //64通りの分類をつくってみる

    std::vector < std::vector <Cube*> > cubeCategory;
    cubeCategory.resize(64);


    


 
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

            sqrt (std::pow(hole0[0] - hole3[0],2) + std::pow(hole0[1] - hole3[1],2)) 
                 < 0.35 / 0.01554 &&
            sqrt (std::pow(hole1[0] - hole4[0],2) + std::pow(hole1[1] - hole4[1],2)) 
                 < 0.35 / 0.01554 &&
            sqrt (std::pow(hole2[0] - hole5[0],2) + std::pow(hole2[1] - hole5[1],2)) 
                 < 0.35 / 0.01554 &&

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

           //fdhxy->Fill(0.01554 * sqrt(std::pow(hole0[0]-hole3[0], 2)
           //                         + std::pow(hole0[1]-hole3[1], 2)));
           //fdhxy->Fill(0.01554 * sqrt(std::pow(hole1[0]-hole4[0], 2)
           //                         + std::pow(hole1[1]-hole4[1], 2)));
           //fdhxy->Fill(0.01554 * sqrt(std::pow(hole2[0]-hole5[0], 2)
           //                         + std::pow(hole2[1]-hole5[1], 2)));
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
    float posxhx[8][8][6] = {};
    float posxhy[8][8][6] = {};
    float posxhz[8][8][6] = {};
    float pitch = 10.40;
    //float tan = 0.4/102.4;
    float tan = 0/102.4;
    int cannotx = 0;
    int cannoty = 0;
    int cannot  = 0;

    int CatNum[64]= {};




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

    for(int icubepre = 0; icubepre < igood; icubepre ++){
        
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

    for(int icube = 0; icube < igood; icube++){
        //cube[icube]の穴位置(X,Y)を求めておく。
        float X1 = 0;
        float Y1 = 0;
        float X2 = 0;
        float Y2 = 0;
        //向かい合う面の穴位置のズレを調べる
        Fill_fdhxy(cube[icube], fdhxy);
        GetEllipse1(cube[icube], center1mean1, center1mean2, p1_tan, X1, Y1);
        GetEllipse2(cube[icube], center2mean1, center2mean2, p2_tan, X2, Y2);
        //ここで求めたX1,Y1,X2,Y2を以下の分類のところで有効活用する

       if (
           EllipseCut1(cube[icube], SDevX1*2.5, SDevY1*3, 
                      center1mean1, center1mean2, p1_tan) == 1 &&
           EllipseCut2(cube[icube], SDevX2*2.5, SDevY2*3,
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


        
        //14面について
        //垂直方向の穴の位置を基準にその他の穴位置を求めておく






            //8x8=64の分類に分ける
        double factor = 1.5;
        int icategory;
        CheckCategory(X1, Y1, X2, Y2, factor, SDevX1, SDevX2, &icategory);

        CatNum[icategory] ++;
        cubeCategory[icategory].push_back(cube[icube]);


        }
       
    }


    
    for (int icat = 0; icat <64; icat ++){
        std::cout << "Category " << icat  << ":" 
                  << CatNum[icat] << std::endl;
    }



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
    float checkhwd[8][8][3];
    float checkhole0[8][8][2];
    float checkhole3[8][8][2];
    int OverPitch     = 0;
    int OverPitch_each= 0;
    int OverPitch_set = 0;
    TH1F * h_overPitch = new TH1F ("h_overPitch", "h_overPitch", 100,10,11);


    Cube *cubeSizeCheck[8][8];

//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
    //キューブをシャッフルする。
    for (int shuff = 0; shuff <unitnum; shuff++){
        std::mt19937_64 get_rand_mt(shuff);
        //std::mt19937_64 get_rand_mt(0);
        std::shuffle(cube.begin(), cube.end(), get_rand_mt );
        
        //分類ごとにシャッフルする

        for (int icat = 0; icat < 64; icat ++){
            std::shuffle(cubeCategory[icat].begin(),
                         cubeCategory[icat].end(), get_rand_mt);
        }

        //隣り合うやつの大きさをみる
        //配列の初期化
        for (int iy = 0; iy < 8; iy ++){
            for (int ix = 0; ix < 8; ix ++){
                for (int j = 0; j < 3 ; j++){
                    checkhwd[ix][iy][j]  = 0.;
                    
                    if (j < 2){
                        checkhole0[ix][iy][j] = 0.;
                        checkhole3[ix][iy][j] = 0.;
                    }
                }
            }
        }
       
        for (int i = 0 ;i<8; i++ ){
            for (int j = 0; j<8; j++){
                cubeSizeCheck[i][j] = cubeCategory[ 8*i + j][0];
                //cubeSizeCheck[i][j] = cube[8*i + j];
            }
        }
/*
            cubeSizeCheck[0][0+i] = cubeAB[i];
            cubeSizeCheck[0][2+i] = cubeAC[i];
            cubeSizeCheck[0][4+i] = cubeAF[i];
            cubeSizeCheck[0][6+i] = cubeAG[i];

            cubeSizeCheck[1][0+i] = cubeBB[i];
            cubeSizeCheck[1][2+i] = cubeBC[i];
            cubeSizeCheck[1][4+i] = cubeBF[i];
            cubeSizeCheck[1][6+i] = cubeBG[i];

            cubeSizeCheck[2][0+i] = cubeCB[i];
            cubeSizeCheck[2][2+i] = cubeCC[i];
            cubeSizeCheck[2][4+i] = cubeCF[i];
            cubeSizeCheck[2][6+i] = cubeCG[i];

            cubeSizeCheck[3][0+i] = cubeDB[i];
            cubeSizeCheck[3][2+i] = cubeDC[i];
            cubeSizeCheck[3][4+i] = cubeDF[i];
            cubeSizeCheck[3][6+i] = cubeDG[i];

            cubeSizeCheck[4][0+i] = cubeEB[i];
            cubeSizeCheck[4][2+i] = cubeEC[i];
            cubeSizeCheck[4][4+i] = cubeEF[i];
            cubeSizeCheck[4][6+i] = cubeEG[i];

            cubeSizeCheck[5][0+i] = cubeFB[i];
            cubeSizeCheck[5][2+i] = cubeFC[i];
            cubeSizeCheck[5][4+i] = cubeFF[i];
            cubeSizeCheck[5][6+i] = cubeFG[i];

            cubeSizeCheck[6][0+i] = cubeGB[i];
            cubeSizeCheck[6][2+i] = cubeGC[i];
            cubeSizeCheck[6][4+i] = cubeGF[i];
            cubeSizeCheck[6][6+i] = cubeGG[i];

            cubeSizeCheck[7][0+i] = cubeHB[i];
            cubeSizeCheck[7][2+i] = cubeHC[i];
            cubeSizeCheck[7][4+i] = cubeHF[i];
            cubeSizeCheck[7][6+i] = cubeHG[i];
        }
*/
/*
        for (int y =0;y < 8; y++){

            for (int x =0;x < 4; x++){
                cubeSizeCheck[y][x] = cubeBC[8*y+x];
                cubeSizeCheck[y][x+4] = cubeBB[8*y+x];
            }
        }
        */
        //各キューブの大きさを得る
        for (int isize2y = 0; isize2y < 8 ; isize2y ++){
            for (int isize2x = 0; isize2x < 8 ; isize2x ++){

                cubeSizeCheck[isize2y][isize2x]->GetSize (checkhwd  [isize2y][isize2x] );
                cubeSizeCheck[isize2y][isize2x]->GetHole0(checkhole0[isize2y][isize2x]);
                cubeSizeCheck[isize2y][isize2x]->GetHole3(checkhole3[isize2y][isize2x]);
            }
        }
        OverPitch_each = 0;
        //隣り合うやつの大きさを調べる
        //右と下の一行ずつは一旦無視する
        for(int iy = 0; iy < 7; iy ++){
            for (int ix = 0; ix < 7; ix ++){
                h_overPitch->Fill(
                     (checkhole0[iy][ix]  [0]+checkhole3[iy][ix]  [0])/2 
                   + (checkhwd  [iy][ix+1][1]               
                   - (checkhole0[iy][ix+1][0]+checkhole3[iy][ix+1][0])/2));

                h_overPitch->Fill(
                     (checkhwd  [iy]  [ix][2] 
                   - (checkhole0[iy]  [ix][1]+checkhole3[iy]  [ix][1])/2)
                   + (checkhole0[iy+1][ix][1]+checkhole3[iy+1][ix][1])/2 ); 

                if ( (checkhole0[iy][ix]  [0]+checkhole3[iy][ix]  [0])/2 
                   + (checkhwd  [iy][ix+1][1]               
                   - (checkhole0[iy][ix+1][0]+checkhole3[iy][ix+1][0])/2) 
                     > pitch ||
                     (checkhwd  [iy]  [ix][2] 
                   - (checkhole0[iy]  [ix][1]+checkhole3[iy]  [ix][1])/2)
                   + (checkhole0[iy+1][ix][1]+checkhole3[iy+1][ix][1])/2 
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
                 (checkhwd  [iy]  [7][2] 
               - (checkhole0[iy]  [7][1]+ checkhole3[iy]  [7][1])/2) 
               + (checkhole0[iy+1][7][1]+ checkhole3[iy+1][7][1])/2);
                                                             
            if ( (checkhwd  [iy]  [7][2]                     
               - (checkhole0[iy]  [7][1]+ checkhole3[iy]  [7][1])/2) 
               + (checkhole0[iy+1][7][1]+ checkhole3[iy+1][7][1])/2 > pitch){

                OverPitch ++;
                OverPitch_each ++;
            }
        }
        //下の一行(iy = 7)
        for (int ix = 0; ix <7; ix ++){
            h_overPitch->Fill(
                 (checkhole0[7][ix][0]+checkhole3[7][ix]  [0])/2 
               + (checkhwd  [7][ix][1]              
               - (checkhole0[7][ix][0]+checkhole3[7][ix+1][0])/2));
                                                    
            if ( (checkhole0[7][ix][0]+checkhole3[7][ix]  [0])/2 
               + (checkhwd  [7][ix][1]              
               - (checkhole0[7][ix][0]+checkhole3[7][ix+1][0])/2) > pitch){

                OverPitch ++;
                OverPitch_each ++;
            }
        }
            


        for (int iarry = 0; iarry < 8; iarry ++){
            for (int iarrx = 0; iarrx < 8; iarrx ++){
    
                
                ArrangebyHole(cubeSizeCheck[iarry][iarrx], 
                          pitch*(iarrx+1), pitch*(iarry+1), 
                          posxhx[iarry][iarrx], 
                          posxhy[iarry][iarrx],
                          posxhz[iarry][iarrx]);






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
    //    TH2F * nexthole = new TH2F ("nexthole", 
    //          "points where next hole is", 50, -1, 1 , 50, -1, 1); 
    
        num_over = 0;
        cannotx = 0;
        cannoty = 0;
        //if (shuff==4883){
        //TH1F * hdiffown = new TH1F ("hdiffown", 
        //      "differential of each side of hole ",50, -1, 1);
        FillDiffy( hdiffx, hdiffxSingle, num_over, hpos, 
                   posxhx, posxhy, posxhz, cannoty, pitch,shuff);
        FillDiffx( hdiffy, hdiffySingle, num_over, hpos, 
                   posxhx, posxhy, posxhz, cannotx, pitch);
        //checkdiff( hdiffown, posxhx, posxhy, posxhz, cannotx);
        //hdiffown->Draw();
        //}

        
    //    std::cout << "num_over : " << num_over << std::endl;
    
        //if (hdiffxSingle->Integral(25,50) > 0 || 
        //    hdiffySingle->Integral(25,50) > 0)
        if (hdiffxSingle->Integral(hdiffxSingle->GetXaxis()->FindBin(0.5),
                                   hdiffxSingle->GetXaxis()->FindBin(1.)) > 0 || 
            hdiffySingle->Integral(hdiffySingle->GetXaxis()->FindBin(0.5),
                                   hdiffySingle->GetXaxis()->FindBin(1.)) > 0){
    
            //std::cout << "unit num : " << shuff <<  std::endl; 
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
        /*
        TCanvas * can1 = new TCanvas("can1", "can1");
        hdiffx->Draw();
        TCanvas * can2 = new TCanvas("can2", "can2");
        hdiffy->Draw();
        */
    
    
        
         
           // hogehoge
        ///**************************************************************
    
    
    
    
    
        
        
        
            if (OverPitch_each > 0){
                OverPitch_set ++;
            }
            
   } 
    /*
        TEllipse * e = new TEllipse(0,0,SDevX2*1, SDevY2*1);
        TCanvas * canvas1 = new TCanvas("canvas1", "canvas1");
        hdiffx->Draw();
        TCanvas * canvas2 = new TCanvas("canvas2", "canvas2");
        hdiffy->Draw();
        TCanvas * c_over  = new TCanvas("c_over", "c_over");
        h_over->Draw();
        TCanvas * c_center= new TCanvas("c_center", "c_center");
        hcenter2->Draw();
        TCanvas * c_centerXY1= new TCanvas("c_centerXY1", "c_centerXY1");
        hcenterXY1->Draw();
        TCanvas * c_centerXY2= new TCanvas("c_centerXY2", "c_centerXY2");
        hcenterXY2->Draw();
        e->Draw("same");
        TCanvas* c_decide = new TCanvas("c_decide", "c_decide");
        h_decideTopd->Draw();
        TCanvas* c_decidemin = new TCanvas("c_decidemin", "c_decidemin");
        h_decideTopdmin->Draw();
        */
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

