#ifndef Particle_h
#define Particle_h

#include "TMath.h"

class Particle{

  //serve che erediti da TObject ??
  //serve accettanza su eta? se si includi Constans.h
 public:
  
  Particle();
  Particle(Double_t _phi, Double_t _eta);
  //Particle(const Particle& source); ci serve??

  virtual ~Particle();

  //calcolo pseudorapidity
  Double_t eta(Double_t _theta);//non riesco a settare come default argument il data member fTheta
   
  Double_t theta(Double_t _eta);//non riesco a settare come default argument il data member fEta
                                //rad
  void setEta(Double_t _eta);
							       
  //Parametri dell'eq parametrica della retta-traiettoria
  //forse da spostare
  Double_t c1() {return TMath::Sin(fTheta)*TMath::Cos(fPhi);}
 
  Double_t c2() {return TMath::Sin(fTheta)*TMath::Sin(fPhi);}
    
  Double_t c3() {return TMath::Cos(fTheta);}
    

  
 private:

  Double_t fPhi; //azimut [0,2Pi]
  Double_t fTheta; // pseudorapidity angle [0, Pi]
  Double_t fEta; // pseudorapydity eta = ln(tg(theta/2)))
  //forse dovremmo mettere coordinate!!
  ClassDef(Particle, 1)
  
};

#endif
