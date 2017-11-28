#include "Riostream.h"
#include "Transport.h"



Point transport(Particle part, Double_t R){
  
  Double_t t = time(part, R);
  //  cout << "Time t = " << t << endl;
  if(t==0){
    cout << "Particle # "<< part.getLabel() << ": WARNING: Transport time == 0" << endl;
    return Point(part.getPoint());
  }
  Double_t _c1 = part.getDirection().c1();
  Double_t _c2 = part.getDirection().c2();
  Double_t _c3 = part.getDirection().c3();

  Double_t x0  = part.getPoint().X();
  Double_t y0  = part.getPoint().Y();
  Double_t z0  = part.getPoint().Z();

  Double_t x = x0+_c1*t;
  Double_t y = y0+_c2*t;
  Double_t z = z0+_c3*t;
  
  return Point(x, y, z);
}



Double_t time(Particle part, Double_t R){
  Double_t x0 = part.getPoint().X();
  Double_t y0 = part.getPoint().Y();
  Double_t _c1 = part.getDirection().c1();
  Double_t _c2 = part.getDirection().c2();
  Double_t delta = (x0*_c1+y0*_c2)*(x0*_c1+y0*_c2) - (_c1*_c1+_c2*_c2)*(x0*x0+y0*y0-R*R);
  Double_t t1 = (-(x0*_c1+y0*_c2) - TMath::Sqrt(delta))/(_c1*_c1+_c2*_c2);
  Double_t t2 = (-(x0*_c1+y0*_c2) + TMath::Sqrt(delta))/(_c1*_c1+_c2*_c2);
  if(t1>0) return t1;
  else if (t2>0) return t2;
  //else return t2;
  else return 0.;
}



