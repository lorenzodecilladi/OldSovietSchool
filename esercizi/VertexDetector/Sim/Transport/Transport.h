#ifndef Transport_h
#define Transport_h


#include "Particle.h"

Point Transport(Particle part, Double_t R);

Double_t time(Particle part, Double_t R);
Double_t x(Double_t t);
Double_t y(Double_t t);
Double_t z(Double_t t);

//Parametri dell'eq parametrica della retta-traiettoria
Double_t c1() {return TMath::Sin(fTheta)*TMath::Cos(fPhi);}

Double_t c2() {return TMath::Sin(fTheta)*TMath::Sin(fPhi);}

Double_t c3() {return TMath::Cos(fTheta);}

 
#endif

