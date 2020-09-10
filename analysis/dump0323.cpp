#include <fstream>

void good_cube(){

TTree *tree = new TTree("tree","tree");

tree->ReadFile("../files/cube_data_circle0918.txt", "saveName/C:x_c/I:y_c:r_c:Xhole:Yhole:size_x:size_y");

tree->SaveAs("good_cube0918.root");

//tree->Draw("size_x>>h1(100,200,300)");
//TCanvas *c2= new TCanvas("c2","c2");
//tree->Draw("size_y>>h2(100,200,300)");



}
