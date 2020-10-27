/*
互いに面する穴同士の共通部分が1ミリ以上あることを要求する関数を書く。

*/
#include "classCube_elastic.h"
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
ClassImp(Cube)

Cube::Cube()
{
}

Cube::Cube(int id,
           float height, float width, float depth,
           float xhole14, float yhole14,
           float xhole25, float yhole25,
           float xhole36, float yhole36,
           float r1, float r2, float r3, float r4, float r5, float r6
          )
        : _id(0),
          _height(0.), _width(0.), _depth(0.),
          _xhole14(0.), _yhole14(0.),
          _xhole25(0.), _yhole25(0.),
          _xhole36(0.), _yhole36(0.),
          _r1(0.), _r2(0.), _r3(0.), _r4(0.), _r5(0.), _r6(0.)

{

   _id = id;
   _height = height;
   _width = width;
   _depth = depth;
   
   _xhole14 = xhole14;
   _yhole14 = yhole14;
   _xhole25 = xhole25;
   _yhole25 = yhole25;
   _xhole36 = xhole36;
   _yhole36 = yhole36;

   _r1 = r1;
   _r2 = r2;
   _r3 = r3;
   _r4 = r4;
   _r5 = r5;
   _r6 = r6;





   //std::cerr << "constructor Cube id = " << _id << std::endl;
   //std::cerr << "set surf1 parameter xsize = " << _surf1_xs << std::endl;
   //std::cerr << "set surf1 parameter ysize = " << _surf1_ys << std::endl;
}

void Cube::GetSize(float size3D[3])
{
    size3D[0] = _height;
    size3D[1] = _width;
    size3D[2] = _depth;
}

void Cube::GetHole14(float holexy[2])
{
    holexy[0] = _xhole14;
    holexy[1] = _yhole14;
}

void Cube::GetHole25(float holexy[2])
{
    holexy[0] = _xhole25;
    holexy[1] = _yhole25;
}

void Cube::GetHole36(float holexy[2])
{
    holexy[0] = _xhole36;
    holexy[1] = _yhole36;
}

void Cube::GetRadius(float radius[6])
{
    radius[0] = _r1;
    radius[1] = _r2;
    radius[2] = _r3;
    radius[3] = _r4;
    radius[4] = _r5;
    radius[5] = _r6;
}

