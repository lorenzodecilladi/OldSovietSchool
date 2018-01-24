#include "Riostream.h"
#include "Tracklet.h"
#include "Detector.h"
#include "MyMath.h"

using namespace detector;

ClassImp(Tracklet)


Tracklet::Tracklet(){
  
  fHit1L = Point();
  fHit2L = Point();
  
}



//standard constructor
Tracklet::Tracklet(Point hit1L, Point hit2L){

  fHit1L = hit1L;
  fHit2L = hit2L;

}

//copy constructor
Tracklet::Tracklet(const Tracklet& source):Point(source){

  fHit1L = source.fHit1L;
  fHit2L = source.fHit2L;

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
  Double_t szV = (1. + 2*r1L/(r2L-r1L))*smZ;

  Point vertex = Point(0,0,zV);
  vertex.setsZ(szV);

  return vertex;
}




Double_t Tracklet::evalPhi(Point hit){
  Double_t x = hit.X();
  Double_t y = hit.Y();
  
  if(x>0 && y>0) return TMath::ATan(y/x);
  else if(x<0 && y<0) return TMath::ATan(y/x)+mymath::pi;
  else if(x>0 && y<0) return TMath::ATan(y/x)+2*mymath::pi;
  else if(x<0 && y>0) return TMath::ATan(y/x)+mymath::pi;
  else {
    cout << "WARNING: x or y == 0 !!! phi set to -1 ___ Smearing::evalPhi TO BE DEBUGGED" << endl;
    return -1.;
  }
}


Bool_t Tracklet::matchHits(){
  Double_t phi1L = evalPhi(fHit1L);
  Double_t phi2L = evalPhi(fHit2L);
  Double_t deltaPhi = TMath::Abs(phi1L-phi2L);

  if(deltaPhi <= detector::cutPhi) return kTRUE;
  else return kFALSE;
}
