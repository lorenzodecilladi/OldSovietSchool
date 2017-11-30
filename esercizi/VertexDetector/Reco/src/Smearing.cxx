#include "Smearing.h"
#include "Detector.h"
#include "Riostream.h"
#include "Math.h"

Double_t evalPhi(Point hit){
  Double_t x = hit.X();
  Double_t y = hit.Y();
  
  if(x>0 && y>0) return TMath::ATan(y/x);
  else if(x<0 && y<0) return TMath::ATan(y/x)+math::pi;
  else if(x>0 && y<0) return TMath::ATan(y/x)+2*math::pi;
  else if(x<0 && y>0) return TMath::ATan(y/x)+math::pi;
  else {
    cout << "WARNING: x or y == 0 !!! phi set to -1 ___ Smearing::evalPhi TO BE DEBUGGED" << endl;
    return -1.;
  }
}


Bool_t matchHits(Point hit1L, Point hit2L){
  Double_t phi1L = evalPhi(hit1L);
  Double_t phi2L = evalPhi(hit2L);
  Double_t deltaPhi = TMath::Abs(phi1L-phi2L);

  if(deltaPhi <= detector::cutPhi) return kTRUE;
  else return kFALSE;
}
