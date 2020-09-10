#include <iostream>
#include <fstream>

void TTree_hist(){

TString gorb = "good";
TString date = "1114";
TString prefolder = "../";
TString makeroot = "1hist1.root";
TString opentxt1 = "../../files/cube_data";
TString opentxt2 = "1hist1.txt";
TString cuttxt   = "1cut.txt";

TString file_root = prefolder + date + gorb + makeroot;
TString file_txt  = prefolder + date + gorb + opentxt2;
TString file_cuttxt = prefolder + date + gorb + cuttxt;

TFile *file = new TFile(file_root,"recreate");
TTree *tree = new TTree("tree","tree");

std::ifstream fin;
fin.open(file_txt);
if(fin.fail()){
    cerr << "cannot open file. " << endl;
    return 1;
}

std::ifstream finCut;
finCut.open(file_cuttxt);
if(finCut.fail()){
    cerr << "cannot open file. " << endl;
    return 1;
}
int isurvive = 0;
string dum_line;
while(true){
    cout << "now isurvive is " << isurvive << endl;
    getline(finCut, dum_line);
    if(finCut.eof()){ break;}

    isurvive++;
}

 cout << "the number of survived cubes is " << isurvive << endl;
 
 int *n_cubeSur = new int[isurvive]; 

for (int i =0; i < isurvive; i++){
    n_cubeSur[i] = 0;
}

Int_t n_cube = isurvive;
Int_t n = 6;


std::string saveName[n];
double col[n];
double colw[n];
double colall[n];
int cubeNum =0;


tree->Branch("col", col, "col[6]/D");
tree->Branch("colw", colw, "colw[6]/D");
tree->Branch("colall", colall, "colall[6]/D");

for(Int_t i=0; i<n_cube;i++){
    for(Int_t j=0; j<n;j++){
        fin >> saveName[j] >> col[j] >> colw[j] >> colall[j];
    
    }

        cout << saveName[0] << endl;
        tree->Fill();
    
}

delete[] n_cubeSur;

tree->Write();
fin.close();
file->Close();
finCut.close();
}
