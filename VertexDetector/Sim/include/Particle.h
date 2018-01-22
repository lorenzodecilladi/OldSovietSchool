#ifndef Particle_h
#define Particle_h

#include "TMath.h"
#include "Point.h"
#include "Direction.h"

/**
 * Particle class. Used to initialise a Particle, always characterised by a Point and a Direction, which are its data members fPoint and fDirection. The third data member of a Particle is an integer label (fLabel), that can be used to keep track of the generated particles. The original position of a Particle is, usually, represented by a Vertex, in which a number of Particles equal to the Vertex's multiplicity are generated.
 */
class Particle : public Point {
  
 public:

  /**
   * Default constructor.
   * fPoint is set using Point's default constructor.
   * fDirection is set using Direction's default constructor.
   * fLabel is set to 0.
   */
  Particle();

  /**
   * Standard constructor.
   * fPoint is set to the Point (point) passed as argument.
   * fDirection is set using Direction's default constructor.
   * fLabel is set to the integer value (label) passed as argument.
   */
  Particle(Point point, UInt_t label);
  
  /**
   * Standard constructor.
   * fPoint is set to the Point (point) passed as argument.
   * fDirection is set to the Direction (dir) passed as argument.
   * fLabel is set to the integer value (label) passed as argument.
   */
  Particle(Point point, Direction dir, UInt_t label);

  virtual ~Particle(); ///< Default destructor.

  
  Point     getPoint()     const {return fPoint;}     ///< Returns fPoint
  Direction getDirection() const {return fDirection;} ///< Returns fDirection
  UInt_t    getLabel()     const {return fLabel;}     ///< Returns fLabel
  
  void setPoint(Point point);       ///< Sets fPoint to point
  void setDirection(Direction dir); ///< Sets fDirection to dir

  /**
   * Performs multiple scattering.
   * The Direction of the Particle (fDirection) is changed as a consequence of the multiple scattering in the beam pipe or in the detector's layers.
   */
  void multipleScattering();

  /**
   * Performs the transport of a Particle.
   * The position of the Particle (represented by the data member fPoint) is updated as a consequence of the transport of the Particle along its Direction from its "previous" position to a new position at a distance R from the beam line. The transport takes a certain time:
   * @see time()
   */
  void transport(Double_t R);

  /**
   * Returns propagation time for a Particle.
   * Returns the time needed for a Particle to propagate along its Direction from its position to a new position at a distance R from the beam line.
   * @see transport()
   */  
  Double_t time(Double_t R);
  
  void print() const;   ///< Prints Particle's coordinates and direction.
  
 private:

  Point fPoint;         ///< Point indicating the 3-dimensional position of the Vertex
  Direction fDirection; ///< Particle's direction
  UInt_t fLabel;        ///< Particle's label
  
  ClassDef(Particle, 1)
  
};

#endif
