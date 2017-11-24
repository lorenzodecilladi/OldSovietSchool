//#if !defined(__CINT__) || defined(__MAKECINT__)
//#include "../include/Point.h"
#include "Point.h"
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
Point::~Point(){}

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
