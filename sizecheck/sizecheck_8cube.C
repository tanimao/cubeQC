#include <iostream>
#include <fstream>
#include <math.h>

#include <cmath>

#include <vector>
//#include "classCube.cc"

#include <stdlib.h>
#include <time.h>

void sizecheck_8cube()
{
    TH2D * h = new TH2D ("h", "nogisu vs. system; nogisu[mm]; system[pix]",
            60,85-3.69,86.5-3.69, 200, 81.3, 82.8);//650*8*0.0156, 670*8*0.0156);
    std::ifstream ifsys ("sizeoutput201224_2.txt");
    std::ifstream ifnog ("sizenogisu201224_2.txt");

    double hsys[64], wsys[64], dsys[64];
    double tatesys[8]={0., 0., 0., 0., 0., 0., 0., 0.};
    double yokosys[8]={0., 0., 0., 0., 0., 0., 0., 0.};
    double tatesys2[8]={0., 0., 0., 0., 0., 0., 0., 0.};
    double yokosys2[8]={0., 0., 0., 0., 0., 0., 0., 0.};
    double tatenog[16], yokonog[16];
    int cubenum;

    for (int i=0; i<64; i++){
        ifsys >> cubenum >> hsys[i] >> wsys[i] >> dsys[i] ;
    }

    for (int ii=0; ii<16; ii++){
        ifnog >> tatenog[ii] >> yokonog[ii] ;
    }

    for (int j=0; j<8; j++){
        for(int jj= 0; jj<8; jj++){

            tatesys[j] = tatesys[j]+ dsys[jj+8*j];
            yokosys[j] = yokosys[j]+ wsys[jj+8*j];

            tatesys2[j] = tatesys2[j]+ dsys[8*jj+j];
            yokosys2[j] = yokosys2[j]+ wsys[8*jj+j];
        }
        h ->Fill(tatenog[j]-3.69, tatesys[j]*0.0156);
        h ->Fill(yokonog[j]-3.69, yokosys[j]*0.0156);

        h ->Fill(tatenog[8+j]-3.69, tatesys2[j]*0.0156);
        h ->Fill(yokonog[8+j]-3.69, yokosys2[j]*0.0156);
    }

    h->SetMarkerStyle(8);
    h->SetMarkerSize(0.5);
    h->Draw();
}

    
