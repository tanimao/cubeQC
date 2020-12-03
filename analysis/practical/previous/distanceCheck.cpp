#include <iostream>
#include <fstream>

void distanceCheck(){

std::ifstream fin;
fin.open("../../files/cube_distance0930.txt");

int n = 5;
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

TGraph *gdistancex = new TGraph();
TGraph *gdistancey = new TGraph();

    for(Int_t j=0; j<n;j++){
        fin >> saveName[j] >> xdummy[j] >> ydummy[j]
            >> radius[j] >> xhole[j] >> yhole[j]
            >> xsize[j] >> ysize[j];
        surface[j] = j;
        xhole_size[j]=xhole[j]/xsize[j];
        yhole_size[j]=yhole[j]/ysize[j];
        
    }
    TGraph *gr1 = new TGraph(n,surface,xhole_size );
    gr1->SetMarkerStyle(8);
    
    gdistancex->SetPoint(0, 150, xsize[0]);
    gdistancey->SetPoint(0, 150, ysize[0]);
    for(int j=0; j<n;j++){
        fin >> saveName[j] >> xdummy[j] >> ydummy[j]
            >> radius[j] >> xhole[j] >> yhole[j]
            >> xsize[j] >> ysize[j];
        surface[j] = j;
        xhole_size[j]=xhole[j]/xsize[j];
        yhole_size[j]=yhole[j]/ysize[j];
    }
    TGraph *gr2 = new TGraph(n,surface,xhole_size );
    gr2->SetMarkerStyle(22);

    
    gdistancex->SetPoint(1, 250, xsize[0]);
    gdistancey->SetPoint(1, 250, ysize[0]);
    
    for(int j=0; j<n;j++){
        fin >> saveName[j] >> xdummy[j] >> ydummy[j]
            >> radius[j] >> xhole[j] >> yhole[j]
            >> xsize[j] >> ysize[j];
        surface[j] = j;
        xhole_size[j]=xhole[j]/xsize[j];
        yhole_size[j]=yhole[j]/ysize[j];
    }
    TGraph *gr3 = new TGraph(n,surface,xhole_size );
    gr3->SetMarkerStyle(23);

    
    gdistancex->SetPoint(2, 300, xsize[0]);
    gdistancey->SetPoint(2, 300, ysize[0]);
    
    for(int j=0; j<n;j++){
        fin >> saveName[j] >> xdummy[j] >> ydummy[j]
            >> radius[j] >> xhole[j] >> yhole[j]
            >> xsize[j] >> ysize[j];
        surface[j] = j;
        xhole_size[j]=xhole[j]/xsize[j];
        yhole_size[j]=yhole[j]/ysize[j];
    }
    TGraph *gr4 = new TGraph(n,surface,xhole_size );
    gr4->SetMarkerStyle(24);

    
    gdistancex->SetPoint(3, 320, xsize[0]);
    gdistancey->SetPoint(3, 320, ysize[0]);
    
    for(int j=0; j<n;j++){
        fin >> saveName[j] >> xdummy[j] >> ydummy[j]
            >> radius[j] >> xhole[j] >> yhole[j]
            >> xsize[j] >> ysize[j];
        surface[j] = j;
        xhole_size[j]=xhole[j]/xsize[j];
        yhole_size[j]=yhole[j]/ysize[j];
    }
    TGraph *gr5 = new TGraph(n,surface,xhole_size );
    gr5->SetMarkerStyle(8);

    
    gdistancex->SetPoint(4, 350, xsize[0]);
    gdistancey->SetPoint(4, 350, ysize[0]);
    
    for(int j=0; j<n;j++){
        fin >> saveName[j] >> xdummy[j] >> ydummy[j]
            >> radius[j] >> xhole[j] >> yhole[j]
            >> xsize[j] >> ysize[j];
        surface[j] = j;
        xhole_size[j]=xhole[j]/xsize[j];
        yhole_size[j]=yhole[j]/ysize[j];
    }
    TGraph *gr6 = new TGraph(n,surface,xhole_size );
    gr6->SetMarkerStyle(8);

    
    gdistancex->SetPoint(5, 400, xsize[0]);
    gdistancey->SetPoint(5, 400, ysize[0]);
    
    for(int j=0; j<n;j++){
        fin >> saveName[j] >> xdummy[j] >> ydummy[j]
            >> radius[j] >> xhole[j] >> yhole[j]
            >> xsize[j] >> ysize[j];
        surface[j] = j;
        xhole_size[j]=xhole[j]/xsize[j];
        yhole_size[j]=yhole[j]/ysize[j];
    }
    TGraph *gr7 = new TGraph(n,surface,xhole_size );
    gr7->SetMarkerStyle(8);

    
    gdistancex->SetPoint(6, 450, xsize[0]);
    gdistancey->SetPoint(6, 450, ysize[0]);
    
    for(int j=0; j<n;j++){
        fin >> saveName[j] >> xdummy[j] >> ydummy[j]
            >> radius[j] >> xhole[j] >> yhole[j]
            >> xsize[j] >> ysize[j];
        surface[j] = j;
        xhole_size[j]=xhole[j]/xsize[j];
        yhole_size[j]=yhole[j]/ysize[j];
    }
    TGraph *gr8 = new TGraph(n,surface,xhole_size );
    gr8->SetMarkerStyle(28);
    
    gdistancex->SetPoint(7, 500, xsize[0]);
    gdistancey->SetPoint(7, 500, ysize[0]);
    

    gr1->SetMarkerColor(2);
    gr2->SetMarkerColor(1);
    gr3->SetMarkerColor(3);
    gr4->SetMarkerColor(2);
    gr5->SetMarkerColor(6);
    gr6->SetMarkerColor(7);
    gr7->SetMarkerColor(8);
    gr8->SetMarkerColor(1);
    gr1->Draw("AP");
    gr2->Draw("P");
    gr3->Draw("P");
    gr4->Draw("P");
    gr5->Draw("P");
    gr6->Draw("P");
    gr7->Draw("P");
    gr8->Draw("P");

TCanvas *c2 = new TCanvas("c2","c2");
    gdistancex->SetMarkerStyle(8);
    gdistancex->Draw("AP");
    gdistancey->SetMarkerStyle(8);
    gdistancey->Draw("P");
    gdistancey->SetMarkerColor(2);
    
/*
std::ifstream f;
f.open("distanceCheck_badsample2.txt");

int n_ = 6;
std::string saveName_[n_];
double xdummy_[n_];
double ydummy_[n_];
double radius_[n_];
double xhole_[n_];
double yhole_[n_];
double xsize_[n_];
double ysize_[n_];
double surface_[n_];
double xhole_size_[n_];
double yhole_size_[n_];

    for(Int_t j=0; j<n_;j++){
        f >> saveName_[j] >> xdummy_[j] >> ydummy_[j]
            >> radius_[j] >> xhole_[j] >> yhole_[j]
            >> xsize_[j] >> ysize_[j];
        surface_[j] = j;
        xhole_size_[j]=xhole_[j]/xsize_[j];
        yhole_size_[j]=yhole_[j]/ysize_[j];
     }
        xhole_size_[1]=yhole_[1]/ysize_[1];
        xhole_size_[2]=yhole_[2]/ysize_[2];
        yhole_size_[1]=xhole_[1]/xsize_[1];
        yhole_size_[2]=xhole_[2]/xsize_[2];

    TGraph *gx = new TGraph(n_,surface_,xhole_size_ );
    gx->SetMarkerStyle(35);
    TGraph *gy = new TGraph(n_,surface_,yhole_size_);
    gy->SetMarkerStyle(1);
    gx->SetMarkerColor(1);
    gx->SetMarkerSize(5);
    gx->Draw("P");
    gy->Draw("P");


    TLegend *leg = new TLegend(0.6,0.1,0.9,0.4);
    leg->AddEntry(gr1,"15cm","p");
    leg->AddEntry(gr2,"25cm","p");
    leg->AddEntry(gr3,"30cm","p");
    leg->AddEntry(gr4,"32cm","p");
    leg->AddEntry(gr5,"35cm","p");
    leg->AddEntry(gr6,"40cm","p");
    leg->AddEntry(gr7,"45cm","p");
    leg->AddEntry(gr8,"50cm","p");
    leg->AddEntry(gx,"real value(5cm)","p");
    leg->Draw();


TFile *f= new TFile("test1002.root","recreate");
gr1->Write();
gr2->Write();
gr3->Write();
gr4->Write();
gr5->Write();
gr6->Write();
gr7->Write();
gr8->Write();
f->Close();

*/
}
