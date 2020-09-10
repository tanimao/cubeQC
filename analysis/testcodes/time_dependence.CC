#include <fstream>
void time_dependence(){

const Int_t n = 98;
Int_t t[n]={0};
Int_t size_x[n]={0}, size_y[n]={0}, Xhole[n]={0}, Yhole[n]={0};
Int_t x_c[n]={0}, y_c[n]={0}, r_c[n]={0};
//Char_t saveName[n];

ifstream fin("test.dat");


for(Int_t i=0;i<n;i++){
    fin >> x_c[i] >> y_c[i] >> r_c[i] >> Xhole[i] >> Yhole[i] >> size_x[i] >> size_y[i];
    t[i] = i+1; 
   }
TCanvas *c1 = new TCanvas("c1","c1");
TGraph *g1 = new TGraph(n, t,size_x);
g1->SetMarkerSize(1.5);
g1->SetMarkerColor(2);
g1->SetMarkerStyle(8);
g1->Draw("AP");

}
