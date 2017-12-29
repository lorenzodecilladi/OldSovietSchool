#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include "TRandom3.h"
#endif

void gausGen(Int_t numEvts=10000, Int_t mean=20, Int_t sigma=5, const char *foutName = "outFile.txt"){

  ofstream fout(foutName);

  Int_t mult = 0;
  for(int i=0; i<numEvts; i++){
    do{mult = gRandom->Gaus(mean,sigma);}
    while(mult<0);
    fout<<mult<<endl;
  }

  fout.close();
}
