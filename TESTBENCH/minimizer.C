#include <boost/python.hpp>

#include <stdio.h>
#include "TApplication.h"
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TMath.h"


#include <fstream>
#include <math.h>


double a[16], b[16];




double func(const double *x){

    double c[16];
    double s[16];
    double pi = TMath::Pi();
    for (int itheta=0;itheta<16;itheta++){
        c[itheta] = cos(itheta*pi/16); 
        s[itheta] = sin(itheta*pi/16);
        std::cout << c[itheta] << s[itheta] << std::endl;
    }
     
    



  double val=0;
  for(int i=0;i<16;i++){
    val += pow(x[0] + x[2]*c[i] -a[i], 2) + pow(x[1] - x[2]*s[i] -b[i], 2);
  }
  return val;
}

void minimizer(){
//int main(int argn,char* argv[]){
  std::ifstream data("edgedata.txt");
  
  double x0, y0, r0;
  data >> x0 >> y0 >> r0;



    
  for(int i=0;i<16;i++){
    data >> a[i] >> b[i];
  }
  ROOT::Math::Minimizer *min = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");
  min->SetMaxFunctionCalls(1000000); // for Minuit/Minuit2
  min->SetMaxIterations(10000); // for GSL
  min->SetTolerance(0.001);
  min->SetPrintLevel(0);
  ROOT::Math::Functor f(&func,1);
  min->SetFunction(f);
  min->SetVariable(0,"x",x0, 0.01);
  min->SetVariable(1,"y",y0, 0.01);
  min->SetVariable(2,"r",r0, 0.01);
  min->Minimize();
  const double *p = min->X();

  std::cout << "initial value : " << x0 << ", " << y0 << ", " << r0 << std::endl;
  std::cout << p[0] << " " << p[1] << " " << p[2] <<std::endl;  
  std::cout << min->MinValue() << std::endl;
/* TApplication theApp("app",&argn,argv);
    theApp.Run();
    return 0;
*/
}

BOOST_PYTHON_MODULE(minimizer){
boost::python::def("minimizer", minimizer);
}
