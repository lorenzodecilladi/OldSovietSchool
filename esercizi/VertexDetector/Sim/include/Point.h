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
  Double_t X(){return fX;}
  Double_t Y(){return fY;}
  Double_t Z(){return fZ;}
  Double_t sX(){return fsX;}
  Double_t sY(){return fsY;}
  Double_t sZ(){return fsZ;}
  

  // setter functions
  void setX(Double_t x);
  void setY(Double_t y);
  void setZ(Double_t z);
  void setsX(Double_t sX);
  void setsY(Double_t sY);
  void setsZ(Double_t sZ);
  void setCoords(Double_t x, Double_t y, Double_t z);

  
 private:
  
  Double_t fX; //x coord
  Double_t fY; //y coord
  Double_t fZ; //z coord
  Double_t fsX; //x sigma
  Double_t fsY; //y sigma
  Double_t fsZ; //z sigma
  

  ClassDef(Point,1) //coordinates of a point
    };

#endif
