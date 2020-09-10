/*


*/
#include "classCube.h"
#include <vector>
#include <cmath>
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


void CubeArrange1(Cube *c1, Cube *c2, Cube *c3, Cube *c4,
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
    
    sizemax[0]    =  hole[7]-par8[3]+par8[1];
    
    
    
    std::cout << "\nhole info: " 
              << hole[0] <<", "<< hole[1] <<", "<< hole[2] <<", "<< hole[3] <<", "
              << hole[4] <<", "<< hole[5] <<", "<< hole[6] <<", "<< hole[7] <<std::endl;
    std::cout << "sizemax[0]: " << sizemax[0] << "\n"<< std::endl;
}


void CubeArrange2(Cube *c1, Cube *c2, Cube *c3, Cube *c4,
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

    float d[8];
    float alpha[0];

    //一個めのキューブをおく。
    std::cout << "*1st cube:" << std::endl;
    d[0] = fibarea[0]/2 + par1[4] - fabs(hole[0]-par1[3]);
    if (d[0] >= 1){  // かさ上げ必要なし。
        sizemax[1] = par1[1];
        if (hole[0] >= par1[3]){
            hole[0] = hole[0] + (- fibarea[0]/2 + d[0]/2);
            fibarea[0] = d[0];
        }
        else {
            hole[0] = hole[0] - (- fibarea[0]/2 + d[0]/2);
            fibarea[0] = d[0];
        }
    }
    else{   
        alpha[0] = 1 - d[0];
        std::cout << "*****d is smaller than 1mm, alpha:" << alpha[0] << std::endl;
        //ファイバが入る分だけかさ増し
        if (hole[0] >= par1[3]){
            hole[0] = hole[0] - fibarea[0]/2 + 0.5;
            sizemax[1] = par1[1] + alpha[0]; //sizemax[1]は今（２列目）の現段階の高さとした。
            fibarea[0] =1;
        }
        else {
            hole[0] = par1[3] - par1[4] + 0.5;
            sizemax[0] = sizemax[0] + alpha[0]; //sizemax[0]は前（１列め）の全体の高さ。
            sizemax[1] = par1[1];
            fibarea[0] =1;
            hole[1] = hole[1] + alpha[0];
            hole[2] = hole[2] + alpha[0];
            hole[3] = hole[3] + alpha[0];
            hole[4] = hole[4] + alpha[0];
            hole[5] = hole[5] + alpha[0];
            hole[6] = hole[6] + alpha[0];
            hole[7] = hole[7] + alpha[0];
        }
    }

    //二個目のキューブをおく。
    std::cout << "*2nd cube:" << std::endl;
    d[1] = fibarea[1]/2 + par2[4] - fabs(hole[1]-(par2[3]+sizemax[1]));
    if (d[1] >= 1){  // かさ上げ必要なし。
        if (hole[1] >= par2[3] + sizemax[1]){
            hole[1] = hole[1] + (- fibarea[1]/2 + d[1]/2);
            fibarea[1] = d[1];
            sizemax[1] = sizemax[1] + par2[1];
        }
        else{
            hole[1] = hole[1] - (- fibarea[1]/2 + d[1]/2);
            fibarea[1] = d[1];
            sizemax[1] = sizemax[1] + par2[1];
        }
    }
    else{
        alpha[1] = 1-d[1];
        std::cout << "*****d is smaller than 1mm, alpha:" << alpha[1] << std::endl;
        if (hole[1] >= par2[3] + sizemax[1]){
            hole[1] = hole[1] - fibarea[1]/2 + 0.5;
            sizemax[1] = sizemax[1] + par2[1] + alpha[1];
            fibarea[1] = 1;
        }
        else{
            hole[1] = (par2[3] + sizemax[1]) - par2[4] +0.5;
            sizemax[0] = sizemax[0] + alpha[1];
            sizemax[1] = sizemax[1] + par2[1];
            fibarea[1] = 1;
            hole[2] = hole[2] + alpha[1];
            hole[3] = hole[3] + alpha[1];
            hole[4] = hole[4] + alpha[1];
            hole[5] = hole[5] + alpha[1];
            hole[6] = hole[6] + alpha[1];
            hole[7] = hole[7] + alpha[1];
        }
    }


    //三個目のキューブをおく。
    std::cout << "*3rd cube:" << std::endl;
    d[2] = fibarea[2]/2 + par3[4] - fabs(hole[2]-(par3[3]+sizemax[1]));
    if (d[2] >= 1){  // かさ上げ必要なし。
        if (hole[2] >= par3[3] + sizemax[1]){
            hole[2] = hole[2] + (- fibarea[2]/2 + d[2]/2);
            fibarea[2] = d[2];
            sizemax[1] = sizemax[1] + par3[1];
        }
        else{
            hole[2] = hole[2] - (- fibarea[2]/2 + d[2]/2);
            fibarea[2] = d[2];
            sizemax[1] = sizemax[1] + par3[1];
        }
    }
    else{
        alpha[2] = 1-d[2];
        std::cout << "*****d is smaller than 1mm, alpha:" << alpha[2] << std::endl;
        if (hole[2] >= par3[3] + sizemax[1]){
            hole[2] = hole[2] - fibarea[2]/2 + 0.5;
            sizemax[1] = sizemax[1] + par3[1] + alpha[2];
            fibarea[2] = 1;
        }
        else{
            hole[2] = (par3[3] + sizemax[1]) - par3[4] +0.5;
            sizemax[0] = sizemax[0] + alpha[2];
            sizemax[1] = sizemax[1] + par3[1];
            fibarea[2] = 1;
            hole[3] = hole[3] + alpha[2];
            hole[4] = hole[4] + alpha[2];
            hole[5] = hole[5] + alpha[2];
            hole[6] = hole[6] + alpha[2];
            hole[7] = hole[7] + alpha[2];
        }
    }
    

    //四個目のキューブをおく。
    std::cout << "*4th cube:" << std::endl;
    d[3] = fibarea[3]/2 + par4[4] - fabs(hole[3]-(par4[3]+sizemax[1]));
    if (d[3] >= 1){  // かさ上げ必要なし。
        if (hole[3] >= par4[3] + sizemax[1]){
            hole[3] = hole[3] + (- fibarea[3]/2 + d[3]/2);
            fibarea[3] = d[3];
            sizemax[1] = sizemax[1] + par4[1];
        }
        else{
            hole[3] = hole[3] - (- fibarea[3]/2 + d[3]/2);
            fibarea[3] = d[3];
            sizemax[1] = sizemax[1] + par4[1];
        }
    }
    else{
        alpha[3] = 1-d[3];
        std::cout << "*****d is smaller than 1mm, alpha:" << alpha[3] << std::endl;
        if (hole[3] >= par4[3] + sizemax[1]){
            hole[3] = hole[3] - fibarea[3]/2 + 0.5;
            sizemax[1] = sizemax[1] + par4[1] + alpha[3];
            fibarea[3] = 1;
        }
        else{
            hole[3] = (par4[3] + sizemax[1]) - par4[4] +0.5;
            sizemax[0] = sizemax[0] + alpha[3];
            sizemax[1] = sizemax[1] + par4[1];
            fibarea[3] = 1;
            hole[4] = hole[4] + alpha[3];
            hole[5] = hole[5] + alpha[3];
            hole[6] = hole[6] + alpha[3];
            hole[7] = hole[7] + alpha[3];
        }
    }
    
    //五個目のキューブをおく。
    std::cout << "*5th cube:" << std::endl;
    d[4] = fibarea[4]/2 + par5[4] - fabs(hole[4]-(par5[3]+sizemax[1]));
    if (d[4] >= 1){  // かさ上げ必要なし。
        if (hole[4] >= par5[3] + sizemax[1]){
            hole[4] = hole[4] + (- fibarea[4]/2 + d[4]/2);
            fibarea[4] = d[4];
            sizemax[1] = sizemax[1] + par5[1];
        }
        else{
            hole[4] = hole[4] - (- fibarea[4]/2 + d[4]/2);
            fibarea[4] = d[4];
            sizemax[1] = sizemax[1] + par5[1];
        }
    }
    else{
        alpha[4] = 1-d[4];
        std::cout << "*****d is smaller than 1mm, alpha:" << alpha[4] << std::endl;
        if (hole[4] >= par5[3] + sizemax[1]){
            hole[4] = hole[4] - fibarea[4]/2 + 0.5;
            sizemax[1] = sizemax[1] + par5[1] + alpha[4];
            fibarea[4] = 1;
        }
        else{
            hole[4] = (par5[3] + sizemax[1]) - par5[4] +0.5;
            sizemax[0] = sizemax[0] + alpha[4];
            sizemax[1] = sizemax[1] + par5[1];
            fibarea[4] = 1;
            hole[5] = hole[5] + alpha[4];
            hole[6] = hole[6] + alpha[4];
            hole[7] = hole[7] + alpha[4];
        }
    }
    
    //六個目のキューブをおく。
    std::cout << "*6th cube:" << std::endl;
    d[5] = fibarea[5]/2 + par6[4] - fabs(hole[5]-(par6[3]+sizemax[1]));
    if (d[5] >= 1){  // かさ上げ必要なし。
        if (hole[5] >= par6[3] + sizemax[1]){
            hole[5] = hole[5] + (- fibarea[5]/2 + d[5]/2);
            fibarea[5] = d[5];
            sizemax[1] = sizemax[1] + par6[1];
        }
        else{
            hole[5] = hole[5] - (- fibarea[5]/2 + d[5]/2);
            fibarea[5] = d[5];
            sizemax[1] = sizemax[1] + par6[1];
        }
    }
    else{
        alpha[5] = 1-d[5];
        std::cout << "*****d is smaller than 1mm, alpha:" << alpha[5] << std::endl;
        if (hole[5] >= par6[3] + sizemax[1]){
            hole[5] = hole[5] - fibarea[5]/2 + 0.5;
            sizemax[1] = sizemax[1] + par6[1] + alpha[5];
            fibarea[5] = 1;
        }
        else{
            hole[5] = (par6[3] + sizemax[1]) - par6[4] +0.5;
            sizemax[0] = sizemax[0] + alpha[5];
            sizemax[1] = sizemax[1] + par6[1];
            fibarea[5] = 1;
            hole[6] = hole[6] + alpha[5];
            hole[7] = hole[7] + alpha[5];
        }
    }

    //七個目のキューブをおく。
    std::cout << "*7th cube:" << std::endl;
    d[6] = fibarea[6]/2 + par7[4] - fabs(hole[6]-(par7[3]+sizemax[1]));
    if (d[6] >= 1){  // かさ上げ必要なし。
        if (hole[6] >= par7[3] + sizemax[1]){
            hole[6] = hole[6] + (- fibarea[6]/2 + d[6]/2);
            fibarea[6] = d[6];
            sizemax[1] = sizemax[1] + par7[1];
        }
        else{
            hole[6] = hole[6] - (- fibarea[6]/2 + d[6]/2);
            fibarea[6] = d[6];
            sizemax[1] = sizemax[1] + par7[1];
        }
    }
    else{
        alpha[6] = 1-d[6];
        std::cout << "*****d is smaller than 1mm, alpha:" << alpha[6] << std::endl;
        if (hole[6] >= par7[3] + sizemax[1]){
            hole[6] = hole[6] - fibarea[6]/2 + 0.5;
            sizemax[1] = sizemax[1] + par7[1] + alpha[6];
            fibarea[6] = 1;
        }
        else{
            hole[6] = (par7[3] + sizemax[1]) - par7[4] +0.5;
            sizemax[0] = sizemax[0] + alpha[6];
            sizemax[1] = sizemax[1] + par7[1];
            fibarea[6] = 1;
            hole[7] = hole[7] + alpha[6];
        }
    }

    //八個目のキューブをおく。
    std::cout << "*8th cube:" << std::endl;
    d[7] = fibarea[7]/2 + par8[4] - fabs(hole[7]-(par8[3]+sizemax[1]));
    if (d[7] >= 1){  // かさ上げ必要なし。
        if (hole[7] >= par8[3] + sizemax[1]){
            hole[7] = hole[7] + (- fibarea[7]/2 + d[7]/2);
            fibarea[7] = d[7];
            sizemax[1] = sizemax[1] + par8[1];
        }
        else{
            hole[7] = hole[7] - (- fibarea[7]/2 + d[7]/2);
            fibarea[7] = d[7];
            sizemax[1] = sizemax[1] + par8[1];
        }
    }
    else{
        alpha[7] = 1-d[7];
        std::cout << "*****d is smaller than 1mm, alpha:" << alpha[7] << std::endl;
        if (hole[7] >= par8[3] + sizemax[1]){
            hole[7] = hole[7] - fibarea[7]/2 + 0.5;
            sizemax[1] = sizemax[1] + par8[1] + alpha[7];
            fibarea[7] = 1;
        }
        else{
            hole[7] = (par8[3] + sizemax[1]) - par8[4] +0.5;
            sizemax[0] = sizemax[0] + alpha[7];
            sizemax[1] = sizemax[1] + par8[1];
            fibarea[7] = 1;
        }
    }

    std::cout << "\nhole info: " 
              << hole[0] <<", "<< hole[1] <<", "<< hole[2] <<", "<< hole[3] <<", "
              << hole[4] <<", "<< hole[5] <<", "<< hole[6] <<", "<< hole[7] <<std::endl;


    std::cout << "sizemax[0] : " << sizemax[0] <<", sizemax[1] : "<< sizemax[1] <<std::endl;

}

Cube::~Cube()
{
}
