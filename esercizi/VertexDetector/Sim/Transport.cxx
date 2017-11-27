#include "Transport.h"


Transport();

//Transport(Double_t _phi, Double_t _eta);
  //Transport(const Transport& source); ci serve??

~Transport();

Double_t Transport::time(Double_t R){
  Double_t x0 = fPart.x0();
  Double_t y0 = fPart.y0();
  Double_t c1 = fPart.c1();
  Double_t c2 = fPart.c2();
  Double_t delta = (x0*c1+y0*c2)*(x0*c1+y0*c2) - (c1*c1+c2*c2)*(x0*x0+y0*y0-R*R);
  Double_t t1 = (-(x0*c1+y0*c2) - TMath::Sqrt(delta))/(c1*c1+c2*c2);
  Double_t t2 = (-(x0*c1+y0*c2) + TMath::Sqrt(delta))/(c1*c1+c2*c2);
  if(t1>0) return t1;
  else if(t2>0) return t2;
  else return 0.;
}



Double_t x(Double_t t){
  Double_t x0 = fPart.x0();
  Double_t c1 = fPart.c1();
  return x0+c1*t;
}
Double_t y(Double_t t){
  Double_t y0 = fPart.y0();
  Double_t c2 = fPart.c2();
  return y0+c2*t;
}
Double_t z(Double_t t){
  Double_t z0 = fPart.z0();
  Double_t c3 = fPart.c3();
  return y0+c2*t;
}
