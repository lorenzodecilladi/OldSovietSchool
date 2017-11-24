#ifndef Particle_h
#define Particle_h

#include "TMath.h"
#include "Point.h"
#include "Direction.h"

class Particle : public Point {

  //serve accettanza su eta? se si includi Detector.h
  
 public:
  
  Particle();
  Particle(Point point, UInt_t label);
  //Particle(const Particle& source); ci serve??

  virtual ~Particle();

  //calcolo pseudorapidity
  Double_t thetaToEta(Double_t theta);//non riesco a settare come default argument il data member fTheta
   
  Double_t etaToTheta(Double_t eta);//non riesco a settare come default argument il data member fEta
                                //rad
  void setDirection(Direction dir);

  void setCoords(Point point);
							       

    

  
 private:



  //forse dovremmo mettere coordinate!!
  Point fPoint;

  Direction fDirection;
  //Double_t fPhi; //azimut [0,2Pi]
  //Double_t fTheta; // pseudorapidity angle [0, Pi]
  //Double_t fEta; // pseudorapydity eta = ln(tg(theta/2)))
  
  //particle label in a single event
  UInt_t fLabel;
  
  ClassDef(Particle, 1)
  
};

#endif
