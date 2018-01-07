#include "Particle.h"
#include "Rootils.h"
#include "Math.h"
#include "Riostream.h"
#include "Detector.h"

ClassImp(Particle)

Particle::Particle(){

  fPoint = Point();
  fDirection = Direction();
  fLabel = 0;
}

Particle::Particle(Point point, UInt_t label){ //Particle(vertice.getPoint(),...)
  fPoint = point; //gli passeremo il vertice
  fDirection = Direction();
  fLabel = label;
}

Particle::Particle(Point point, Direction dir, UInt_t label){ //Particle(vertice.getPoint(),...)
  fPoint = point; //gli passeremo il vertice
  fDirection = dir;
  fLabel = label;
}

Particle::~Particle(){}



//---------- SET FUNCIONS ----------
void Particle::setPoint(Point point){
  fPoint.setCoords(point.X(), point.Y(), point.Z());
}
void Particle::setDirection(Direction dir){
  fDirection = dir;
}



//---------- TRANSPORT ----------
void Particle::transport(Double_t R){
  
  Double_t t = time(R);
  if(t==0){
    cout << "Particle # "<< fLabel << ": WARNING: Transport time == 0" << endl;
    return;
  }
  
  Double_t _c1 = fDirection.c1();
  Double_t _c2 = fDirection.c2();
  Double_t _c3 = fDirection.c3();
  Double_t x0  = fPoint.X();
  Double_t y0  = fPoint.Y();
  Double_t z0  = fPoint.Z();

  Double_t x = x0+_c1*t;
  Double_t y = y0+_c2*t;
  Double_t z = z0+_c3*t;
  fPoint = Point(x, y, z);
}

Double_t Particle::time(Double_t R){
  Double_t x0 = fPoint.X();
  Double_t y0 = fPoint.Y();
  Double_t _c1 = fDirection.c1();
  Double_t _c2 = fDirection.c2();
  Double_t delta = (x0*_c1+y0*_c2)*(x0*_c1+y0*_c2) - (_c1*_c1+_c2*_c2)*(x0*x0+y0*y0-R*R);
  Double_t t1 = (-(x0*_c1+y0*_c2) - TMath::Sqrt(delta))/(_c1*_c1+_c2*_c2);
  Double_t t2 = (-(x0*_c1+y0*_c2) + TMath::Sqrt(delta))/(_c1*_c1+_c2*_c2);
  if(t1>0) return t1;
  else if (t2>0) return t2;
  //else return t2;
  else return 0.;
}



//---------- MULTIPLE SCATTERING (MS) ----------

//Restituisce nuova direzione della particella nel SR del lab
void Particle::multipleScattering(){

  //SR lab, before MS
  Double_t _theta = fDirection.theta();
  Double_t _phi = fDirection.phi();

  //SR con apici, after MS
  Double_t theta1 = rootils::rndmGaus(0., detector::thetaSpace);
  Double_t phi1 = rootils::rndmUniform(0., 2*math::pi); //fDirection.phi();
  //Double_t phi1 = fDirection.phi();
  //Double_t phi1 = gRandom->Rndm(); //rootils::rndmUniform(0., 2*math::pi); //fDirection.phi();
  Direction dir1 = Direction(theta1, phi1); //sempre dei c
    
  //back to SR lab (sempre i coefficienti c)

  Double_t mat[3][3];
  mat[0][0] = -TMath::Sin(_phi);
  mat[0][1] = -TMath::Cos(_phi)*TMath::Cos(_theta);
  mat[0][2] =  TMath::Cos(_phi)*TMath::Sin(_theta);
  mat[1][0] =  TMath::Cos(_phi);
  mat[1][1] = -TMath::Sin(_phi)*TMath::Cos(_theta);
  mat[1][2] =  TMath::Sin(_phi)*TMath::Sin(_theta);
  mat[2][0] =  0.;
  mat[2][1] =  TMath::Sin(_theta);
  mat[2][2] =  TMath::Cos(_theta);

  Double_t cP[3] = {dir1.c1(), dir1.c2(), dir1.c3()}; //P particle S.R.
  Double_t c1L = 0, c2L = 0, c3L = 0.; //c1, c2, c3 dopo lo scattering nel SR del laboratorio
  
  for(int i=0; i<3; i++){
    c1L += mat[0][i]*cP[i];
    c2L += mat[1][i]*cP[i];
    c3L += mat[2][i]*cP[i];
  }
  fDirection = Direction(c1L, c2L, c3L);
}



//---------- PRINT PARTICLE ----------
void Particle::print() const {

  cout << "\nlabel: " << fLabel << endl;
  cout << "\nx: " << fPoint.X() << endl;
  cout << "y: " << fPoint.Y() << endl;
  cout << "z: " << fPoint.Z() << endl;
  
  cout << "\ntheta: " << fDirection.theta() << endl;
  cout << "phi: " << fDirection.phi() << endl;
  cout << "eta: " << fDirection.eta() << endl;
  cout << "c1: " << fDirection.c1() << endl;
  cout << "c2: " << fDirection.c2() << endl;
  cout << "c3: " << fDirection.c3() << endl;

}