void CubeArrangey1(Cube *c1, Cube *c2, Cube *c3, Cube *c4,
                  Cube *c5, Cube *c6, Cube *c7, Cube *c8, 
                  float * hole, float * fibarea,
                  float * sizemax)
{

    //キューブのパラメータを格納する変数
    float hwd[8][3], hole25[8][2], rad[8][6];
    c1->GetSize(hwd[0]);
    c1->GetHole25(hole25[0]);
    c1->GetRadius(rad[0]);
    c2->GetSize(hwd[1]);
    c2->GetHole25(hole25[1]);
    c2->GetRadius(rad[1]);
    c3->GetSize(hwd[2]);
    c3->GetHole25(hole25[2]);
    c3->GetRadius(rad[2]);
    c4->GetSize(hwd[3]);
    c4->GetHole25(hole25[3]);
    c4->GetRadius(rad[3]);
    c5->GetSize(hwd[4]);
    c5->GetHole25(hole25[4]);
    c5->GetRadius(rad[4]);
    c6->GetSize(hwd[5]);
    c6->GetHole25(hole25[5]);
    c6->GetRadius(rad[5]);
    c7->GetSize(hwd[6]);
    c7->GetHole25(hole25[6]);
    c7->GetRadius(rad[6]);
    c8->GetSize(hwd[7]);
    c8->GetHole25(hole25[7]);
    c8->GetRadius(rad[7]);


    float cubelength = hwd[0][2]+hwd[1][2]+hwd[2][2]+hwd[3][2]
                      +hwd[4][2]+hwd[5][2]+hwd[6][2]+hwd[7][2];
    float delta      = 82.3 - cubelength;
    float idelta[8];
    float gap[9];
    if (delta<=0){


        //hwd[][2]はdepthのこと
        hole[0] = hole25[0][0];
        hole[1] = hole25[1][0] + hwd[0][2];
        hole[2] = hole25[2][0] + hwd[0][2]+hwd[1][2];
        hole[3] = hole25[3][0] + hwd[0][2]+hwd[1][2]+hwd[2][2];
        hole[4] = hole25[4][0] + hwd[0][2]+hwd[1][2]+hwd[2][2]+hwd[3][2];
        hole[5] = hole25[5][0] + hwd[0][2]+hwd[1][2]+hwd[2][2]+hwd[3][2]+hwd[4][2];
        hole[6] = hole25[6][0] + hwd[0][2]+hwd[1][2]+hwd[2][2]+hwd[3][2]+hwd[4][2]+hwd[5][2];
        hole[7] = hole25[7][0] + hwd[0][2]+hwd[1][2]+hwd[2][2]+hwd[3][2]
                                +hwd[4][2]+hwd[5][2]+hwd[6][2];
    
        
        fibarea[0] = 2*rad[0][1];
        fibarea[1] = 2*rad[1][1];
        fibarea[2] = 2*rad[2][1];
        fibarea[3] = 2*rad[3][1];
        fibarea[4] = 2*rad[4][1];
        fibarea[5] = 2*rad[5][1];
        fibarea[6] = 2*rad[6][1];
        fibarea[7] = 2*rad[7][1];



        sizemax[0] = cubelength;
    }
    else{
        for (int i=0; i<8; i++){
            idelta[i] = delta * ((float) rand()/RAND_MAX);    
        }
        sort(idelta, idelta+8);
        gap[0] = idelta[0];
        gap[8] = delta - idelta[7];
        for (int igap=0; igap<8; igap++){
            gap[igap] = idelta[igap] - idelta[igap-1];
        }
        //std::cout << "delta : " << delta << std::endl;
        //std::cout << "after sort : " << idelta[0] << ", "<< idelta[1] << ", "<< idelta[2]
          //        << ", " << idelta[3] << ", " << idelta[4] << ", " << idelta[5]
          //        << ", " << idelta[6] << ", " << idelta[7] 
          //        << std::endl;
        //std::cout << "gap : " << gap[0] << ", "<< gap[1] << ", "<< gap[2]
          //        << ", " << gap[3] << ", " << gap[4] << ", " << gap[5]
          //        << ", " << gap[6] << ", " << gap[7] << ", " << gap[8]
          //        << std::endl;
          
        //hwd[][2]はdepthのこと
        hole[0] = hole25[0][0] + gap[0];
        hole[1] = hole25[1][0] + hwd[0][2] + gap[0]+gap[1];
        hole[2] = hole25[2][0] + hwd[0][2]+hwd[1][2] + gap[0]+gap[1]+gap[2];
        hole[3] = hole25[3][0] + hwd[0][2]+hwd[1][2]+hwd[2][2] + gap[0]+gap[1]+gap[2]+gap[3];
        hole[4] = hole25[4][0] + hwd[0][2]+hwd[1][2]+hwd[2][2]+hwd[3][2] + gap[0]+gap[1]+gap[2]+gap[3]+gap[4];
        hole[5] = hole25[5][0] + hwd[0][2]+hwd[1][2]+hwd[2][2]+hwd[3][2]+hwd[4][2] + gap[0]+gap[1]+gap[2]+gap[3]+gap[4]+gap[5];
        hole[6] = hole25[6][0] + hwd[0][2]+hwd[1][2]+hwd[2][2]+hwd[3][2]+hwd[4][2]+hwd[5][2] 
                               + gap[0]+gap[1]+gap[2]+gap[3]+gap[4]+gap[5]+gap[6];
        hole[7] = hole25[7][0] + hwd[0][2]+hwd[1][2]+hwd[2][2]+hwd[3][2]
                                +hwd[4][2]+hwd[5][2]+hwd[6][2] 
                               + gap[0]+gap[1]+gap[2]+gap[3]+gap[4]+gap[5]+gap[6]+gap[7];


        //par[0]:xs, par[1]:ys, par[2]:xh, par[3]:yh, par[4]:r
        

        fibarea[0] = 2*rad[0][1];
        fibarea[1] = 2*rad[1][1];
        fibarea[2] = 2*rad[2][1];
        fibarea[3] = 2*rad[3][1];
        fibarea[4] = 2*rad[4][1];
        fibarea[5] = 2*rad[5][1];
        fibarea[6] = 2*rad[6][1];
        fibarea[7] = 2*rad[7][1];

        sizemax[0] = hwd[0][2]+hwd[1][2]+hwd[2][2]+hwd[3][2]+hwd[4][2]+hwd[5][2]+hwd[6][2]+hwd[7][2]+delta -gap[8]; 
    }   
    
    
    //std::cout << "hole info: " 
      //        << hole[0] <<", "<< hole[1] <<", "<< hole[2] <<", "<< hole[3] <<", "
      //        << hole[4] <<", "<< hole[5] <<", "<< hole[6] <<", "<< hole[7] <<std::endl;
    //std::cout << "sizemax[0]: " << sizemax[0] << "\n"<< std::endl;
}


void CubeArrangey2(Cube *c1, Cube *c2, Cube *c3, Cube *c4,
                  Cube *c5, Cube *c6, Cube *c7, Cube *c8, 
                  float * hole, float * fibarea,
                  float * sizemax)

//hole[8]   : 各キューブのファイバーが通る領域の中心の高さ
//fibarea[8]: 各キューブのファイバーが通る領域の直径
//sizemax[0]: 前の列までの最大キューブ高さ
//sizemax[1]: 今回の列のキューブ高さ

