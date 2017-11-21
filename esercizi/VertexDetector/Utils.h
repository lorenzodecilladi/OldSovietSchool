#ifndef Utils_h
#define Utils_h

#include "Constants.h"
#include "TRandom3.h"
using namespace constants;

namespace utils{

  Double_t rndmUniform(Double_t min, Double_t max){
    Double_t x = gRandom -> Rndm();
    return x*(max-min) + min;
  }

  Double_t rndmGauss(Double_t mean, Double_t sigma){
    Double_t x = gRandom -> Gaus(mean, sigma);
    return x;
  }
  
  Double_t radToDeg(Double_t rad){
    return rad*180./pi;
  }
  Double_t degToRad(Double_t deg){
    return deg*pi/180.;
  }

  
}

#endif

