#ifndef MYMATH_H
#define MYMATH_H

#include "TMath.h"

namespace mymath{

  static const Double_t pi = TMath::Pi();
  
  Double_t radToDeg(Double_t rad){
    return rad*180./pi;
  }
  
  Double_t degToRad(Double_t deg){
    return deg*pi/180.;
  }
  
}

#endif
