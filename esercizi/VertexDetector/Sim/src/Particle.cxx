#include "Particle.h"
#include "Rootils.h"
#include "Math.h"
#include "Riostream.h"

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

Particle::~Particle(){}

void Particle::setPoint(Point point){
  fPoint.setCoords(point.X(), point.Y(), point.Z());
}

void Particle::setDirection(Direction dir){
  fDirection = dir;
}

void Particle::print(){

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
