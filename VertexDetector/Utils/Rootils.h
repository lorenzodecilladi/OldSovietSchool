#ifndef ROOTILS_H
#define ROOTILS_H

#include "TRandom3.h"

namespace rootils{

  Double_t rndmUniform(Double_t min, Double_t max){
    Double_t x = gRandom -> Rndm(0);
    return x*(max-min) + min;
  }

  Double_t rndmGaus(Double_t mean, Double_t sigma){
    gRandom->SetSeed(0);
    Double_t x = gRandom -> Gaus(mean, sigma);
    return x;
  }

}

#endif

