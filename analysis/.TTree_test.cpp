#include <iostream>
#include <fstream>

void TTree_test(){

TFile *file = new TFile("TTree_test.root","recreate");
TTree *tree = new TTree("tree","tree");

std::ifstream fin;
fin.open("testdata.txt");
if(fin.fail()){
    cerr << "cannot open file. " << endl;
    return 1;
}
 //Int_t n_cube = 10; 
 Int_t n = 6;

int xsize[n];
int ysize[n];

tree->Branch("xsize", xsize, "xsize[6]/I");
tree->Branch("ysize", ysize, "ysize[6]/I");

//for(Int_t i; i<n_cube;i++){
    for(Int_t j=0; j<n;j++){
          fin  >> xsize[j] >> ysize[j];
    
    }


    tree->Fill();

tree->Write();
fin.close();
file->Close();

}
