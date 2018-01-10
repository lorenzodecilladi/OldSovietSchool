#ifndef POINT_H
#define POINT_H

#include "TObject.h"


/**
 * Point class. Used to initialise points in the 3-dimensional space.
 */
class Point : public TObject{

 public:
  
  /**
   * Default constructor.
   * Sets (x,y,z) to (0.,0.,0.) and (sX, sY, sZ) to (0.01, 0.01, 0.01) [cm].
   */
  Point();

  /**
   * Standard constructor.
   */
  Point(Double_t x, Double_t y, Double_t z);

  /**
   * Copy constructor.
   */
  Point(const Point& source);

  /**
   * Default destructor.
   */
  virtual ~Point();


  Point& operator= (const Point& source);   ///< Assignment operator
  
  // getter funtions
  Double_t X() const {return fX;}    ///< Returns x coordinate
  Double_t Y() const {return fY;}    ///< Returns y coordinate
  Double_t Z() const {return fZ;}    ///< Returns z coordinate
  Double_t sX() const {return fsX;}  ///< Returns error on x coordinate
  Double_t sY() const {return fsY;}  ///< Returns error on y coordinate
  Double_t sZ() const {return fsZ;}  ///< Returns error on z coordinate
  

  // setter functions
  void setX(Double_t x);             ///< Sets x coordinate
  void setY(Double_t y);             ///< Sets y coordinate
  void setZ(Double_t z);             ///< Sets z coordinate
  void setsX(Double_t sX);           ///< Sets error on x coordinate
  void setsY(Double_t sY);           ///< Sets error on y coordinate
  void setsZ(Double_t sZ);           ///< Sets error on z coordinate
  void setCoords(Double_t x, Double_t y, Double_t z); ///< Setx (x,y,z) coordinates


  // smearing (changes Point coordinates on detector layers)
  void smearing(Double_t R);
  
  
 private:
  
  Double_t fX; ///< x coordinate
  Double_t fY; ///< y coordinate
  Double_t fZ; ///< z coordinate
  Double_t fsX; ///< error on x coordinate
  Double_t fsY; ///< error on y coordinate
  Double_t fsZ; ///< error on z coordinate

  ClassDef(Point,1)
    };

#endif
