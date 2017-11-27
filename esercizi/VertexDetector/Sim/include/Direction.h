
//typedef struct{
//  Double_t eta, theta, phi;
//} Direction;

#ifndef DIRECTION_H
#define DIRECTION_H

#include "TObject.h"

class Direction : public TObject{

 public:

  Direction();
  Direction(Double_t theta, Double_t phi);
  Direction(Double_t c1, Double_t c2, Double_t c3);
  Direction(const Direction& source);
  
  virtual ~Direction();

  //assignment operator
  Direction& operator= (const Direction& source);

  //calcolo pseudorapidity
  Double_t thetaToEta();//non riesco a settare come default argument il data member fTheta
   
  Double_t etaToTheta();//non riesco a settare come default argument il data member fEta
                                //rad


//evaluate c1, c2, c3 from theta, phi. And viceversa.
  Double_t evalC1();
  Double_t evalC2();
  Double_t evalC3();
  Double_t evalTheta();
  Double_t evalPhi();
  
  // getter funtions
  Double_t theta(){return fTheta;}
  Double_t phi(){return fPhi;}
  Double_t eta(){return fEta;}
  Double_t c1(){return fC1;}
  Double_t c2(){return fC2;}
  Double_t c3(){return fC3;}
  

  // setter functions
  // ???

  
 private:
  
  Double_t fEta;
  Double_t fTheta;
  Double_t fPhi;
  Double_t fC1;
  Double_t fC2;
  Double_t fC3;

  
  ClassDef(Direction,1)
    };

#endif
