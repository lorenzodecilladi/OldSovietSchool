#ifndef Constants_h
#define Constants_h

#include "TMath.h"

namespace constants{

  Double_t pi = TMath::Pi();
  
  Double_t sZv = 5.33; //cm    sigma Z vertex
  Double_t sXv = 0.01; //cm    sigma X vertex
  Double_t sYv = 0.01; //cm    sigma Y vertex
  
  Double_t rBP = 3.;   //cm    R Beam Pipe
  Double_t tBP = 0.08; //cm    thickness Beam Pipe
  
  Double_t r1L = 4.;   //cm    R 1st Layer
  Double_t t1L = 0.02; //cm    thickness 1st Layer
  
  Double_t r2L = 7.;   //cm    R 2nd Layer
  Double_t t2L = 0.02; //cm    thickness 2nd Layer
  
  Double_t length = 27.; //cm
  
  Double_t etaMin = -2.; // pseudorapidity acceptance  
  Double_t etaMax = 2.;
  
  Double_t smZhit = 0.012; //cm  smearing Z direction  (120 #mum)
  Double_t smRhit = 0.003; //cm  smearing r#phi direction (30 #mum)

}
#endif
