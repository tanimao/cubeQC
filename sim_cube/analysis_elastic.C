#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>

#include <vector>
//#include "classCube_matsu_sukima.cc"
#include "classCube_elastic.cc"

#include <stdlib.h>
#include <time.h>

#include <random>
#include <algorithm>

// root -l analysis.C




void analysis_elastic()
{

//    gRandom->SetSeed(2);
    gRandom->SetSeed((unsigned int ) time(NULL));
//    srand(1);
//    srand((unsigned int) time(NULL));
//    //std::cout << "time : "<< (unsigned int) time(NULL) << std::endl; 
    // TH1F でパラメたの測定分布を読み込む
    TFile * fr = new TFile("201007hist.root", "read");//半径だけはここから持ってくる
    TH1D  * h1  = (TH1D*)fr->Get("h1");  //radius
    TFile * fin = new TFile("hist_correlation1007.root", "read");//半径だけはここから持ってくる
    TH3D * sizexyz = (TH3D*)fin->Get("sizexyz");
    TH2D * hole1   = (TH2D*)fin->Get("hole1");
    TH2D * hole2   = (TH2D*)fin->Get("hole2");
    TH2D * hole3   = (TH2D*)fin->Get("hole3");
    TH2D * hole4   = (TH2D*)fin->Get("hole4");
    TH2D * hole5   = (TH2D*)fin->Get("hole5");
    TH2D * hole6   = (TH2D*)fin->Get("hole6");
    TH2D * hole7   = (TH2D*)fin->Get("hole7");
    TH2D * hole8   = (TH2D*)fin->Get("hole8");
 
    // 読み込んだ分布より、GetRndom で値を取ってきて、
   // float sizehwd[3];
   // float hole14[2];
   // float hole25[2];
   // float hole36[2];
    
    Double_t sizehwd[3];
    Double_t hole14[2];
    Double_t hole25[2];
    Double_t hole36[2];
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
        //サイズごとに、参照するヒストグラムを変えることで、相関を表現
        if (sizehwd[0] < _sMean){
            if (sizehwd[1] < _sMean){
                if (sizehwd[2] < _sMean){
                    hole1->GetRandom2(hole14[0], hole14[1]);
                    hole1->GetRandom2(hole25[0], hole25[1]);
                    hole1->GetRandom2(hole36[0], hole36[1]);
                }else{
                    hole4->GetRandom2(hole14[0], hole14[1]);
                    hole4->GetRandom2(hole25[0], hole25[1]);
                    hole4->GetRandom2(hole36[0], hole36[1]);
                }
            }else{
                if (sizehwd[2] < _sMean){
                    hole3->GetRandom2(hole14[0], hole14[1]);
                    hole3->GetRandom2(hole25[0], hole25[1]);
                    hole3->GetRandom2(hole36[0], hole36[1]);
                }else{
                    hole7->GetRandom2(hole14[0], hole14[1]);
                    hole7->GetRandom2(hole25[0], hole25[1]);
                    hole7->GetRandom2(hole36[0], hole36[1]);
                }
            }
        }else{
            if (sizehwd[1] < _sMean){
                if (sizehwd[2] < _sMean){
                    hole2->GetRandom2(hole14[0], hole14[1]);
                    hole2->GetRandom2(hole25[0], hole25[1]);
                    hole2->GetRandom2(hole36[0], hole36[1]);
                }else{
                    hole6->GetRandom2(hole14[0], hole14[1]);
                    hole6->GetRandom2(hole25[0], hole25[1]);
                    hole6->GetRandom2(hole36[0], hole36[1]);
                }
            }else{
                if (sizehwd[2] < _sMean){
                    hole5->GetRandom2(hole14[0], hole14[1]);
                    hole5->GetRandom2(hole25[0], hole25[1]);
                    hole5->GetRandom2(hole36[0], hole36[1]);
                }else{
                    hole8->GetRandom2(hole14[0], hole14[1]);
                    hole8->GetRandom2(hole25[0], hole25[1]);
                    hole8->GetRandom2(hole36[0], hole36[1]);
                }
            }
        }

       //rは以前のままにしておく 
        for (int isu = 0; isu<6; isu++){
            r[isu]  = h1->GetRandom();

                    
        }
        if (
         //10/13 現行の条件(以下)
           8+ 652+0.8-1 < sizehwd[0] && sizehwd[0] < 664+0.8-0.5 && 
           8+ 652+0.8-1 < sizehwd[1] && sizehwd[1] < 664+0.8-0.5 && 
           8+ 652+0.8-1 < sizehwd[2] && sizehwd[2] < 664+0.8-0.5 && 

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

            1==1

            ){        
            igood += 1; 
            cube.push_back( new Cube(igood,
            //ピクセル数をミリメートルに変換
                   0.01554*sizehwd[0], 0.01554*sizehwd[1], 0.01554*sizehwd[2], 
                   0.01554*hole14[0], 0.01554*hole14[1],  
                   0.01554*hole25[0], 0.01554*hole25[1],  
                   0.01554*hole36[0], 0.01554*hole36[1],  
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
        CubeArrangey1(cube[0], cube[1], cube[2], cube[3],
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
        
        //std::cout << "sizemaxx : "<< sizemaxx[0] << "\n" << std::endl;
    
    
        //std::cout << "********************************************" << std::endl;
        //std::cout << "sizemax::  y: "<< sizemax[0] << ", x: "<< sizemaxx[0] << std::endl;
        //fout << sizemax[0] << "  " << sizemaxx[0] << std::endl;
        //std::cout << "********************************************" << std::endl;
        float widthrange = 82.3;
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
    
    fout.close();
}



