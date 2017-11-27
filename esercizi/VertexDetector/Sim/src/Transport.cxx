#include "Riostream.h"
#include "Transport.h"



Point transport(Particle part, Double_t R){
  
  Double_t t = time(part, R);
  if(t==0){
    cout << "WARNING: Transport time == 0" << endl;
    return Point(part.getPoint());
  }
  Double_t _c1 = c1(part.getDirection());
  Double_t _c2 = c2(part.getDirection());
  Double_t _c3 = c3(part.getDirection());

  Double_t x0 = part.getPoint().X();
  Double_t y0 = part.getPoint().Y();
  Double_t z0 = part.getPoint().Z();

  Double_t x = x0+_c1*t;
  Double_t y = y0+_c2*t;
  Double_t z = z0+_c3*t;
  
  return Point(x, y, z);
}



Double_t time(Particle part, Double_t R){
  Double_t x0 = part.getPoint().X();
  Double_t y0 = part.getPoint().Y();
  Double_t _c1 = c1(part.getDirection());
  Double_t _c2 = c2(part.getDirection());
  Double_t delta = (x0*_c1+y0*_c2)*(x0*_c1+y0*_c2) - (_c1*_c1+_c2*_c2)*(x0*x0+y0*y0-R*R);
  Double_t t1 = (-(x0*_c1+y0*_c2) - TMath::Sqrt(delta))/(_c1*_c1+_c2*_c2);
  Double_t t2 = (-(x0*_c1+y0*_c2) + TMath::Sqrt(delta))/(_c1*_c1+_c2*_c2);
  if(t1>0) return t1;
  else if(t2>0) return t2;
  else return 0.;
}



//Parametri dell'eq parametrica della retta-traiettoria
Double_t c1(Direction dir){
  Double_t theta = dir.theta;
  Double_t phi = dir.phi;
  return TMath::Sin(theta)*TMath::Cos(phi);
}

Double_t c2(Direction dir){
  Double_t theta = dir.theta;
  Double_t phi = dir.phi;
  return TMath::Sin(theta)*TMath::Sin(phi);
}

Double_t c3(Direction dir){
  Double_t theta = dir.theta;
  return TMath::Cos(theta);
}

