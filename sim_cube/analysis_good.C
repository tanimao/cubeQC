#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>

#include <vector>
//#include "classCube_matsu.cc"
#include "classCube_matsu_sukima.cc"
//#include "classCube.cc"

#include <stdlib.h>
#include <time.h>

#include <random>
#include <algorithm>

// root -l analysis.C




void analysis_good()
{

//    gRandom->SetSeed(2);
    gRandom->SetSeed((unsigned int ) time(NULL));
//    srand(1);
//    srand((unsigned int) time(NULL));
//    std::cout << "time : "<< (unsigned int) time(NULL) << std::endl; 
    // TH1F でパラメたの測定分布を読み込む
    TFile * fin = new TFile("0829goodsizecor0910hist.root", "read");
    TH1D  * h1  = (TH1D*)fin->Get("h1");  //radius
    TH1D  * h2  = (TH1D*)fin->Get("h2");  //xhole
    TH1D  * h3  = (TH1D*)fin->Get("h3");  //yhole
    TH1D  * h4  = (TH1D*)fin->Get("h4");  //xsize
    TH1D  * h5  = (TH1D*)fin->Get("h5");  //ysize
    TH1D  * hb  = (TH1D*)fin->Get("hb");  //bump
    TH1D  * hE  = (TH1D*)fin->Get("hE");  //Esum
    //  hogehoge
 
    // 読み込んだ分布より、GetRndom で値を取ってきて、
    float xs[6];
    float ys[6];
    float xh[6];
    float yh[6];
    float r[6];
    
    float parlist[5];
    
    int igood = 0;
    int cubemax = 10000;
    int unitnum = 5000;
   // キューブのパラメータを決定しながら、キューブを定義する

	//Cube *c = new Cube(1,1,1,1,1); 
   //Cube *cube[12000];
    std::vector < Cube* > cube;
 
    for (int icu = 0; icu<cubemax; icu++) {
        for (int isu = 0; isu<6; isu++){
            xs[isu] = h4->GetRandom();
            ys[isu] = h5->GetRandom();
            xh[isu] = h2->GetRandom();
            yh[isu] = h3->GetRandom();
            r[isu]  = h1->GetRandom();
        }
        if (
            /*
            650 < xs[0] && xs[0] < 669 && 
            650 < xs[1] && xs[1] < 669 && 
            650 < xs[2] && xs[2] < 669 && 
            650 < xs[3] && xs[3] < 669 && 
            650 < xs[4] && xs[4] < 669 && 
            650 < xs[5] && xs[5] < 669 && 

            650 < ys[0] && ys[0] < 669 && 
            650 < ys[1] && ys[1] < 669 && 
            650 < ys[2] && ys[2] < 669 && 
            650 < ys[3] && ys[3] < 669 && 
            650 < ys[4] && ys[4] < 669 && 
            650 < ys[5] && ys[5] < 669 && 

            165 < xh[0] && xh[0] < 200 && 
            165 < xh[1] && xh[1] < 200 && 
            165 < xh[2] && xh[2] < 200 && 
            165 < xh[3] && xh[3] < 200 && 
            165 < xh[4] && xh[4] < 200 && 
            165 < xh[5] && xh[5] < 200 && 

            165 < yh[0] && yh[0] < 200 && 
            165 < yh[1] && yh[1] < 200 && 
            165 < yh[2] && yh[2] < 200 && 
            165 < yh[3] && yh[3] < 200 && 
            165 < yh[4] && yh[4] < 200 && 
            165 < yh[5] && yh[5] < 200 && 

            47.5  < r[0]  && r[0] < 51.5 && 
            47.5  < r[1]  && r[1] < 51.5 && 
            47.5  < r[2]  && r[2] < 51.5 && 
            47.5  < r[3]  && r[3] < 51.5 && 
            47.5  < r[4]  && r[4] < 51.5 && 
            47.5  < r[5]  && r[5] < 51.5 &&

            650 < xs[0] && xs[0] < 665 && 
            650 < xs[1] && xs[1] < 665 && 
            650 < xs[2] && xs[2] < 665 && 
            650 < xs[3] && xs[3] < 665 && 
            650 < xs[4] && xs[4] < 665 && 
            650 < xs[5] && xs[5] < 665 && 

            650 < ys[0] && ys[0] < 665 && 
            650 < ys[1] && ys[1] < 665 && 
            650 < ys[2] && ys[2] < 665 && 
            650 < ys[3] && ys[3] < 665 && 
            650 < ys[4] && ys[4] < 665 && 
            650 < ys[5] && ys[5] < 665 && 

            170 < xh[0] && xh[0] < 200 && 
            170 < xh[1] && xh[1] < 200 && 
            170 < xh[2] && xh[2] < 200 && 
            170 < xh[3] && xh[3] < 200 && 
            170 < xh[4] && xh[4] < 200 && 
            170 < xh[5] && xh[5] < 200 && 

            170 < yh[0] && yh[0] < 200 && 
            170 < yh[1] && yh[1] < 200 && 
            170 < yh[2] && yh[2] < 200 && 
            170 < yh[3] && yh[3] < 200 && 
            170 < yh[4] && yh[4] < 200 && 
            170 < yh[5] && yh[5] < 200 && 
            */

            48  < r[0]  && 
            48  < r[1]  && 
            48  < r[2]  && 
            48  < r[3]  && 
            48  < r[4]  && 
            48  < r[5]  && 
            1==1
            ){        
            igood += 1; 
            cube.push_back( new Cube(igood,
            //ピクセル数をミリメートルに変換
                   0.01554*xs[0],0.01554*ys[0],0.01554*xh[0],0.01554*yh[0], 0.01554*r[0],
                   0.01554*xs[1],0.01554*ys[1],0.01554*xh[1],0.01554*yh[1], 0.01554*r[1],
                   0.01554*xs[2],0.01554*ys[2],0.01554*xh[2],0.01554*yh[2], 0.01554*r[2],
                   0.01554*xs[3],0.01554*ys[3],0.01554*xh[3],0.01554*yh[3], 0.01554*r[3],
                   0.01554*xs[4],0.01554*ys[4],0.01554*xh[4],0.01554*yh[4], 0.01554*r[4],
                   0.01554*xs[5],0.01554*ys[5],0.01554*xh[5],0.01554*yh[5], 0.01554*r[5])); 
        //  id と parameter :  必要な parameter は自分で定義する
            cube[igood-1]->GetInfoSurf1();
            cube[igood-1]->GetSurf1(parlist);
            std::cout << "parlist : "<< parlist[0] << ", " << parlist[1] << ", " << parlist[2] 
                      << ", " << parlist[3] << ", " << parlist[4]<< std::endl;
        }
//        if (parlist[0]<680){
//            cube.pop_back();
//        }
        std::cout << "simulated cube : "<< icu+1 << std::endl;
        std::cout << "good cube      : "<< cube.size() << std::endl;
        std::cout << "************************************************" << std::endl;
        std::cout << "************************************************" << std::endl;
    }    





   // selection cut かける
    
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
    
        std::cout << "===array 1:===" << std::endl;
        CubeArrange1(cube[0], cube[1], cube[2], cube[3],
                     cube[4], cube[5], cube[6], cube[7],
                     hole, fibarea, sizemax);
    //    std::cout << hole[0] <<" "<< fibarea[0]<<" " << sizemax[0] << std::endl;
        //sizediff = 82.1 - sizemax[0];
        //std::cout << "sizediff : "<< sizediff << std::endl;
    
    
    
    
    
        std::cout << "===array 2:===" << std::endl;
        CubeArrange2(cube[8],  cube[9],  cube[10], cube[11],
                     cube[12], cube[13], cube[14], cube[15],
                     hole, fibarea, sizemax);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemax[0] >= sizemax[1]){
        }
        else{
        sizemax[0] = sizemax[1];
        }
        
        std::cout << "sizemax : "<< sizemax[0] << "\n" << std::endl;
    
    
    
    
    
        std::cout << "===array 3:===" << std::endl;
        CubeArrange2(cube[16], cube[17], cube[18], cube[19],
                     cube[20], cube[21], cube[22], cube[23],
                     hole, fibarea, sizemax);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemax[0] >= sizemax[1]){
        }
        else{
        sizemax[0] = sizemax[1];
        }
        
        std::cout << "sizemax : "<< sizemax[0] << "\n" << std::endl;
    
    
    
    
    
        std::cout << "===array 4:===" << std::endl;
        CubeArrange2(cube[24], cube[25], cube[26], cube[27],
                     cube[28], cube[29], cube[30], cube[31],
                     hole, fibarea, sizemax);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemax[0] >= sizemax[1]){
        }
        else{
        sizemax[0] = sizemax[1];
        }
        
        std::cout << "sizemax : "<< sizemax[0] << "\n" << std::endl;
    
    
        std::cout << "===array 5:===" << std::endl;
        CubeArrange2(cube[32], cube[33], cube[34], cube[35],
                     cube[36], cube[37], cube[38], cube[39],
                     hole, fibarea, sizemax);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemax[0] >= sizemax[1]){
        }
        else{
        sizemax[0] = sizemax[1];
        }
        
        std::cout << "sizemax : "<< sizemax[0] << "\n" << std::endl;
    
    
        std::cout << "===array 6:===" << std::endl;
        CubeArrange2(cube[40], cube[41], cube[42], cube[43],
                     cube[44], cube[45], cube[46], cube[47],
                     hole, fibarea, sizemax);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemax[0] >= sizemax[1]){
        }
        else{
        sizemax[0] = sizemax[1];
        }
        
        std::cout << "sizemax : "<< sizemax[0] << "\n" << std::endl;
    
    
        std::cout << "===array 7:===" << std::endl;
        CubeArrange2(cube[48], cube[49], cube[50], cube[51],
                     cube[52], cube[53], cube[54], cube[55],
                     hole, fibarea, sizemax);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemax[0] >= sizemax[1]){
        }
        else{
        sizemax[0] = sizemax[1];
        }
        
        std::cout << "sizemax : "<< sizemax[0] << "\n" << std::endl;
    
    
        std::cout << "===array 8:===" << std::endl;
        CubeArrange2(cube[56], cube[57], cube[58], cube[59],
                     cube[60], cube[61], cube[62], cube[63],
                     hole, fibarea, sizemax);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemax[0] >= sizemax[1]){
        }
        else{
        sizemax[0] = sizemax[1];
        }
        
        std::cout << "sizemax : "<< sizemax[0] << "\n" << std::endl;
    
    
    
    
    
    
        /////////////////////////////////////////////////////////////////////////////////
        ///横方向にも同様に並べる。
        float holex[8]    = {0,0,0,0,0,0,0,0};
        float fibareax[8] = {0,0,0,0,0,0,0,0};
        float sizemaxx[2] =  {0,0};
        float sizediffx = 0;
    
        std::cout << "===array 1:===" << std::endl;
        CubeArrangex1(cube[0],  cube[8],  cube[16], cube[24],
                     cube[32], cube[40], cube[48], cube[56],
                     holex, fibareax, sizemaxx);
    
    
        std::cout << "===array 2:===" << std::endl;
        CubeArrangex2(cube[1],  cube[9],  cube[17], cube[25],
                     cube[33], cube[41], cube[49], cube[57],
                     holex, fibareax, sizemaxx);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemaxx[0] >= sizemaxx[1]){
        }
        else{
        sizemaxx[0] = sizemaxx[1];
        }
        
        std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
    
    
        std::cout << "===array 3:===" << std::endl;
        CubeArrangex2(cube[2],  cube[10],  cube[18], cube[26],
                     cube[34], cube[42], cube[50], cube[58],
                     holex, fibareax, sizemaxx);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemaxx[0] >= sizemaxx[1]){
        }
        else{
        sizemaxx[0] = sizemaxx[1];
        }
        
        std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
    
    
        std::cout << "===array 4:===" << std::endl;
        CubeArrangex2(cube[3],  cube[11],  cube[19], cube[27],
                     cube[35], cube[43], cube[51], cube[59],
                     holex, fibareax, sizemaxx);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemaxx[0] >= sizemaxx[1]){
        }
        else{
        sizemaxx[0] = sizemaxx[1];
        }
        
        std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
    
        std::cout << "===array 5:===" << std::endl;
        CubeArrangex2(cube[4],  cube[12],  cube[20], cube[28],
                     cube[36], cube[44], cube[52], cube[60],
                     holex, fibareax, sizemaxx);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemaxx[0] >= sizemaxx[1]){
        }
        else{
        sizemaxx[0] = sizemaxx[1];
        }
        
        std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
    
        std::cout << "===array 6:===" << std::endl;
        CubeArrangex2(cube[5],  cube[13],  cube[21], cube[29],
                     cube[37], cube[45], cube[53], cube[61],
                     holex, fibareax, sizemaxx);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemaxx[0] >= sizemaxx[1]){
        }
        else{
        sizemaxx[0] = sizemaxx[1];
        }
        
        std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
        std::cout << "===array 7:===" << std::endl;
        CubeArrangex2(cube[6],  cube[14],  cube[22], cube[30],
                     cube[38], cube[46], cube[54], cube[62],
                     holex, fibareax, sizemaxx);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemaxx[0] >= sizemaxx[1]){
        }
        else{
        sizemaxx[0] = sizemaxx[1];
        }
        
        std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
        std::cout << "===array 8:===" << std::endl;
        CubeArrangex2(cube[7],  cube[15],  cube[23], cube[31],
                     cube[39], cube[47], cube[55], cube[63],
                     holex, fibareax, sizemaxx);
    
        ///sizemax[0]とsizemax[1]を比較して、大きい方をそれまでの代表とし、sizemax[0]に入れる。
        if (sizemaxx[0] >= sizemaxx[1]){
        }
        else{
        sizemaxx[0] = sizemaxx[1];
        }
        
        std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
        std::cout << "********************************************" << std::endl;
        std::cout << "sizemax::  y: "<< sizemax[0] << ", x: "<< sizemaxx[0] << std::endl;
        fout << sizemax[0] << "  " << sizemaxx[0] << std::endl;
        std::cout << "********************************************" << std::endl;
        if (sizemax[0]==100 || sizemaxx[0]==100){
            miss += 1;
        }
        else{
            if (sizemax[0] < 82.3){
                yclear += 1;
            }
            if (sizemaxx[0] < 82.3){
                xclear += 1;
            }
            if (sizemax[0] < 82.3 && sizemaxx[0] <82.3){
                andclear +=1;
            }
            if (sizemax[0] >=82.2 || sizemaxx[0] >=82.2){
                OutOfRange +=1;
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
       std::cout << "OutOfRange : " <<OutOfRange<< " /" << unitnum<<", "<<(float) OutOfRange*100/unitnum<< "%" << std::endl;
       std::cout << "yclear : " << yclear   << " /" << unitnum << ", " << (float) yclear*100/unitnum   << "%" << std::endl;
       std::cout << "xclear : " << xclear   << " /" << unitnum << ", " << (float) xclear*100/unitnum   << "%" << std::endl;
       std::cout << "both   : " << andclear << " /" << unitnum << ", " << (float) andclear*100/unitnum << "%" << std::endl;
   std::cout << "time : "<< (unsigned int) time(NULL) << std::endl; 
    
    fout.close();
}



