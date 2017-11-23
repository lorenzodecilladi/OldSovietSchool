#include "Particle.h"
#include "Rootils.h"
#include "Math.h"

ClassImp(Particle)

Particle::Particle(){

  fPoint = Point();

  fDirection.phi = rootils::rndmUniform(0., 2*math::pi);
  fDirection.eta = rootils::rndmUniform(-2., 2.);
  fDirection.theta = etaToTheta(fDirection.eta);


  fLabel = 0;
}

Particle::Particle(Point point, Int_t label){
  fPoint = point;

  fDirection.phi = rootils::rndmUniform(0., 2*math::pi);
  fDirection.eta = rootils::rndmUniform(-2., 2.);
  fDirection.theta = etaToTheta(fDirection.eta);

  fLabel = label;
}

Particle::~Particle(){}


void Particle::setDirection(Direction dir){
  fDirection.phi = dir.phi;
  fDirection.eta = dir.eta;
  fDirection.theta = dir.theta;
}

void setCoords(Point point){
  fPoint.setCoords(point.X(), point.Y(), point.Z());
}


Double_t Particle::thetaToEta(Double_t theta){
  return -TMath::Log(TMath::Tan(theta/2.));
}

Double_t Particle::etaToTheta(Double_t eta){
  return 2.*TMath::ATan(TMath::Exp(-eta));
}
