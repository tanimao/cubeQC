#include <iostream>
#include <fstream>

void macro_badcube(){

TFile *fin = new TFile("bad0925.root", "read");
TTree *tree = (TTree*)fin->Get("tree");

TCut cut1("cut1", "abs(xhole[0]-yhole[2])<=5");
TCut cut2("cut2", "abs(xhole[2]-yhole[0])<=5");
TCut cut3("cut3", "abs(xhole[1]-yhole[3])<=5");
TCut cut4("cut4", "abs(xhole[3]-yhole[1])<=5");
TCut cut5("cut5", "abs(xhole[4]-yhole[5])<=5");
TCut cut6("cut6", "abs(xhole[5]-yhole[4])<=5");
tree->Draw("ysize[4]>>h1(100,200,300)",cut1&&cut2&&cut3&&cut4&&cut5&&cut6);


}
