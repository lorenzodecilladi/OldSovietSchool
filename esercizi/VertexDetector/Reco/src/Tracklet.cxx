#include "Riostream.h"
#include "Tracklet.h"
#include "Detector.h"


using namespace detector;

ClassImp(Tracklet)


Tracklet::Tracklet(){
  
  fHit1L = Point();
  fHit2L = Point();
  
}



//copy constructor
Tracklet::Tracklet(Point hit1L, Point hit2L){

  fHit1L = hit1L;
  fHit2L = hit2L;

}

//destructor
Tracklet::~Tracklet(){}//cout << "Destroying Tracklet..."<< endl;}

//assignment operator
Tracklet& Tracklet::operator= (const Tracklet& source){
  if(this == &source) return *this;
  this -> ~Tracklet();
  new(this) Tracklet(source);
  return *this;
}

Point Tracklet::extractVertex(){

  Double_t z1L = fHit1L.Z();
  Double_t z2L = fHit2L.Z();
  Double_t zV = z1L-r1L*((z2L-z1L)/(r2L-r1L));

  return Point(0,0,zV);
}
