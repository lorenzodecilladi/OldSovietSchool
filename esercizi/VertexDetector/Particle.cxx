#include "Particle.h"
#include "Utils.h"

Particle::Particle(){
  fPhi = utils::rndmUniform(0., 2*pi);
  fEta = utils::rndmUniform(-2., 2.);
  fTheta = theta(fEta);
}

Particle::Particle(Double_t _phi, Double_t _eta){
  fPhi = _phi;
  fEta = _eta;
  fTheta = theta(fEta);
}

Particle::~Particle(){
}

void Particle::setEta(Double_t _eta){
  fEta = _eta;
  fTheta = theta(fEta);
  c1();
  c2();
  c3();
}

Double_t Particle::eta(Double_t _theta){
  return -TMath::Log(TMath::Tan(_theta/2.));
}

Double_t Particle::theta(Double_t _eta){
  return 2.*TMath::ATan(TMath::Exp(-fEta));
}
