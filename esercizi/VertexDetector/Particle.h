#ifndef Particle_h
#define Particle_h

#include "TMath.h"

class Particle{

  //serve che erediti da TObject
  //serve accettanza su eta? se si includi Constans.h
 public:
  Particle();
  //Particle(Double_t s, Double_t p, Int_t e, Bool_t sex); ci serve??
  //Particle(const Particle& source); ci serve??

  virtual ~Particle();


  //Parametri dell'eq parametrica della retta-traiettoria
  Double_t c1(Double_t phi = fPhi, Double_t theta = fTheta) return TMath::Sin(theta)*TMath::Cos(phi);
  Double_t c2(Double_t phi = fPhi, Double_t theta = fTheta) return TMath::Sin(theta)*TMath::Sin(phi);
  Double_t c3(Double_t phi = fPhi, Double_t theta = fTheta) return TMath::Cos(theta);


 private:

  Double_t fPhi; //azimut [0,2Pi]
  Double_t fTheta; // pseudorapidity angle [0, Pi]
  Double_t fEta; // pseudorapydity eta = ln(tg(theta/2)))
  
}

#endif