{
    float hwd[8][3], hole25[8][2], rad[8][6];
    c1->GetSize(hwd[0]);
    c1->GetHole25(hole25[0]);
    c1->GetRadius(rad[0]);
    c2->GetSize(hwd[1]);
    c2->GetHole25(hole25[1]);
    c2->GetRadius(rad[1]);
    c3->GetSize(hwd[2]);
    c3->GetHole25(hole25[2]);
    c3->GetRadius(rad[2]);
    c4->GetSize(hwd[3]);
    c4->GetHole25(hole25[3]);
    c4->GetRadius(rad[3]);
    c5->GetSize(hwd[4]);
    c5->GetHole25(hole25[4]);
    c5->GetRadius(rad[4]);
    c6->GetSize(hwd[5]);
    c6->GetHole25(hole25[5]);
    c6->GetRadius(rad[5]);
    c7->GetSize(hwd[6]);
    c7->GetHole25(hole25[6]);
    c7->GetRadius(rad[6]);
    c8->GetSize(hwd[7]);
    c8->GetHole25(hole25[7]);
    c8->GetRadius(rad[7]);
    //各キューブのパラメータを取得する

    float cubelength = hwd[0][2]+hwd[1][2]+hwd[2][2]+hwd[3][2]
                      +hwd[4][2]+hwd[5][2]+hwd[6][2]+hwd[7][2];
    float delta      = 82.3 - cubelength;
    float idelta[8];
    float gap[9];
    if (delta<=0){
        //キューブの全長がジグ幅より大きい時はその時点でアウト
        sizemax[1] = cubelength;
        //std::cout << "cubelength = " << cubelength << ", " << std::endl;
        //std::cout << "delta = " << delta << "<=0."<< std::endl;
        return; 
    }
    else{
        //キューブの全長がジグ幅より小さい時は、gap を分配する
        for (int i=0; i<8; i++){
            idelta[i] = delta * ((float) rand()/RAND_MAX);    
        }
        sort(idelta, idelta+8);
        gap[0] = idelta[0];
        gap[8] = delta - idelta[7];
        for (int igap=0; igap<8; igap++){
            gap[igap] = idelta[igap] - idelta[igap-1];
        }
        //std::cout << "delta : " << delta << std::endl;
        //std::cout << "after sort : " << idelta[0] << ", "<< idelta[1] << ", "<< idelta[2]
          //        << ", " << idelta[3] << ", " << idelta[4] << ", " << idelta[5]
          //        << ", " << idelta[6] << ", " << idelta[7] 
          //        << std::endl;
        //std::cout << "gap : " << gap[0] << ", "<< gap[1] << ", "<< gap[2]
          //        << ", " << gap[3] << ", " << gap[4] << ", " << gap[5]
          //        << ", " << gap[6] << ", " << gap[7] << ", " << gap[8]
          //        << std::endl;
    
    }



        //par[0]:xs, par[1]:ys, par[2]:xh, par[3]:yh, par[4]:r


    float d[8];
    float alpha[0];

    //一個めのキューブをおく。
 //   //std::cout << "*1st cube:" << std::endl;
    d[0] = fibarea[0]/2 + rad[0][1] - fabs(hole[0]-(hole25[0][0]+gap[0]));
    if (d[0] >= 1){  // かさ上げ必要なし。
        sizemax[1] = hwd[0][2]+gap[0];
        if (hole[0] >= hole25[0][0]+gap[0]){
            hole[0] = hole[0] + (- fibarea[0]/2 + d[0]/2);
            fibarea[0] = d[0];
        }
        else {
            hole[0] = hole[0] - (- fibarea[0]/2 + d[0]/2);
            fibarea[0] = d[0];
        }
    }
    else{   
            sizemax[1]=100;
            return;
        

    }

    //二個目のキューブをおく。
 //   //std::cout << "*2nd cube:" << std::endl;
    d[1] = fibarea[1]/2 + rad[1][1] - fabs(hole[1]-(hole25[1][0]+gap[1]+sizemax[1]));
    if (d[1] >= 1){  // かさ上げ必要なし。
        if (hole[1] >= hole25[1][0]+gap[1] + sizemax[1]){
            hole[1] = hole[1] + (- fibarea[1]/2 + d[1]/2);
            fibarea[1] = d[1];
            sizemax[1] = sizemax[1] + hwd[1][2]+gap[1];
        }
        else{
            hole[1] = hole[1] - (- fibarea[1]/2 + d[1]/2);
            fibarea[1] = d[1];
            sizemax[1] = sizemax[1] + hwd[1][2]+gap[1];
        }
    }
    else{
        if (fabs(fibarea[1]/2-rad[1][1])>fabs(hole[1]-(hole25[1][0]+gap[1]+sizemax[1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + hwd[1][2]+gap[1];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }


    //三個目のキューブをおく。
 //   //std::cout << "*3rd cube:" << std::endl;
    d[2] = fibarea[2]/2 + rad[2][1] - fabs(hole[2]-(hole25[2][0]+gap[2]+sizemax[1]));
    if (d[2] >= 1){  // かさ上げ必要なし。
        if (hole[2] >= hole25[2][0]+gap[2] + sizemax[1]){
            hole[2] = hole[2] + (- fibarea[2]/2 + d[2]/2);
            fibarea[2] = d[2];
            sizemax[1] = sizemax[1] + hwd[2][2]+gap[2];
        }
        else{
            hole[2] = hole[2] - (- fibarea[2]/2 + d[2]/2);
            fibarea[2] = d[2];
            sizemax[1] = sizemax[1] + hwd[2][2]+gap[2];
        }
    }
    else{
        if (fabs(fibarea[2]/2-rad[2][1])>fabs(hole[2]-(hole25[2][0]+gap[2]+sizemax[1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + hwd[2][2]+gap[2];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }
    

    //四個目のキューブをおく。
 //   //std::cout << "*4th cube:" << std::endl;
    d[3] = fibarea[3]/2 + rad[3][1] - fabs(hole[3]-(hole25[3][0]+gap[3]+sizemax[1]));
    if (d[3] >= 1){  // かさ上げ必要なし。
        if (hole[3] >= hole25[3][0]+gap[3] + sizemax[1]){
            hole[3] = hole[3] + (- fibarea[3]/2 + d[3]/2);
            fibarea[3] = d[3];
            sizemax[1] = sizemax[1] + hwd[3][2]+gap[3];
        }
        else{
            hole[3] = hole[3] - (- fibarea[3]/2 + d[3]/2);
            fibarea[3] = d[3];
            sizemax[1] = sizemax[1] + hwd[3][2]+gap[3];
        }
    }
    else{
        if (fabs(fibarea[3]/2-rad[3][1])>fabs(hole[3]-(hole25[3][0]+gap[3]+sizemax[1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + hwd[3][2]+gap[3];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }
    
    //五個目のキューブをおく。
 //   //std::cout << "*5th cube:" << std::endl;
    d[4] = fibarea[4]/2 + rad[4][1] - fabs(hole[4]-(hole25[4][0]+gap[4]+sizemax[1]));
    if (d[4] >= 1){  // かさ上げ必要なし。
        if (hole[4] >= hole25[4][0]+gap[4] + sizemax[1]){
            hole[4] = hole[4] + (- fibarea[4]/2 + d[4]/2);
            fibarea[4] = d[4];
            sizemax[1] = sizemax[1] + hwd[4][2]+gap[4];
        }
        else{
            hole[4] = hole[4] - (- fibarea[4]/2 + d[4]/2);
            fibarea[4] = d[4];
            sizemax[1] = sizemax[1] + hwd[4][2]+gap[4];
        }
    }
    else{
        if (fabs(fibarea[4]/2-rad[4][1])>fabs(hole[4]-(hole25[4][0]+gap[4]+sizemax[1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + hwd[4][2]+gap[4];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }
    
    //六個目のキューブをおく。
  //  //std::cout << "*6th cube:" << std::endl;
    d[5] = fibarea[5]/2 + rad[5][1] - fabs(hole[5]-(hole25[5][0]+gap[5]+sizemax[1]));
    if (d[5] >= 1){  // かさ上げ必要なし。
        if (hole[5] >= hole25[5][0]+gap[5] + sizemax[1]){
            hole[5] = hole[5] + (- fibarea[5]/2 + d[5]/2);
            fibarea[5] = d[5];
            sizemax[1] = sizemax[1] + hwd[5][2]+gap[5];
        }
        else{
            hole[5] = hole[5] - (- fibarea[5]/2 + d[5]/2);
            fibarea[5] = d[5];
            sizemax[1] = sizemax[1] + hwd[5][2]+gap[5];
        }
    }
    else{
        if (fabs(fibarea[5]/2-rad[5][1])>fabs(hole[5]-(hole25[5][0]+gap[5]+sizemax[1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + hwd[5][2]+gap[5];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }

    //七個目のキューブをおく。
 //   //std::cout << "*7th cube:" << std::endl;
    d[6] = fibarea[6]/2 + rad[6][1] - fabs(hole[6]-(hole25[6][0]+gap[6]+sizemax[1]));
    if (d[6] >= 1){  // かさ上げ必要なし。
        if (hole[6] >= hole25[6][0]+gap[6] + sizemax[1]){
            hole[6] = hole[6] + (- fibarea[6]/2 + d[6]/2);
            fibarea[6] = d[6];
            sizemax[1] = sizemax[1] + hwd[6][2]+gap[6];
        }
        else{
            hole[6] = hole[6] - (- fibarea[6]/2 + d[6]/2);
            fibarea[6] = d[6];
            sizemax[1] = sizemax[1] + hwd[6][2]+gap[6];
        }
    }
    else{
        if (fabs(fibarea[6]/2-rad[6][1])>fabs(hole[6]-(hole25[6][0]+gap[6]+sizemax[1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + hwd[6][2]+gap[6];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }

    //八個目のキューブをおく。
//    //std::cout << "*8th cube:" << std::endl;
    d[7] = fibarea[7]/2 + rad[7][1] - fabs(hole[7]-(hole25[7][0]+gap[7]+sizemax[1]));
    if (d[7] >= 1){  // かさ上げ必要なし。
        if (hole[7] >= hole25[7][0]+gap[7] + sizemax[1]){
            hole[7] = hole[7] + (- fibarea[7]/2 + d[7]/2);
            fibarea[7] = d[7];
            sizemax[1] = sizemax[1] + hwd[7][2]+gap[7];
        }
        else{
            hole[7] = hole[7] - (- fibarea[7]/2 + d[7]/2);
            fibarea[7] = d[7];
            sizemax[1] = sizemax[1] + hwd[7][2]+gap[7];
        }
    }
    else{
        if (fabs(fibarea[7]/2-rad[7][1])>fabs(hole[7]-(hole25[7][0]+gap[7]+sizemax[1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + hwd[7][2]+gap[7];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }

//    //std::cout << "\nhole info: " 
//              << hole[0] <<", "<< hole[1] <<", "<< hole[2] <<", "<< hole[3] <<", "
//              << hole[4] <<", "<< hole[5] <<", "<< hole[6] <<", "<< hole[7] <<std::endl;


    //std::cout << "sizemax[0] : " << sizemax[0] <<", sizemax[1] : "<< sizemax[1] <<std::endl;

}
///******************************************************************************
///******************************************************************************
///横に並べていく関数
///各キューブの2面のxsize 等を使う。
void CubeArrangex1(Cube *c1, Cube *c2, Cube *c3, Cube *c4,
                  Cube *c5, Cube *c6, Cube *c7, Cube *c8, 
                  float * hole, float * fibarea,
                  float * sizemax)
{
    //par[0]:xs, par[1]:ys, par[2]:xh, par[3]:yh, par[4]:r
    float hwd[8][3], hole36[8][2], rad[8][6];

    c1->GetSize(hwd[0]);
    c1->GetHole36(hole36[0]);
    c1->GetRadius(rad[0]);
    c2->GetSize(hwd[1]);
    c2->GetHole36(hole36[1]);
    c2->GetRadius(rad[1]);
    c3->GetSize(hwd[2]);
    c3->GetHole36(hole36[2]);
    c3->GetRadius(rad[2]);
    c4->GetSize(hwd[3]);
    c4->GetHole36(hole36[3]);
    c4->GetRadius(rad[3]);
    c5->GetSize(hwd[4]);
    c5->GetHole36(hole36[4]);
    c5->GetRadius(rad[4]);
    c6->GetSize(hwd[5]);
    c6->GetHole36(hole36[5]);
    c6->GetRadius(rad[5]);
    c7->GetSize(hwd[6]);
    c7->GetHole36(hole36[6]);
    c7->GetRadius(rad[6]);
    c8->GetSize(hwd[7]);
    c8->GetHole36(hole36[7]);
    c8->GetRadius(rad[7]);


    ///穴位置が縦の時と定義がちょっと異なる
    float cubelength = hwd[0][1]+hwd[1][1]+hwd[2][1]+hwd[3][1]
                      +hwd[4][1]+hwd[5][1]+hwd[6][1]+hwd[7][1];
    float delta      = 82.3 - cubelength;
    float idelta[8];
    float gap[9];
    if (delta<=0.001){
        std::cout << "cubelength = " << cubelength << ", " << std::endl;
        std::cout << "delta = " << delta << "<=0."<< std::endl;
    //第3面はyholeを使う。
        hole[0] = hole36[0][1];
        hole[1] = hole36[1][1] + hwd[0][1];
        hole[2] = hole36[2][1] + hwd[0][1]+hwd[1][1];
        hole[3] = hole36[3][1] + hwd[0][1]+hwd[1][1]+hwd[2][1];
        hole[4] = hole36[4][1] + hwd[0][1]+hwd[1][1]+hwd[2][1]+hwd[3][1];
        hole[5] = hole36[5][1] + hwd[0][1]+hwd[1][1]+hwd[2][1]+hwd[3][1]+hwd[4][1];
        hole[6] = hole36[6][1] + hwd[0][1]+hwd[1][1]+hwd[2][1]+hwd[3][1]+hwd[4][1]+hwd[5][1];
        hole[7] = hole36[7][1] + hwd[0][1]+hwd[1][1]+hwd[2][1]+hwd[3][1]
                                +hwd[4][1]+hwd[5][1]+hwd[6][1];
       //第3面の穴 
        fibarea[0] = 2*rad[0][2];
        fibarea[1] = 2*rad[1][2];
        fibarea[2] = 2*rad[2][2];
        fibarea[3] = 2*rad[3][2];
        fibarea[4] = 2*rad[4][2];
        fibarea[5] = 2*rad[5][2];
        fibarea[6] = 2*rad[6][2];
        fibarea[7] = 2*rad[7][2];


        sizemax[0] = cubelength; 
    } 
    else{
        for (int i=0; i<8; i++){
            idelta[i] = delta * ((float) rand()/RAND_MAX);    
        }
        sort(idelta, idelta+8);
        gap[0] = idelta[0];
        gap[8] = delta - idelta[7];
        for (int igap=0; igap<8; igap++){
            gap[igap] = idelta[igap] - idelta[igap-1];
        }
        //std::cout << "delta : " << delta << std::endl;
        //std::cout << "after sort : " << idelta[0] << ", "<< idelta[1] << ", "<< idelta[2]
          //        << ", " << idelta[3] << ", " << idelta[4] << ", " << idelta[5]
          //        << ", " << idelta[6] << ", " << idelta[7] 
          //        << std::endl;
        //std::cout << "gap : " << gap[0] << ", "<< gap[1] << ", "<< gap[2]
          //        << ", " << gap[3] << ", " << gap[4] << ", " << gap[5]
          //        << ", " << gap[6] << ", " << gap[7] << ", " << gap[8]
          //        << std::endl;


        //par[0]:xs, par[1]:ys, par[2]:xh, par[3]:yh, par[4]:r

        hole[0] = hole36[0][1] + gap[0];
        hole[1] = hole36[1][1] + hwd[0][1] + gap[0]+gap[1];
        hole[2] = hole36[2][1] + hwd[0][1]+hwd[1][1] + gap[0]+gap[1]+gap[2];
        hole[3] = hole36[3][1] + hwd[0][1]+hwd[1][1]+hwd[2][1] + gap[0]+gap[1]+gap[2]+gap[3];
        hole[4] = hole36[4][1] + hwd[0][1]+hwd[1][1]+hwd[2][1]+hwd[3][1] + gap[0]+gap[1]+gap[2]+gap[3]+gap[4];
        hole[5] = hole36[5][1] + hwd[0][1]+hwd[1][1]+hwd[2][1]+hwd[3][1]+hwd[4][1] + gap[0]+gap[1]+gap[2]+gap[3]+gap[4]+gap[5];
        hole[6] = hole36[6][1] + hwd[0][1]+hwd[1][1]+hwd[2][1]+hwd[3][1]+hwd[4][1]+hwd[5][1] 
                               + gap[0]+gap[1]+gap[2]+gap[3]+gap[4]+gap[5]+gap[6];
        hole[7] = hole36[7][1] + hwd[0][1]+hwd[1][1]+hwd[2][1]+hwd[3][1]
                                +hwd[4][1]+hwd[5][1]+hwd[6][1] 
                               + gap[0]+gap[1]+gap[2]+gap[3]+gap[4]+gap[5]+gap[6]+gap[7];



        fibarea[0] = 2*rad[0][2];
        fibarea[1] = 2*rad[1][2];
        fibarea[2] = 2*rad[2][2];
        fibarea[3] = 2*rad[3][2];
        fibarea[4] = 2*rad[4][2];
        fibarea[5] = 2*rad[5][2];
        fibarea[6] = 2*rad[6][2];
        fibarea[7] = 2*rad[7][2];

        sizemax[0] = hwd[0][1]+hwd[1][1]+hwd[2][1]+hwd[3][1]+hwd[4][1]+hwd[5][1]+hwd[6][1]+hwd[7][1]+delta -gap[8]; 
        
    }   
    
    
    //std::cout << "hole info: " 
      //        << hole[0] <<", "<< hole[1] <<", "<< hole[2] <<", "<< hole[3] <<", "
      //        << hole[4] <<", "<< hole[5] <<", "<< hole[6] <<", "<< hole[7] <<std::endl;
    //std::cout << "sizemax[0]: " << sizemax[0] << "\n"<< std::endl;
}



///横に並べていく関数
///各キューブの2面のxsize 等を使う。
void CubeArrangex2(Cube *c1, Cube *c2, Cube *c3, Cube *c4,
                  Cube *c5, Cube *c6, Cube *c7, Cube *c8, 
                  float * hole, float * fibarea,
                  float * sizemax)

//hole[8]   : 各キューブのファイバーが通る領域の中心の高さ
//fibarea[8]: 各キューブのファイバーが通る領域の直径
//sizemax[0]: 前の列までの最大キューブ高さ
//sizemax[1]: 今回の列のキューブ高さ

{
    float hwd[8][3], hole36[8][2], rad[8][6];
    c1->GetSize(hwd[0]);
    c1->GetHole36(hole36[0]);
    c1->GetRadius(rad[0]);
    c2->GetSize(hwd[1]);
    c2->GetHole36(hole36[1]);
    c2->GetRadius(rad[1]);
    c3->GetSize(hwd[2]);
    c3->GetHole36(hole36[2]);
    c3->GetRadius(rad[2]);
    c4->GetSize(hwd[3]);
    c4->GetHole36(hole36[3]);
    c4->GetRadius(rad[3]);
    c5->GetSize(hwd[4]);
    c5->GetHole36(hole36[4]);
    c5->GetRadius(rad[4]);
    c6->GetSize(hwd[5]);
    c6->GetHole36(hole36[5]);
    c6->GetRadius(rad[5]);
    c7->GetSize(hwd[6]);
    c7->GetHole36(hole36[6]);
    c7->GetRadius(rad[6]);
    c8->GetSize(hwd[7]);
    c8->GetHole36(hole36[7]);
    c8->GetRadius(rad[7]);
    //par[0]:xs, par[1]:ys, par[2]:xh, par[3]:yh, par[4]:rに対応
    //各キューブのパラメータを取得する
    float cubelength = hwd[0][1]+hwd[1][1]+hwd[2][1]+hwd[3][1]
                      +hwd[4][1]+hwd[5][1]+hwd[6][1]+hwd[7][1];
    //std::cout << "cubelength x: "<< cubelength << std::endl;
                    
    
    float delta      = 82.3 - cubelength;
    float idelta[8];
    float gap[9];
    if (cubelength == 82.3){
        std::cout << delta << std::endl;
    }
    if (delta<=0.001){
        std::cout << "hello" << std::endl;
        sizemax[1] = cubelength;
        std::cout << "delta = " << delta << "<=0."<< std::endl;
        return; 
    }
    else{
        for (int i=0; i<8; i++){
            idelta[i] = delta * ((float) rand()/RAND_MAX);    
        }
        sort(idelta, idelta+8);
        gap[0] = idelta[0];
        gap[8] = delta - idelta[7];
        for (int igap=0; igap<8; igap++){
            gap[igap] = idelta[igap] - idelta[igap-1];
        }
        //std::cout << "delta : " << delta << std::endl;
        //std::cout << "after sort : " << idelta[0] << ", "<< idelta[1] << ", "<< idelta[2]
          //        << ", " << idelta[3] << ", " << idelta[4] << ", " << idelta[5]
          //        << ", " << idelta[6] << ", " << idelta[7] 
          //        << std::endl;
        //std::cout << "gap : " << gap[0] << ", "<< gap[1] << ", "<< gap[2]
          //        << ", " << gap[3] << ", " << gap[4] << ", " << gap[5]
          //        << ", " << gap[6] << ", " << gap[7] << ", " << gap[8]
          //        << std::endl;
    
    }
        //par[0]:xs, par[1]:ys, par[2]:xh, par[3]:yh, par[4]:r

    float d[8];
    float alpha[0];

    //一個めのキューブをおく。
//    //std::cout << "*1st cube:" << std::endl;
    d[0] = fibarea[0]/2 + rad[0][2] - fabs(hole[0]-(gap[0]+hole36[0][1]));
    if (d[0] >= 1){  // かさ上げ必要なし。
        sizemax[1] = hwd[0][1]+gap[0];
        if (hole[0] >= (gap[0]+hole36[0][1])){
            hole[0] = hole[0] + (- fibarea[0]/2 + d[0]/2);
            fibarea[0] = d[0];
        }
        else {
            hole[0] = hole[0] - (- fibarea[0]/2 + d[0]/2);
            fibarea[0] = d[0];
        }
    }
    else{   
            sizemax[1] =100;
            return;
    }

    //二個目のキューブをおく。
//    //std::cout << "*2nd cube:" << std::endl;
    d[1] = fibarea[1]/2 + rad[1][2] - fabs(hole[1]-(gap[1]+sizemax[1]+hole36[1][1]));
    if (d[1] >= 1){  // かさ上げ必要なし。
        if (hole[1] >= gap[1] + sizemax[1]+hole36[1][1]){
            hole[1] = hole[1] + (- fibarea[1]/2 + d[1]/2);
            fibarea[1] = d[1];
            sizemax[1] = sizemax[1] + hwd[1][1]+gap[1];
        }
        else{
            hole[1] = hole[1] - (- fibarea[1]/2 + d[1]/2);
            fibarea[1] = d[1];
            sizemax[1] = sizemax[1] + hwd[1][1]+gap[1];
        }
    }
    else{
        if (fabs(fibarea[1]/2-rad[1][2])>fabs(hole[1]-(gap[1]+sizemax[1]+hole36[1][1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + hwd[1][1]+gap[1];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }


    //三個目のキューブをおく。
//    //std::cout << "*3rd cube:" << std::endl;
    d[2] = fibarea[2]/2 + rad[2][2] - fabs(hole[2]-(gap[2]+sizemax[1]+hole36[2][1]));
    if (d[2] >= 1){  // かさ上げ必要なし。
        if (hole[2] >= gap[2] + sizemax[1]+hole36[2][1]){
            hole[2] = hole[2] + (- fibarea[2]/2 + d[2]/2);
            fibarea[2] = d[2];
            sizemax[1] = sizemax[1] + hwd[2][1]+gap[2];
        }
        else{
            hole[2] = hole[2] - (- fibarea[2]/2 + d[2]/2);
            fibarea[2] = d[2];
            sizemax[1] = sizemax[1] + hwd[2][1]+gap[2];
        }
    }
    else{
        if (fabs(fibarea[2]/2-rad[2][2])>fabs(hole[2]-(gap[2]+sizemax[1]+hole36[2][1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + hwd[2][1]+gap[2];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }
    

    //四個目のキューブをおく。
//    //std::cout << "*4th cube:" << std::endl;
    d[3] = fibarea[3]/2 + rad[3][2] - fabs(hole[3]-(gap[3]+sizemax[1]+hole36[3][1]));
    if (d[3] >= 1){  // かさ上げ必要なし。
        if (hole[3] >= gap[3] + sizemax[1]+hole36[3][1]){
            hole[3] = hole[3] + (- fibarea[3]/2 + d[3]/2);
            fibarea[3] = d[3];
            sizemax[1] = sizemax[1] + hwd[3][1]+gap[3];
        }
        else{
            hole[3] = hole[3] - (- fibarea[3]/2 + d[3]/2);
            fibarea[3] = d[3];
            sizemax[1] = sizemax[1] + hwd[3][1]+gap[3];
        }
    }
    else{
        if (fabs(fibarea[3]/2-rad[3][2])>fabs(hole[3]-(gap[3]+sizemax[1]+hole36[3][1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + hwd[3][1]+gap[3];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }
    
    //五個目のキューブをおく。
//    //std::cout << "*5th cube:" << std::endl;
    d[4] = fibarea[4]/2 + rad[4][2] - fabs(hole[4]-(gap[4]+sizemax[1]+hole36[4][1]));
    if (d[4] >= 1){  // かさ上げ必要なし。
        if (hole[4] >= gap[4] + sizemax[1]+hole36[4][1]){
            hole[4] = hole[4] + (- fibarea[4]/2 + d[4]/2);
            fibarea[4] = d[4];
            sizemax[1] = sizemax[1] + hwd[4][1]+gap[4];
        }
        else{
            hole[4] = hole[4] - (- fibarea[4]/2 + d[4]/2);
            fibarea[4] = d[4];
            sizemax[1] = sizemax[1] + hwd[4][1]+gap[4];
        }
    }
    else{
        if (fabs(fibarea[4]/2-rad[4][2])>fabs(hole[4]-(gap[4]+sizemax[1]+hole36[4][1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + hwd[4][1]+gap[4];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }
    
    //六個目のキューブをおく。
//    //std::cout << "*6th cube:" << std::endl;
    d[5] = fibarea[5]/2 + rad[5][2] - fabs(hole[5]-(gap[5]+sizemax[1]+hole36[5][1]));
    if (d[5] >= 1){  // かさ上げ必要なし。
        if (hole[5] >= gap[5] + sizemax[1]+hole36[5][1]){
            hole[5] = hole[5] + (- fibarea[5]/2 + d[5]/2);
            fibarea[5] = d[5];
            sizemax[1] = sizemax[1] + hwd[5][1]+gap[5];
        }
        else{
            hole[5] = hole[5] - (- fibarea[5]/2 + d[5]/2);
            fibarea[5] = d[5];
            sizemax[1] = sizemax[1] + hwd[5][1]+gap[5];
        }
    }
    else{
        if (fabs(fibarea[5]/2-rad[5][2])>fabs(hole[5]-(gap[5]+sizemax[1]+hole36[5][1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + hwd[5][1]+gap[5];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }

    //七個目のキューブをおく。
//    //std::cout << "*7th cube:" << std::endl;
    d[6] = fibarea[6]/2 + rad[6][2] - fabs(hole[6]-(gap[6]+sizemax[1]+hole36[6][1]));
    if (d[6] >= 1){  // かさ上げ必要なし。
        if (hole[6] >= gap[6] + sizemax[1]+hole36[6][1]){
            hole[6] = hole[6] + (- fibarea[6]/2 + d[6]/2);
            fibarea[6] = d[6];
            sizemax[1] = sizemax[1] + hwd[6][1]+gap[6];
        }
        else{
            hole[6] = hole[6] - (- fibarea[6]/2 + d[6]/2);
            fibarea[6] = d[6];
            sizemax[1] = sizemax[1] + hwd[6][1]+gap[6];
        }
    }
    else{
        if (fabs(fibarea[6]/2-rad[6][2])>fabs(hole[6]-(gap[6]+sizemax[1]+hole36[6][1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + hwd[6][1]+gap[6];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }

    //八個目のキューブをおく。
//    //std::cout << "*8th cube:" << std::endl;
    d[7] = fibarea[7]/2 + rad[7][2] - fabs(hole[7]-(gap[7]+sizemax[1]+hole36[7][1]));
    if (d[7] >= 1){  // かさ上げ必要なし。
        if (hole[7] >= gap[7] + sizemax[1]+hole36[7][1]){
            hole[7] = hole[7] + (- fibarea[7]/2 + d[7]/2);
            fibarea[7] = d[7];
            sizemax[1] = sizemax[1] + hwd[7][1]+gap[7];
        }
        else{
            hole[7] = hole[7] - (- fibarea[7]/2 + d[7]/2);
            fibarea[7] = d[7];
            sizemax[1] = sizemax[1] + hwd[7][1]+gap[7];
        }
    }
    else{
        if (fabs(fibarea[7]/2-rad[7][2])>fabs(hole[7]-(gap[7]+sizemax[1]+hole36[7][1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + hwd[7][1]+gap[7];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }

//    //std::cout << "\nhole info: " 
//              << hole[0] <<", "<< hole[1] <<", "<< hole[2] <<", "<< hole[3] <<", "
//              << hole[4] <<", "<< hole[5] <<", "<< hole[6] <<", "<< hole[7] <<std::endl;


    //std::cout << "sizemax[0] : " << sizemax[0] <<", sizemax[1] : "<< sizemax[1] <<std::endl;

}





Cube::~Cube()

{
}
