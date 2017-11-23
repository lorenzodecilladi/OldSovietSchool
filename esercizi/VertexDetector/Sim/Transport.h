#ifndef Transport_h
#define Transport_h

#include "Particle.h"
#include "Vertix.h"

class Transport{

  //serve che erediti da TObject ??
  //serve accettanza su eta? se si includi Constans.h
 public:
  
  Transport();
  Transport(Double_t _phi, Double_t _eta);
  //Transport(const Transport& source); ci serve??

  virtual ~Transport();

  Double_t time(Double_t R);
  Double_t x(Double_t t);
  Double_t y(Double_t t);
  Double_t z(Double_t t);
  

    //Parametri dell'eq parametrica della retta-traiettoria
  //forse da spostare
  Double_t c1() {return TMath::Sin(fTheta)*TMath::Cos(fPhi);}
 
  Double_t c2() {return TMath::Sin(fTheta)*TMath::Sin(fPhi);}
    
  Double_t c3() {return TMath::Cos(fTheta);}



  
 private:

  Particle fPart;
  Vertix fVert;
  //detector ???

  
  ClassDef(Transport, 1)
  
};

#endif

