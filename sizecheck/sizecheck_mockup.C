#include <iostream>
#include <fstream>
#include <math.h>

#include <cmath>

#include <vector>
//#include "classCube.cc"

#include <stdlib.h>
#include <time.h>

void sizecheck_mockup()
{
    TH2D * h = new TH2D ("h", "nogisu vs. system; nogisu[mm]; system[pix]",80,10.1,10.4, 200, 650*0.0156, 670*0.0156);
    //TGraphErrors * gr = new TGraphErrors(36*2);
    std::ifstream ifsys ("sizeoutput210118_size.txt");
    std::ifstream ifnog ("xsizeysizenogisu210118.txt");

    double xsys[36], ysys[36];
    double sys[36*2], syserror[36*2];
    double xnogmin[36], xnogmax[36], xnogmean[36], ynogmin[36], ynogmax[36], ynogmean[36] ;
    double nogmean[36*2], nogerror[36*2] ;
    int cube1, cube2;
    int surf1, surf2;

    for (int i=0; i<36; i++){
        ifsys >> xsys[i] >> ysys[i] ;
        ifnog >> xnogmin[i] >> xnogmax[i] >> ynogmin[i] >> ynogmax[i] ;
        xnogmean[i] = (xnogmin[i] + xnogmax[i])/2;
        ynogmean[i] = (ynogmin[i] + ynogmax[i])/2;
        nogmean[2*i] = xnogmean[i];
        nogmean[2*i+1] = ynogmean[i];
        nogerror[2*i] = xnogmax[i] - xnogmean[i];
        nogerror[2*i+1] = ynogmax[i] - ynogmean[i];
        sys[2*i] = xsys[i];
        sys[2*i+1] = ysys[i];
        syserror[2*i] = 1;
        syserror[2*i+1] = 1;
        
        
        //h ->Fill(xnog, xsys);//*0.0156);
        //h ->Fill(ynog, ysys);//*0.0156);
    }
    
    TGraphErrors *gr = new TGraphErrors (36*2, nogmean, sys, nogerror, syserror);
    gr->SetMarkerStyle(8);
    gr->SetMarkerSize(0.5);
    gr->Draw("ap");
    TFile *f = new TFile ("mockup.root", "recreate");
    gr->Write();
    f->Close();
}

    
