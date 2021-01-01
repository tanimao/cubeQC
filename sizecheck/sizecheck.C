#include <iostream>
#include <fstream>
#include <math.h>

#include <cmath>

#include <vector>
//#include "classCube.cc"

#include <stdlib.h>
#include <time.h>

void sizecheck()
{
    TH2D * h = new TH2D ("h", "nogisu vs. system; nogisu[mm]; system[pix]",60,13.7-3.69,14.3-3.69, 200, 650*0.0155, 670*0.0155);
    std::ifstream ifsys ("sizeoutput.txt");
    std::ifstream ifnog ("sizenogisu.txt");

    double hsys, wsys, dsys;
    double hnog, wnog, dnog;

    for (int i=0; i<40; i++){
        ifsys >> hsys >> wsys >> dsys ;
        ifnog >> hnog >> wnog >> dnog ;
        h ->Fill(hnog-3.69, hsys*0.0155);
        h ->Fill(wnog-3.69, dsys*0.0155);
        h ->Fill(dnog-3.69, wsys*0.0155);
    }
    h->SetMarkerStyle(8);
    h->SetMarkerSize(0.5);
    h->Draw();
}

    
