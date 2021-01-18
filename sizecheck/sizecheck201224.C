#include <iostream>
#include <fstream>
#include <math.h>

#include <cmath>

#include <vector>
//#include "classCube.cc"

#include <stdlib.h>
#include <time.h>

void sizecheck201224()
{
    TH2D * h = new TH2D ("h", 
            "nogisu vs. system; nogisu[mm]; system[pix]",
            80,10.1,10.4, 200, 10.1/0.0156, 10.4/0.0156);//650*0.0156, 670*0.0156);
    std::ifstream ifsys ("data201224cor.txt");
    std::ifstream ifnog ("xsizeysizenogisu201224.txt");

    double xsys, ysys;
    double xnog, ynog;
    int cube1, cube2;
    int surf1, surf2;

    for (int i=0; i<60; i++){
        ifsys >> cube1 >> surf1 >> xsys >> ysys ;
        ifnog >> cube2 >> surf2 >> xnog >> ynog ;
        h ->Fill(xnog, xsys);//*0.0156);
        h ->Fill(ynog, ysys);//*0.0156);
    }
    h->SetMarkerStyle(8);
    h->SetMarkerSize(0.5);
    h->Draw();
}

    
