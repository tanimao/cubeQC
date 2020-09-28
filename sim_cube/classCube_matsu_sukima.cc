/*


*/
#include "classCube.h"
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
ClassImp(Cube)

Cube::Cube()
{
}

Cube::Cube(int id,
           float surf1_xs, float surf1_ys, float surf1_xh, float surf1_yh, float surf1_r,
           float surf2_xs, float surf2_ys, float surf2_xh, float surf2_yh, float surf2_r,
           float surf3_xs, float surf3_ys, float surf3_xh, float surf3_yh, float surf3_r,
           float surf4_xs, float surf4_ys, float surf4_xh, float surf4_yh, float surf4_r,
           float surf5_xs, float surf5_ys, float surf5_xh, float surf5_yh, float surf5_r,
           float surf6_xs, float surf6_ys, float surf6_xh, float surf6_yh, float surf6_r
          )
        : _id(0),
          _surf1_xs(0.), _surf1_ys(0.), _surf1_xh(0.), _surf1_yh(0.), _surf1_r(0.),
          _surf2_xs(0.), _surf2_ys(0.), _surf2_xh(0.), _surf2_yh(0.), _surf2_r(0.),
          _surf3_xs(0.), _surf3_ys(0.), _surf3_xh(0.), _surf3_yh(0.), _surf3_r(0.),
          _surf4_xs(0.), _surf4_ys(0.), _surf4_xh(0.), _surf4_yh(0.), _surf4_r(0.),
          _surf5_xs(0.), _surf5_ys(0.), _surf5_xh(0.), _surf5_yh(0.), _surf5_r(0.),
          _surf6_xs(0.), _surf6_ys(0.), _surf6_xh(0.), _surf6_yh(0.), _surf6_r(0.)

{

   _id = id;
	_surf1_xs = surf1_xs;
	_surf1_ys = surf1_ys;
	_surf1_xh = surf1_xh;
	_surf1_yh = surf1_yh;
	_surf1_r  = surf1_r;

	_surf2_xs = surf2_xs;
	_surf2_ys = surf2_ys;
	_surf2_xh = surf2_xh;
	_surf2_yh = surf2_yh;
	_surf2_r  = surf2_r;

	_surf3_xs = surf3_xs;
	_surf3_ys = surf3_ys;
	_surf3_xh = surf3_xh;
	_surf3_yh = surf3_yh;
	_surf3_r  = surf3_r;

	_surf4_xs = surf4_xs;
	_surf4_ys = surf4_ys;
	_surf4_xh = surf4_xh;
	_surf4_yh = surf4_yh;
	_surf4_r  = surf4_r;

	_surf5_xs = surf5_xs;
	_surf5_ys = surf5_ys;
	_surf5_xh = surf5_xh;
	_surf5_yh = surf5_yh;
	_surf5_r  = surf5_r;

	_surf6_xs = surf6_xs;
	_surf6_ys = surf6_ys;
	_surf6_xh = surf6_xh;
	_surf6_yh = surf6_yh;
	_surf6_r  = surf6_r;

   std::cerr << "constructor Cube id = " << _id << std::endl;
   std::cerr << "set surf1 parameter xsize = " << _surf1_xs << std::endl;
   std::cerr << "set surf1 parameter ysize = " << _surf1_ys << std::endl;
}


void Cube::GetSurf1(float parlist[5])
{
    parlist[0] = _surf1_xs;
    parlist[1] = _surf1_ys;
    parlist[2] = _surf1_xh;
    parlist[3] = _surf1_yh;
    parlist[4] = _surf1_r;
}

void Cube::GetSurf2(float parlist[5])
{
    parlist[0] = _surf2_xs;
    parlist[1] = _surf2_ys;
    parlist[2] = _surf2_xh;
    parlist[3] = _surf2_yh;
    parlist[4] = _surf2_r;
}

void Cube::GetSurf3(float parlist[5])
{
    parlist[0] = _surf3_xs;
    parlist[1] = _surf3_ys;
    parlist[2] = _surf3_xh;
    parlist[3] = _surf3_yh;
    parlist[4] = _surf3_r;
}

void Cube::GetSurf4(float parlist[5])
{
    parlist[0] = _surf4_xs;
    parlist[1] = _surf4_ys;
    parlist[2] = _surf4_xh;
    parlist[3] = _surf4_yh;
    parlist[4] = _surf4_r;
}

