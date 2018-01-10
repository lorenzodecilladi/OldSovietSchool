//#include "../include/Point.h"
#include "Riostream.h"
#include "Point.h"
#include "Rootils.h"
#include "Detector.h"
//#endif

ClassImp(Point)

//default constructor
Point::Point():TObject(){
  fX = 0.;
  fY = 0.;
  fZ = 0.;
  fsX = 0.01; //[cm]
  fsY = 0.01;
  fsZ = 0.01;
}

//standard constructor
Point::Point(Double_t x, Double_t y, Double_t z):TObject(){
  fX = x;
  fY = y;
  fZ = z;
  fsX = 0.01; //[cm]
  fsY = 0.01;
  fsZ = 0.01;
}

//copy constructor
Point::Point(const Point& source):TObject(source){
  fX = source.fX;
  fY = source.fY;
  fZ = source.fZ;
  fsX = source.fsX;
  fsY = source.fsY;
  fsZ = source.fsZ;
}

//destructor
Point::~Point(){}//cout << "Destroying Point..."<< endl;}

//assignment operator
Point& Point::operator= (const Point& source){
  if(this == &source) return *this;
  this -> ~Point();
  new(this) Point(source);
  return *this;
}


//setter functions
void Point::setX(Double_t x){fX = x;}
void Point::setY(Double_t y){fY = y;}
void Point::setZ(Double_t z){fZ = z;}
void Point::setsX(Double_t sX){fsX = sX;}
void Point::setsY(Double_t sY){fsY = sY;}
void Point::setsZ(Double_t sZ){fsZ = sZ;}
void Point::setCoords(Double_t x, Double_t y, Double_t z){
  setX(x);
  setY(y);
  setZ(z);
}


void Point::smearing(Double_t R){
  Double_t x0 = fX;
  Double_t y0 = fY;
  Double_t z0 = fZ;

  //namespace rootils  in /Utils/Rootils.h
  //namespace detector in /Geometry/Detector.h
  Double_t smearZ    = rootils::rndmGaus(0., detector::smZ);
  Double_t smearRPhi = rootils::rndmGaus(0., detector::smRPhi);
  Double_t smearPhi  = smearRPhi/R;

  fX = x0*TMath::Cos(smearPhi) - y0*TMath::Sin(smearPhi);
  fY = y0*TMath::Cos(smearPhi) + x0*TMath::Sin(smearPhi);
  fZ = z0 + smearZ;
}
