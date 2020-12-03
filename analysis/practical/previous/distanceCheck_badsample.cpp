#include <iostream>
#include <fstream>

void distanceCheck_badsample(){

std::ifstream fin;
fin.open("distanceCheck_badsample.txt");

int n = 6;
std::string saveName[n];
double xdummy[n];
double ydummy[n];
double radius[n];
double xhole[n];
double yhole[n];
double xsize[n];
double ysize[n];
double surface[n];
double xhole_size[n];
double yhole_size[n];

    for(Int_t j=0; j<n;j++){
        fin >> saveName[j] >> xdummy[j] >> ydummy[j]
            >> radius[j] >> xhole[j] >> yhole[j]
            >> xsize[j] >> ysize[j];
        surface[j] = j;
        xhole_size[j]=xhole[j]/xsize[j];
        yhole_size[j]=yhole[j]/ysize[j];
     }
        xhole_size[1]=yhole[1]/ysize[1];
        xhole_size[2]=yhole[2]/ysize[2];
        yhole_size[1]=xhole[1]/xsize[1];
        yhole_size[2]=xhole[2]/xsize[2];

    TGraph *gx = new TGraph(n,surface,xhole_size );
    gx->SetMarkerStyle(8);
    TGraph *gy = new TGraph(n,surface,yhole_size );
    gy->SetMarkerStyle(8);
    gx->SetMarkerColor(2);
    gx->Draw("ap");
    //gy->Draw("p");


}
