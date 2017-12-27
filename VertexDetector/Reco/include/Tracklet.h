#ifndef TRACKLET_H
#define TRACKLET_H

#include "Point.h"

class Tracklet : public Point{

 public:

  Tracklet();
  Tracklet(Point hit1L, Point hit2L);
  Tracklet(const Tracklet& source);

  virtual ~Tracklet();

  //assignment operator
  Tracklet& operator= (const Tracklet& source);

  Point extractVertex();

  
 private:

  Point fHit1L;
  Point fHit2L;

  ClassDef(Tracklet,1) //coordinates of a point
};


#endif
