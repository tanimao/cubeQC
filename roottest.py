
import ROOT

import time
import numpy as np

start = time.time()
a = np.zeros(50)
def func(x):
    val = 0
    for i in range(50):
        val += pow(x[0]-a[i],2)
    return val


def main():
    f = open("data.txt")
    areas = f.read().split()
    print(areas)
    for i, area in enumerate(areas):
        a[i] = int(area)
        print(a[i])
    print (a)
    f.close()
    print('time : {} sec'.format(time.time()-start))

    minimizer = ROOT.Math.Factory.CreateMinimizer('Minuit2', 'Migrad')
    minimizer.SetMaxFunctionCalls(1000000)
    minimizer.SetMaxIterarions(10000)
    minimizer.SetTolerance(0.001)
    minimizer.SetPrintLevel(0)
     
"""  

  ROOT::Math::Minimizer* min = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");
  min->SetMaxFunctionCalls(1000000); // for Minuit/Minuit2
  min->SetMaxIterations(10000); // for GSL
  min->SetTolerance(0.001);
  min->SetPrintLevel(0);
  ROOT::Math::Functor f(&func,1);
  min->SetFunction(f);
  min->SetVariable(0,"x",0, 0.01);
  min->Minimize();
  const double *p = min->X();
  cout<<p[0]<<endl;  
"""


if __name__ == "__main__":
    main()





