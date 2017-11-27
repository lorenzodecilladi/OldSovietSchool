#include "Direction.h"
#include "Math.h"
#include "Rootils.h"

ClassImp(Direction)

//default constructor
Direction::Direction():TObject(){

  fPhi = rootils::rndmUniform(0., 2*math::pi);
  fEta = rootils::rndmUniform(-2., 2.);
  fTheta = etaToTheta();
  fC1 = evalC1();
  fC2 = evalC2();
  fC3 = evalC3();
}

//standard constructor
Direction::Direction(Double_t theta, Double_t phi):TObject(){
  fPhi = phi;
  fTheta = theta;
  fEta = thetaToEta();
  fC1 = evalC1();
  fC2 = evalC2();
  fC3 = evalC3();
}

Direction::Direction(Double_t c1, Double_t c2, Double_t c3):TObject(){
  fC1 = c1;
  fC2 = c2;
  fC3 = c3;
  fTheta = evalTheta();
  fPhi = evalPhi();
  fEta = thetaToEta();
}

//copy constructor
Direction::Direction(const Direction& source):TObject(source){
  fEta = source.fEta;
  fTheta = source.fTheta;
  fPhi = source.fPhi;
  fC1 = source.fC1;
  fC2 = source.fC2;
  fC3 = source.fC3;
}

//destructor
Direction::~Direction(){}

//assignment operator
Direction& Direction::operator= (const Direction& source){
  if(this == &source) return *this;
  this -> ~Direction();
  new(this) Direction(source);
  return *this;
}


//Conversions eta <-> theta
Double_t Direction::thetaToEta(){
  return -TMath::Log(TMath::Tan(fTheta/2.));
}
Double_t Direction::etaToTheta(){
  return 2.*TMath::ATan(TMath::Exp(-fEta));
}



//evaluate c1, c2, c3 from theta, phi. And viceversa.
Double_t Direction::evalC1(){
  return TMath::Sin(fTheta)*TMath::Cos(fPhi);
}
Double_t Direction::evalC2(){
  return TMath::Sin(fTheta)*TMath::Sin(fPhi);
}
Double_t Direction::evalC3(){
  return TMath::Cos(fTheta);
}
Double_t Direction::evalTheta(){
  return TMath::ACos(fC3);
}
Double_t Direction::evalPhi(){ //se fC1 o fC2 == 0??
  if(fC1>0 && fC2>0) return ATan(fC2/fC1);
  else if(fC1<0 && fC2<0) return ATan(fC2/fC1)+math::pi;
  else if(fC1>0 && fC2<0) return ATan(fC2/fC1)+2*math::pi;
  else if(fC1<0 && fC2>0) return ATan(fC2/fC1)+math::pi;
}





//setter functions
//???
