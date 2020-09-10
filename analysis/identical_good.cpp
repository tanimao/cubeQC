#include <fstream>

void identical_good(){

TTree *tree = new TTree("tree","tree");

tree->ReadFile("cube_data0913extracted.dat", "saveName/C:x_c/I:y_c:r_c:Xhole:Yhole:size_x:size_y");

tree->SaveAs("identical_good0913_new.root");

//tree->Draw("size_x>>h1(100,200,300)");
//TCanvas *c2= new TCanvas("c2","c2");
//tree->Draw("size_y>>h2(100,200,300)");



}