void Cube::GetSurf5(float parlist[5])
{
    parlist[0] = _surf5_xs;
    parlist[1] = _surf5_ys;
    parlist[2] = _surf5_xh;
    parlist[3] = _surf5_yh;
    parlist[4] = _surf5_r;
}

void Cube::GetSurf6(float parlist[5])
{
    parlist[0] = _surf6_xs;
    parlist[1] = _surf6_ys;
    parlist[2] = _surf6_xh;
    parlist[3] = _surf6_yh;
    parlist[4] = _surf6_r;
}


void CubeArrangey1(Cube *c1, Cube *c2, Cube *c3, Cube *c4,
                  Cube *c5, Cube *c6, Cube *c7, Cube *c8, 
                  float * hole, float * fibarea,
                  float * sizemax)
{
    float par1[5], par2[5], par3[5], par4[5];
    float par5[5], par6[5], par7[5], par8[5];
    //par[0]:xs, par[1]:ys, par[2]:xh, par[3]:yh, par[4]:r
    c1->GetSurf1(par1);
    c2->GetSurf1(par2);
    c3->GetSurf1(par3);
    c4->GetSurf1(par4);
    c5->GetSurf1(par5);
    c6->GetSurf1(par6);
    c7->GetSurf1(par7);
    c8->GetSurf1(par8);


    float cubelength = par1[1]+par2[1]+par3[1]+par4[1]+par5[1]+par6[1]+par7[1]+par8[1];
    float delta      = 82.3 - cubelength;
    float idelta[8];
    float gap[9];
    if (delta<=0){

        hole[0] = par1[3]; 
        hole[1] = par2[3] + par1[1];
        hole[2] = par3[3] + par1[1]+par2[1];
        hole[3] = par4[3] + par1[1]+par2[1]+par3[1];
        hole[4] = par5[3] + par1[1]+par2[1]+par3[1]+par4[1];
        hole[5] = par6[3] + par1[1]+par2[1]+par3[1]+par4[1]+par5[1];
        hole[6] = par7[3] + par1[1]+par2[1]+par3[1]+par4[1]+par5[1]+par6[1];
        hole[7] = par8[3] + par1[1]+par2[1]+par3[1]+par4[1]+par5[1]+par6[1]+par7[1];
    
    
        fibarea[0] = 2*par1[4];
        fibarea[1] = 2*par2[4];
        fibarea[2] = 2*par3[4];
        fibarea[3] = 2*par4[4];
        fibarea[4] = 2*par5[4];
        fibarea[5] = 2*par6[4];
        fibarea[6] = 2*par7[4];
        fibarea[7] = 2*par8[4];
        
        sizemax[0] = par1[1]+par2[1]+par3[1]+par4[1]+par5[1]+par6[1]+par7[1]+par8[1];
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
        std::cout << "delta : " << delta << std::endl;
        std::cout << "after sort : " << idelta[0] << ", "<< idelta[1] << ", "<< idelta[2]
                  << ", " << idelta[3] << ", " << idelta[4] << ", " << idelta[5]
                  << ", " << idelta[6] << ", " << idelta[7] 
                  << std::endl;
        std::cout << "gap : " << gap[0] << ", "<< gap[1] << ", "<< gap[2]
                  << ", " << gap[3] << ", " << gap[4] << ", " << gap[5]
                  << ", " << gap[6] << ", " << gap[7] << ", " << gap[8]
                  << std::endl;


        //par[0]:xs, par[1]:ys, par[2]:xh, par[3]:yh, par[4]:r
        hole[0] = par1[3] + gap[0];
        hole[1] = par1[1] + gap[0] + par2[3] + gap[1];
        hole[2] = par1[1] + gap[0] + par2[1] + gap[1] + par3[3] + gap[2];
        hole[3] = par1[1] + gap[0] + par2[1] + gap[1] + par3[1] + gap[2] + par4[3] + gap[3];
        hole[4] = par1[1] + gap[0] + par2[1] + gap[1] + par3[1] + gap[2] + par4[1] + gap[3]
                + par5[3] + gap[4];
        hole[5] = par1[1] + gap[0] + par2[1] + gap[1] + par3[1] + gap[2] + par4[1] + gap[3]
                + par5[1] + gap[4] + par6[3] + gap[5];
        hole[6] = par1[1] + gap[0] + par2[1] + gap[1] + par3[1] + gap[2] + par4[1] + gap[3]
                + par5[1] + gap[4] + par6[1] + gap[5] + par7[3] + gap[6];
        hole[7] = par1[1] + gap[0] + par2[1] + gap[1] + par3[1] + gap[2] + par4[1] + gap[3]
                + par5[1] + gap[4] + par6[1] + gap[5] + par7[1] + gap[6] + par8[3] + gap[7];
        
        fibarea[0] = 2*par1[4];
        fibarea[1] = 2*par2[4];
        fibarea[2] = 2*par3[4];
        fibarea[3] = 2*par4[4];
        fibarea[4] = 2*par5[4];
        fibarea[5] = 2*par6[4];
        fibarea[6] = 2*par7[4];
        fibarea[7] = 2*par8[4];

        sizemax[0] = par1[1]+par2[1]+par3[1]+par4[1]+par5[1]
                    +par6[1]+par7[1]+par8[1]+delta  - gap[8];
    }   
    
    
    std::cout << "hole info: " 
              << hole[0] <<", "<< hole[1] <<", "<< hole[2] <<", "<< hole[3] <<", "
              << hole[4] <<", "<< hole[5] <<", "<< hole[6] <<", "<< hole[7] <<std::endl;
    std::cout << "sizemax[0]: " << sizemax[0] << "\n"<< std::endl;
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
    float par1[5], par2[5], par3[5], par4[5];
    float par5[5], par6[5], par7[5], par8[5];
    //par[0]:xs, par[1]:ys, par[2]:xh, par[3]:yh, par[4]:rに対応
    //各キューブのパラメータを取得する
    c1->GetSurf1(par1);
    c2->GetSurf1(par2);
    c3->GetSurf1(par3);
    c4->GetSurf1(par4);
    c5->GetSurf1(par5);
    c6->GetSurf1(par6);
    c7->GetSurf1(par7);
    c8->GetSurf1(par8);



    float cubelength = par1[1]+par2[1]+par3[1]+par4[1]+par5[1]+par6[1]+par7[1]+par8[1];
    float delta      = 82.3 - cubelength;
    float idelta[8];
    float gap[9];
    if (delta<=0){
        sizemax[1] = cubelength;
        std::cout << "cubelength = " << cubelength << ", " << std::endl;
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
        std::cout << "delta : " << delta << std::endl;
        std::cout << "after sort : " << idelta[0] << ", "<< idelta[1] << ", "<< idelta[2]
                  << ", " << idelta[3] << ", " << idelta[4] << ", " << idelta[5]
                  << ", " << idelta[6] << ", " << idelta[7] 
                  << std::endl;
        std::cout << "gap : " << gap[0] << ", "<< gap[1] << ", "<< gap[2]
                  << ", " << gap[3] << ", " << gap[4] << ", " << gap[5]
                  << ", " << gap[6] << ", " << gap[7] << ", " << gap[8]
                  << std::endl;
    
    }



        //par[0]:xs, par[1]:ys, par[2]:xh, par[3]:yh, par[4]:r


    float d[8];
    float alpha[0];

    //一個めのキューブをおく。
 //   std::cout << "*1st cube:" << std::endl;
    d[0] = fibarea[0]/2 + par1[4] - fabs(hole[0]-(par1[3]+gap[0]));
    if (d[0] >= 1){  // かさ上げ必要なし。
        sizemax[1] = par1[1]+gap[0];
        if (hole[0] >= par1[3]+gap[0]){
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
 //   std::cout << "*2nd cube:" << std::endl;
    d[1] = fibarea[1]/2 + par2[4] - fabs(hole[1]-(par2[3]+gap[1]+sizemax[1]));
    if (d[1] >= 1){  // かさ上げ必要なし。
        if (hole[1] >= par2[3]+gap[1] + sizemax[1]){
            hole[1] = hole[1] + (- fibarea[1]/2 + d[1]/2);
            fibarea[1] = d[1];
            sizemax[1] = sizemax[1] + par2[1]+gap[1];
        }
        else{
            hole[1] = hole[1] - (- fibarea[1]/2 + d[1]/2);
            fibarea[1] = d[1];
            sizemax[1] = sizemax[1] + par2[1]+gap[1];
        }
    }
    else{
        if (fabs(fibarea[1]/2-par2[4])>fabs(hole[1]-(par2[3]+gap[1]+sizemax[1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + par2[1]+gap[1];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }


    //三個目のキューブをおく。
 //   std::cout << "*3rd cube:" << std::endl;
    d[2] = fibarea[2]/2 + par3[4] - fabs(hole[2]-(par3[3]+gap[2]+sizemax[1]));
    if (d[2] >= 1){  // かさ上げ必要なし。
        if (hole[2] >= par3[3]+gap[2] + sizemax[1]){
            hole[2] = hole[2] + (- fibarea[2]/2 + d[2]/2);
            fibarea[2] = d[2];
            sizemax[1] = sizemax[1] + par3[1]+gap[2];
        }
        else{
            hole[2] = hole[2] - (- fibarea[2]/2 + d[2]/2);
            fibarea[2] = d[2];
            sizemax[1] = sizemax[1] + par3[1]+gap[2];
        }
    }
    else{
        if (fabs(fibarea[2]/2-par3[4])>fabs(hole[2]-(par3[3]+gap[2]+sizemax[1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + par3[1]+gap[2];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }
    

    //四個目のキューブをおく。
 //   std::cout << "*4th cube:" << std::endl;
    d[3] = fibarea[3]/2 + par4[4] - fabs(hole[3]-(par4[3]+gap[3]+sizemax[1]));
    if (d[3] >= 1){  // かさ上げ必要なし。
        if (hole[3] >= par4[3]+gap[3] + sizemax[1]){
            hole[3] = hole[3] + (- fibarea[3]/2 + d[3]/2);
            fibarea[3] = d[3];
            sizemax[1] = sizemax[1] + par4[1]+gap[3];
        }
        else{
            hole[3] = hole[3] - (- fibarea[3]/2 + d[3]/2);
            fibarea[3] = d[3];
            sizemax[1] = sizemax[1] + par4[1]+gap[3];
        }
    }
    else{
        if (fabs(fibarea[3]/2-par4[4])>fabs(hole[3]-(par4[3]+gap[3]+sizemax[1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + par4[1]+gap[3];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }
    
    //五個目のキューブをおく。
 //   std::cout << "*5th cube:" << std::endl;
    d[4] = fibarea[4]/2 + par5[4] - fabs(hole[4]-(par5[3]+gap[4]+sizemax[1]));
    if (d[4] >= 1){  // かさ上げ必要なし。
        if (hole[4] >= par5[3]+gap[4] + sizemax[1]){
            hole[4] = hole[4] + (- fibarea[4]/2 + d[4]/2);
            fibarea[4] = d[4];
            sizemax[1] = sizemax[1] + par5[1]+gap[4];
        }
        else{
            hole[4] = hole[4] - (- fibarea[4]/2 + d[4]/2);
            fibarea[4] = d[4];
            sizemax[1] = sizemax[1] + par5[1]+gap[4];
        }
    }
    else{
        if (fabs(fibarea[4]/2-par5[4])>fabs(hole[4]-(par5[3]+gap[4]+sizemax[1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + par5[1]+gap[4];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }
    
    //六個目のキューブをおく。
  //  std::cout << "*6th cube:" << std::endl;
    d[5] = fibarea[5]/2 + par6[4] - fabs(hole[5]-(par6[3]+gap[5]+sizemax[1]));
    if (d[5] >= 1){  // かさ上げ必要なし。
        if (hole[5] >= par6[3]+gap[5] + sizemax[1]){
            hole[5] = hole[5] + (- fibarea[5]/2 + d[5]/2);
            fibarea[5] = d[5];
            sizemax[1] = sizemax[1] + par6[1]+gap[5];
        }
        else{
            hole[5] = hole[5] - (- fibarea[5]/2 + d[5]/2);
            fibarea[5] = d[5];
            sizemax[1] = sizemax[1] + par6[1]+gap[5];
        }
    }
    else{
        if (fabs(fibarea[5]/2-par6[4])>fabs(hole[5]-(par6[3]+gap[5]+sizemax[1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + par6[1]+gap[5];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }

    //七個目のキューブをおく。
 //   std::cout << "*7th cube:" << std::endl;
    d[6] = fibarea[6]/2 + par7[4] - fabs(hole[6]-(par7[3]+gap[6]+sizemax[1]));
    if (d[6] >= 1){  // かさ上げ必要なし。
        if (hole[6] >= par7[3]+gap[6] + sizemax[1]){
            hole[6] = hole[6] + (- fibarea[6]/2 + d[6]/2);
            fibarea[6] = d[6];
            sizemax[1] = sizemax[1] + par7[1]+gap[6];
        }
        else{
            hole[6] = hole[6] - (- fibarea[6]/2 + d[6]/2);
            fibarea[6] = d[6];
            sizemax[1] = sizemax[1] + par7[1]+gap[6];
        }
    }
    else{
        if (fabs(fibarea[6]/2-par7[4])>fabs(hole[6]-(par7[3]+gap[6]+sizemax[1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + par7[1]+gap[6];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }

    //八個目のキューブをおく。
//    std::cout << "*8th cube:" << std::endl;
    d[7] = fibarea[7]/2 + par8[4] - fabs(hole[7]-(par8[3]+gap[7]+sizemax[1]));
    if (d[7] >= 1){  // かさ上げ必要なし。
        if (hole[7] >= par8[3]+gap[7] + sizemax[1]){
            hole[7] = hole[7] + (- fibarea[7]/2 + d[7]/2);
            fibarea[7] = d[7];
            sizemax[1] = sizemax[1] + par8[1]+gap[7];
        }
        else{
            hole[7] = hole[7] - (- fibarea[7]/2 + d[7]/2);
            fibarea[7] = d[7];
            sizemax[1] = sizemax[1] + par8[1]+gap[7];
        }
    }
    else{
        if (fabs(fibarea[7]/2-par8[4])>fabs(hole[7]-(par8[3]+gap[7]+sizemax[1]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + par8[1]+gap[7];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }

//    std::cout << "\nhole info: " 
//              << hole[0] <<", "<< hole[1] <<", "<< hole[2] <<", "<< hole[3] <<", "
//              << hole[4] <<", "<< hole[5] <<", "<< hole[6] <<", "<< hole[7] <<std::endl;


    std::cout << "sizemax[0] : " << sizemax[0] <<", sizemax[1] : "<< sizemax[1] <<std::endl;

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
    float par1[5], par2[5], par3[5], par4[5];
    float par5[5], par6[5], par7[5], par8[5];
    //par[0]:xs, par[1]:ys, par[2]:xh, par[3]:yh, par[4]:r
    c1->GetSurf2(par1);
    c2->GetSurf2(par2);
    c3->GetSurf2(par3);
    c4->GetSurf2(par4);
    c5->GetSurf2(par5);
    c6->GetSurf2(par6);
    c7->GetSurf2(par7);
    c8->GetSurf2(par8);

    ///穴位置が縦の時と定義がちょっと異なる
    float cubelength = par1[0]+par2[0]+par3[0]+par4[0]+par5[0]+par6[0]+par7[0]+par8[0];
    float delta      = 82.3 - cubelength;
    float idelta[8];
    float gap[9];
    if (delta<=0){
        hole[0] = par1[2]; 
        hole[1] = par2[2] + par1[1];
        hole[2] = par3[2] + par1[1]+par2[1];
        hole[3] = par4[2] + par1[1]+par2[1]+par3[1];
        hole[4] = par5[2] + par1[1]+par2[1]+par3[1]+par4[1];
        hole[5] = par6[2] + par1[1]+par2[1]+par3[1]+par4[1]+par5[1];
        hole[6] = par7[2] + par1[1]+par2[1]+par3[1]+par4[1]+par5[1]+par6[1];
        hole[7] = par8[2] + par1[1]+par2[1]+par3[1]+par4[1]+par5[1]+par6[1]+par7[1];


        fibarea[0] = 2*par1[4];
        fibarea[1] = 2*par2[4];
        fibarea[2] = 2*par3[4];
        fibarea[3] = 2*par4[4];
        fibarea[4] = 2*par5[4];
        fibarea[5] = 2*par6[4];
        fibarea[6] = 2*par7[4];
        fibarea[7] = 2*par8[4];
        
        sizemax[0] =  par1[1]+par2[1]+par3[1]+par4[1]+par5[1]+par6[1]+par7[1]+par8[1];
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
        std::cout << "delta : " << delta << std::endl;
        std::cout << "after sort : " << idelta[0] << ", "<< idelta[1] << ", "<< idelta[2]
                  << ", " << idelta[3] << ", " << idelta[4] << ", " << idelta[5]
                  << ", " << idelta[6] << ", " << idelta[7] 
                  << std::endl;
        std::cout << "gap : " << gap[0] << ", "<< gap[1] << ", "<< gap[2]
                  << ", " << gap[3] << ", " << gap[4] << ", " << gap[5]
                  << ", " << gap[6] << ", " << gap[7] << ", " << gap[8]
                  << std::endl;


        //par[0]:xs, par[1]:ys, par[2]:xh, par[3]:yh, par[4]:r
        hole[0] = par1[2] + gap[0];
        hole[1] = par1[0] + gap[0] + par2[2] + gap[1];
        hole[2] = par1[0] + gap[0] + par2[0] + gap[1] + par3[2] + gap[2];
        hole[3] = par1[0] + gap[0] + par2[0] + gap[1] + par3[0] + gap[2] + par4[2] + gap[3];
        hole[4] = par1[0] + gap[0] + par2[0] + gap[1] + par3[0] + gap[2] + par4[0] + gap[3]
                + par5[2] + gap[4];
        hole[5] = par1[0] + gap[0] + par2[0] + gap[1] + par3[0] + gap[2] + par4[0] + gap[3]
                + par5[0] + gap[4] + par6[2] + gap[5];
        hole[6] = par1[0] + gap[0] + par2[0] + gap[1] + par3[0] + gap[2] + par4[0] + gap[3]
                + par5[0] + gap[4] + par6[0] + gap[5] + par7[2] + gap[6];
        hole[7] = par1[0] + gap[0] + par2[0] + gap[1] + par3[0] + gap[2] + par4[0] + gap[3]
                + par5[0] + gap[4] + par6[0] + gap[5] + par7[0] + gap[6] + par8[2] + gap[7];
        
        fibarea[0] = 2*par1[4];
        fibarea[1] = 2*par2[4];
        fibarea[2] = 2*par3[4];
        fibarea[3] = 2*par4[4];
        fibarea[4] = 2*par5[4];
        fibarea[5] = 2*par6[4];
        fibarea[6] = 2*par7[4];
        fibarea[7] = 2*par8[4];

        sizemax[0] = par1[0]+par2[0]+par3[0]+par4[0]+par5[0]
                    +par6[0]+par7[0]+par8[0]+delta  - gap[8];
    }   
    
    
    std::cout << "hole info: " 
              << hole[0] <<", "<< hole[1] <<", "<< hole[2] <<", "<< hole[3] <<", "
              << hole[4] <<", "<< hole[5] <<", "<< hole[6] <<", "<< hole[7] <<std::endl;
    std::cout << "sizemax[0]: " << sizemax[0] << "\n"<< std::endl;
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
    float par1[5], par2[5], par3[5], par4[5];
    float par5[5], par6[5], par7[5], par8[5];
    //par[0]:xs, par[1]:ys, par[2]:xh, par[3]:yh, par[4]:rに対応
    //各キューブのパラメータを取得する
    c1->GetSurf2(par1);
    c2->GetSurf2(par2);
    c3->GetSurf2(par3);
    c4->GetSurf2(par4);
    c5->GetSurf2(par5);
    c6->GetSurf2(par6);
    c7->GetSurf2(par7);
    c8->GetSurf2(par8);
    
    
    float cubelength = par1[0]+par2[0]+par3[0]+par4[0]+par5[0]+par6[0]+par7[0]+par8[0];
    float delta      = 82.3 - cubelength;
    float idelta[8];
    float gap[9];
    if (delta<=0){
        sizemax[1] = cubelength;
        std::cout << "cubelength = " << cubelength << ", " << std::endl;
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
        std::cout << "delta : " << delta << std::endl;
        std::cout << "after sort : " << idelta[0] << ", "<< idelta[1] << ", "<< idelta[2]
                  << ", " << idelta[3] << ", " << idelta[4] << ", " << idelta[5]
                  << ", " << idelta[6] << ", " << idelta[7] 
                  << std::endl;
        std::cout << "gap : " << gap[0] << ", "<< gap[1] << ", "<< gap[2]
                  << ", " << gap[3] << ", " << gap[4] << ", " << gap[5]
                  << ", " << gap[6] << ", " << gap[7] << ", " << gap[8]
                  << std::endl;
    
    }
        //par[0]:xs, par[1]:ys, par[2]:xh, par[3]:yh, par[4]:r

    float d[8];
    float alpha[0];

    //一個めのキューブをおく。
//    std::cout << "*1st cube:" << std::endl;
    d[0] = fibarea[0]/2 + par1[4] - fabs(hole[0]-(gap[0]+par1[2]));
    if (d[0] >= 1){  // かさ上げ必要なし。
        sizemax[1] = par1[0]+gap[0];
        if (hole[0] >= (gap[0]+par1[2])){
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
//    std::cout << "*2nd cube:" << std::endl;
    d[1] = fibarea[1]/2 + par2[4] - fabs(hole[1]-(gap[1]+sizemax[1]+par2[2]));
    if (d[1] >= 1){  // かさ上げ必要なし。
        if (hole[1] >= gap[1] + sizemax[1]+par2[2]){
            hole[1] = hole[1] + (- fibarea[1]/2 + d[1]/2);
            fibarea[1] = d[1];
            sizemax[1] = sizemax[1] + par2[0]+gap[1];
        }
        else{
            hole[1] = hole[1] - (- fibarea[1]/2 + d[1]/2);
            fibarea[1] = d[1];
            sizemax[1] = sizemax[1] + par2[0]+gap[1];
        }
    }
    else{
        if (fabs(fibarea[1]/2-par2[4])>fabs(hole[1]-(gap[1]+sizemax[1]+par2[2]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + par2[0]+gap[1];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }


    //三個目のキューブをおく。
//    std::cout << "*3rd cube:" << std::endl;
    d[2] = fibarea[2]/2 + par3[4] - fabs(hole[2]-(gap[2]+sizemax[1]+par3[2]));
    if (d[2] >= 1){  // かさ上げ必要なし。
        if (hole[2] >= gap[2] + sizemax[1]+par3[2]){
            hole[2] = hole[2] + (- fibarea[2]/2 + d[2]/2);
            fibarea[2] = d[2];
            sizemax[1] = sizemax[1] + par3[0]+gap[2];
        }
        else{
            hole[2] = hole[2] - (- fibarea[2]/2 + d[2]/2);
            fibarea[2] = d[2];
            sizemax[1] = sizemax[1] + par3[0]+gap[2];
        }
    }
    else{
        if (fabs(fibarea[2]/2-par3[4])>fabs(hole[2]-(gap[2]+sizemax[1]+par3[2]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + par3[0]+gap[2];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }
    

    //四個目のキューブをおく。
//    std::cout << "*4th cube:" << std::endl;
    d[3] = fibarea[3]/2 + par4[4] - fabs(hole[3]-(gap[3]+sizemax[1]+par4[2]));
    if (d[3] >= 1){  // かさ上げ必要なし。
        if (hole[3] >= gap[3] + sizemax[1]+par4[2]){
            hole[3] = hole[3] + (- fibarea[3]/2 + d[3]/2);
            fibarea[3] = d[3];
            sizemax[1] = sizemax[1] + par4[0]+gap[3];
        }
        else{
            hole[3] = hole[3] - (- fibarea[3]/2 + d[3]/2);
            fibarea[3] = d[3];
            sizemax[1] = sizemax[1] + par4[0]+gap[3];
        }
    }
    else{
        if (fabs(fibarea[3]/2-par4[4])>fabs(hole[3]-(gap[3]+sizemax[1]+par4[2]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + par4[0]+gap[3];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }
    
    //五個目のキューブをおく。
//    std::cout << "*5th cube:" << std::endl;
    d[4] = fibarea[4]/2 + par5[4] - fabs(hole[4]-(gap[4]+sizemax[1]+par5[2]));
    if (d[4] >= 1){  // かさ上げ必要なし。
        if (hole[4] >= gap[4] + sizemax[1]+par5[2]){
            hole[4] = hole[4] + (- fibarea[4]/2 + d[4]/2);
            fibarea[4] = d[4];
            sizemax[1] = sizemax[1] + par5[0]+gap[4];
        }
        else{
            hole[4] = hole[4] - (- fibarea[4]/2 + d[4]/2);
            fibarea[4] = d[4];
            sizemax[1] = sizemax[1] + par5[0]+gap[4];
        }
    }
    else{
        if (fabs(fibarea[4]/2-par5[4])>fabs(hole[4]-(gap[4]+sizemax[1]+par5[2]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + par5[0]+gap[4];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }
    
    //六個目のキューブをおく。
//    std::cout << "*6th cube:" << std::endl;
    d[5] = fibarea[5]/2 + par6[4] - fabs(hole[5]-(gap[5]+sizemax[1]+par6[2]));
    if (d[5] >= 1){  // かさ上げ必要なし。
        if (hole[5] >= gap[5] + sizemax[1]+par6[2]){
            hole[5] = hole[5] + (- fibarea[5]/2 + d[5]/2);
            fibarea[5] = d[5];
            sizemax[1] = sizemax[1] + par6[0]+gap[5];
        }
        else{
            hole[5] = hole[5] - (- fibarea[5]/2 + d[5]/2);
            fibarea[5] = d[5];
            sizemax[1] = sizemax[1] + par6[0]+gap[5];
        }
    }
    else{
        if (fabs(fibarea[5]/2-par6[4])>fabs(hole[5]-(gap[5]+sizemax[1]+par6[2]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + par6[0]+gap[5];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }

    //七個目のキューブをおく。
//    std::cout << "*7th cube:" << std::endl;
    d[6] = fibarea[6]/2 + par7[4] - fabs(hole[6]-(gap[6]+sizemax[1]+par7[2]));
    if (d[6] >= 1){  // かさ上げ必要なし。
        if (hole[6] >= gap[6] + sizemax[1]+par7[2]){
            hole[6] = hole[6] + (- fibarea[6]/2 + d[6]/2);
            fibarea[6] = d[6];
            sizemax[1] = sizemax[1] + par7[0]+gap[6];
        }
        else{
            hole[6] = hole[6] - (- fibarea[6]/2 + d[6]/2);
            fibarea[6] = d[6];
            sizemax[1] = sizemax[1] + par7[0]+gap[6];
        }
    }
    else{
        if (fabs(fibarea[6]/2-par7[4])>fabs(hole[6]-(gap[6]+sizemax[1]+par7[2]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + par7[0]+gap[6];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }

    //八個目のキューブをおく。
//    std::cout << "*8th cube:" << std::endl;
    d[7] = fibarea[7]/2 + par8[4] - fabs(hole[7]-(gap[7]+sizemax[1]+par8[2]));
    if (d[7] >= 1){  // かさ上げ必要なし。
        if (hole[7] >= gap[7] + sizemax[1]+par8[2]){
            hole[7] = hole[7] + (- fibarea[7]/2 + d[7]/2);
            fibarea[7] = d[7];
            sizemax[1] = sizemax[1] + par8[0]+gap[7];
        }
        else{
            hole[7] = hole[7] - (- fibarea[7]/2 + d[7]/2);
            fibarea[7] = d[7];
            sizemax[1] = sizemax[1] + par8[0]+gap[7];
        }
    }
    else{
        if (fabs(fibarea[7]/2-par8[4])>fabs(hole[7]-(gap[7]+sizemax[1]+par8[2]))){
            //hole[1]はそのまま
            //fibarea[1]もそのまま
            sizemax[1] =sizemax[1] + par8[0]+gap[7];
        }
        else{
            sizemax[1] =100;
            return;
        }
    }

//    std::cout << "\nhole info: " 
//              << hole[0] <<", "<< hole[1] <<", "<< hole[2] <<", "<< hole[3] <<", "
//              << hole[4] <<", "<< hole[5] <<", "<< hole[6] <<", "<< hole[7] <<std::endl;


    std::cout << "sizemax[0] : " << sizemax[0] <<", sizemax[1] : "<< sizemax[1] <<std::endl;

}





Cube::~Cube()

{
}
