#include "Particle.h"
#include "Rootils.h"
#include "Math.h"

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

