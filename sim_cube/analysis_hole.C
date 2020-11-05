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
    int unitnum = 5000;
   // キューブのパラメータを決定しながら、キューブを定義する

	//Cube *c = new Cube(1,1,1,1,1); 
   //Cube *cube[12000];
    std::vector < Cube* > cube;
 
    double _sMean = 659.2; //if文での参照用。macro_forrangeif.cppよりとってきた

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
        //  id と parameter :  必要な parameter は自分で定義する
        //    cube[igood-1]->GetSurf1(parlist);
        }
//        if (parlist[0]<680){
//            cube.pop_back();
//        }
       // //std::cout << "simulated cube : "<< icu+1 << std::endl;
       // //std::cout << "good cube      : "<< cube.size() << std::endl;
       // //std::cout << "************************************************" << std::endl;
       // //std::cout << "************************************************" << std::endl;
    }    





   // selection cut かける
   //キューブを64個穴基準で並べる 
    float posxhx[8][8][6] = {0.};
    float posxhy[8][8][6] = {0.};
    float posxhz[8][8][6] = {0.};
    float pitch = 10.3;

    for (int iarry = 0; iarry < 8; iarry ++){
        for (int iarrx = 0; iarrx < 8; iarrx ++){

            ArrayHole(  cube[8*iarry + iarrx], pitch*(iarrx+1), pitch*(iarry+1), 
                      posxhx[iarry][iarrx], 
                      posxhy[iarry][iarrx],
                      posxhz[iarry][iarrx]);
                        
            for (int i6 = 0; i6 <6 ; i6++){
                cout << posxhx[iarry][iarrx][i6] << endl;
                cout << posxhy[iarry][iarrx][i6] << endl;
            }

        }
    }
    
    TH1F * hdiffx = new TH1F ("hdiffx", "differential of two hole centers",100, 0, 1);
    TH1F * hdiffy = new TH1F ("hdiffy", "differential of two hole centers",100, 0, 1);

    FillDiffy( hdiffx, posxhx, posxhy, posxhz);
    FillDiffx( hdiffy, posxhx, posxhy, posxhz);

    /*
    TCanvas * can1 = new TCanvas("can1", "can1");
    hdiffx->Draw();
    TCanvas * can2 = new TCanvas("can2", "can2");
    hdiffy->Draw();
    */

    //キューブをシャッフルする。
    int miss   = 0;
    int OutOfRange = 0;
    int yclear = 0;
    int xclear = 0;    
    int andclear = 0;

    std::ofstream fout("sizemax.txt" );
    for (int shuff = 0; shuff <unitnum; shuff++){
        std::mt19937_64 get_rand_mt(shuff);
        std::shuffle(cube.begin(), cube.end(), get_rand_mt );
    
     
       // hogehoge
    ///***********************************************************************






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
    
       // 残ったやつ取って並べて、
       // Getxxxxx の関数などを class 追加して、数値のばらつきを取ってきて計算したり。
     
       // hogehoge
       std::cout << "************************************************" << std::endl;
       std::cout << "simulated cube : "<< cubemax << std::endl;
       std::cout << "good cube      : "<< cube.size() << std::endl;
       std::cout << "good rate      : "<< (float) cube.size()*100/cubemax << "%" << std::endl;
       std::cout << "************************************************" << std::endl;
       std::cout << "miss : "   << miss     << " /" << unitnum << ", " << (float) miss*100/unitnum     << "%" << std::endl;
       std::cout << "OutOfRange : "<<OutOfRange<< " /" <<unitnum<< ", "<< (float) OutOfRange*100/unitnum<< "%" << std::endl;
       std::cout << "yclear : " << yclear   << " /" << unitnum << ", " << (float) yclear*100/unitnum   << "%" << std::endl;
       std::cout << "xclear : " << xclear   << " /" << unitnum << ", " << (float) xclear*100/unitnum   << "%" << std::endl;
       std::cout << "both   : " << andclear << " /" << unitnum << ", " << (float) andclear*100/unitnum << "%" << std::endl;
   std::cout << "time : "<< (unsigned int) time(NULL) << std::endl; 


    //テキストファイルに出力
    std::ofstream ratetxt("good_clear_ela.txt", std::ios::app);
    ratetxt << Nall << " " << (float) cube.size() * 100/cubemax
                    << " " << (float) andclear * 100/unitnum << std::endl;

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
                    hmax = 1;// ihmax ;
                    hmin = 1;// 2*ihmin ;
                    smax = 1;// ismax ;
                    smin = 1;// ismin ;
                    analysis_hole1(fr, fin, fh, Nall, hmax, hmin, smax, smin);
//                }
//            }
//        }
//    }
}

