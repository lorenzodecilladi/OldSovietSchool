#include "Transport.h"


Double_t time(Particle part, Double_t R){
  Double_t x0 = part.getCoords.X();
  Double_t y0 = part.getCoords.Y();
  Double_t c1 = c1();
  Double_t c2 = c2();
  Double_t delta = (x0*c1+y0*c2)*(x0*c1+y0*c2) - (c1*c1+c2*c2)*(x0*x0+y0*y0-R*R);
  Double_t t1 = (-(x0*c1+y0*c2) - TMath::Sqrt(delta))/(c1*c1+c2*c2);
  Double_t t2 = (-(x0*c1+y0*c2) + TMath::Sqrt(delta))/(c1*c1+c2*c2);
  if(t1>0) return t1;
  else if(t2>0) return t2;
  else return 0.;
}

Double_t x(Particle part, Double_t R){
  Double_t t = time(part, R);
  Double_t x0 = part.getCoords.X();
  Double_t y0 = part.getCoords.Y();
  Double_t c1 = c1();
  Double_t c2 = c2();
  
}
Double_t y(Particle part, Double_t R);
Double_t z(Particle part, Double_t R);
  
  
 private:

  Particle fPart;
  Vertix fVert;
  //detector ???

  
  ClassDef(Transport, 1)
  
};

#endif

