#include "../include/Point.h"
//#include "TObject.h"
//#include "Point.h"

//ClassImp(Point)

//default constructor
Point::Point(){//:TObject(){
  fX = 0.;
  fY = 0.;
  fZ = 0.;
}

//standard constructor
Point::Point(Double_t x, Double_t y, Double_t z){//:TObject(){
  fX = x;
  fY = y;
  fZ = z;
}

//copy constructor
Point::Point(const Point& source){//:TObject(source){
  fX = source.fX;
  fY = source.fY;
  fZ = source.fZ;
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


//getter functions
Double_t Point::X(){return fX;}
Double_t Point::Y(){return fY;}
Double_t Point::Z(){return fZ;}


//setter functions
void Point::setX(Double_t x){fX = x;}
void Point::setY(Double_t y){fY = y;}
void Point::setZ(Double_t z){fZ = z;}
void Point::setCoords(Double_t x, Double_t y, Double_t z){
  setX(x);
  setY(y);
  setZ(z);
}
