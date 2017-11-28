#ifndef Particle_h
#define Particle_h

#include "TMath.h"
#include "Point.h"
#include "Direction.h"

class Particle : public Point, public Direction {
  //serve accettanza su eta? se si includi Detector.h
  
 public:
  
  Particle();
  Particle(Point point, UInt_t label);
  //Particle(const Particle& source); ci serve??

  virtual ~Particle();

  Point getPoint(){return fPoint;}
  Direction getDirection(){return fDirection;}
  UInt_t getLabel(){return fLabel;}
  
  void setPoint(Point point);
  void setDirection(Direction dir);

  void print();
  
 private:

  Point fPoint;
  Direction fDirection;
  UInt_t fLabel; //particle label in a single event
  
  ClassDef(Particle, 1)
  
};

#endif
