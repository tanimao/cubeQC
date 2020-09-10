#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void good_soukan0925(){


const char *fileName = "../files/cube_data_circle0918.txt";

ofstream ofs(fileName);
if(!ofs){
    cerr<< "cannot open file.\n";
    cin.get();
    return 0;
}

ifstream ifs(fileName);
if(!ifs)
{
    cout << "cannot open file.\n"<< endl;
    cin.get();
    return 0;

}
const Int_t n = 60;
string data[n];
Int_t bufx[n], bufy[n], r[n], Lx[n], Ly[n], size_x[n], size_y[n];
    for(Int_t i; i<n; i++){
        ifs >> data[i] >> bufx[i] >> bufy[i] >> r[i] >> Lx[i] >> Ly[i] >> size_x[i] >> size_y[i];
        
        cout << data[i]<< size_x[i]<<endl;
        }

}
