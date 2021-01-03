#include <math.h>
#include <cmath>

void test2(){
TH1D * h = new TH1D("h","h",100,-10,10);
TH1D * h2 = new TH1D("h2","h2",100,-10,10);

h->FillRandom("gaus",100000);
TCanvas * c1 =new TCanvas ("c1","c1");
h->Draw();

float a1=0, a2=0, a3=0, d1=0, d2=0, d3=0;
std::cout << "hello" << h->GetRandom() 
//    ", " << fabs(1.)
<< std::endl;
for (int i=0; i < 1000; i++){
    
    a1 = h->GetRandom();
    a2 = h->GetRandom();
    a3 = h->GetRandom();

    d1 = fabs(a1);
    d2 = fabs(a2);
    d3 = fabs(a3);
std::cout << "hello" << h->GetRandom() 
//    ", " << fabs(1.)
<< std::endl;

    if (d1 <= d2 && d1 <= d3){
        std::cout << d1 << ", " << d2 << ", " << d3 << std::endl;
        h2->Fill(a1);
    }else if (d2 <= d1 && d2 <= d3){
        std::cout << d1 << ", " << d2 << ", " << d3 << std::endl;
        h2->Fill(a2);
    }else {
        std::cout << d1 << ", " << d2 << ", " << d3 << std::endl;
        h2->Fill(a3);
    }
}

TCanvas * c2 =new TCanvas ("c2","c2");
h2->Draw();
}
