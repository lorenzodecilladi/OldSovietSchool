#ifndef MATH_H
#define MATH_H

#include "TMath.h"

namespace math{

  static const Double_t pi = TMath::Pi();
  
  Double_t radToDeg(Double_t rad){
    return rad*180./pi;
  }
  
  Double_t degToRad(Double_t deg){
    return deg*pi/180.;
  }
  
}

#endif
