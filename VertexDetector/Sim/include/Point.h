#ifndef POINT_H
#define POINT_H

#include "TObject.h"


/**
 * Point class. Used to initialise a point in the 3-dimensional space.
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
  Double_t  X() const {return fX;}   ///< Returns x coordinate
  Double_t  Y() const {return fY;}   ///< Returns y coordinate
  Double_t  Z() const {return fZ;}   ///< Returns z coordinate
  Double_t sX() const {return fsX;}  ///< Returns uncertainty on x coordinate
  Double_t sY() const {return fsY;}  ///< Returns uncertainty on y coordinate
  Double_t sZ() const {return fsZ;}  ///< Returns uncertainty on z coordinate
  

  // setter functions
  void  setX(Double_t x);            ///< Sets x coordinate
  void  setY(Double_t y);            ///< Sets y coordinate
  void  setZ(Double_t z);            ///< Sets z coordinate
  void setsX(Double_t sX);           ///< Sets uncertainty on x coordinate
  void setsY(Double_t sY);           ///< Sets uncertainty on y coordinate
  void setsZ(Double_t sZ);           ///< Sets uncertainty on z coordinate
  void setCoords(Double_t x, Double_t y, Double_t z); ///< Sets (x,y,z) coordinates


  /**
   * Smearing of Point's coordinates on a detector layer at radius R.
   * Function intended to be used when the Point represents a hit on a detector's layer. The coordinates of the point receive a gaussian smearing. The parameters for the smearing along the Z coordinate and along the r&phi; direction are hardcoded in the file VertexDetector/Geometry/Detector.h (suggested values are 120 &mu;m along the z coordinate and 30 &mu;m in th r&phi; direction).
   */
  void smearing(Double_t R);
  
  
 private:
  Double_t fX;  ///< x coordinate
  Double_t fY;  ///< y coordinate
  Double_t fZ;  ///< z coordinate
  Double_t fsX; ///< uncertainty on x coordinate
  Double_t fsY; ///< uncertainty on y coordinate
  Double_t fsZ; ///< uncertainty on z coordinate

  ClassDef(Point,1)
    };

#endif
