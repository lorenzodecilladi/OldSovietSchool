#ifndef POINT_H
#define POINT_H

#include "TObject.h"

class Point : public TObject{

 public:

  Point();
  Point(Double_t x, Double_t y, Double_t z);
  Point(const Point& source);
  
  virtual ~Point();

  //assignment operator
  Point& operator= (const Point& source);
  
  // getter funtions
  Double_t X();
  Double_t Y();
  Double_t Z();

  // setter functions
  void setX(Double_t x);
  void setY(Double_t y);
  void setZ(Double_t z);
  void setCoords(Double_t x, Double_t y, Double_t z);

  
 private:
  
  Double_t fX; //x coord
  Double_t fY; //y coord
  Double_t fZ; //z coord
  

  ClassDef(Point,1) //coordinates of a point
    };

#endif
