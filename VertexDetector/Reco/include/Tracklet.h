#ifndef TRACKLET_H
#define TRACKLET_H

#include "Point.h"

/**
 * Tracklet class. Used to initialise a Tracklet, which is a line joining two hits (data members fHits1L and fHits2L. These hits are Points located on two different layers of the detector. The tracklet can be accepted, or not, as a viable candidate for a high momentum Particle's trajectory according to geometrical constraints defined in the method matchHits(). If the tracklet is accepted, then it is used to extrapolate the reconstructed vertex position: the intersection between the tracklet and the beam line (see extractVertex()).
 */
class Tracklet : public Point{

 public:

  /**
   * Default constructor.
   * fHits1L and fHits2L are set using Point's default constructor.
   */
  Tracklet();

  /**
   * Standard constructor.
   * The tho hits joined by the Tracklet are passed as arguments (hit1L, hit2L).
   */
  Tracklet(Point hit1L, Point hit2L);
  
  Tracklet(const Tracklet& source);  ///< Copy constructor
  virtual ~Tracklet();               ///< Default destructor
  Tracklet& operator= (const Tracklet& source); ///< assignment operator

  /**
   * Extrapolates the reconstructed vertex position (z coordinate only) on the beam line.
   * A line joining the two hits on the two detector's layers is used to extrapolate the z coordinate of the reconstructed vertex.
   * The x and y coordinates of the reconstructed vertex are set to 0. (see the constraint decribed in matchHits() for an explanation).
   * The uncertainty on the reconstructed z coordinate is propagated taking into account the smearing of the hits on the detector's layers.
   */
  Point extractVertex();

  /**
   * Returns the azimutal angle &phi; of the hit passed as argument.
   * Given the (x,y,z) coordinates of the hit position, the method evaluates and returns its azimutal &phi; coordinate.
   */
  Double_t evalPhi(Point hit);

  /**
   * Checks whether the Tracklet is to be accepted.
   * A Tracklet is accepted only if the distance between the azimutal &phi; coordinates of the two hits (Tracklet's data members) is <= cutPhi.
   *cutPhi is hardcoded in ~/VertexDetector/Geometry/Detector.h and is a variable of the namespace detector. Its value is set to 0.01 rad and let us consider negligible the distance in &phi; between the two hits of accepted tracklets.
   */
  Bool_t matchHits();

  
 private:

  Point fHit1L; ///< Hit on the first  layer of the detector
  Point fHit2L; ///< Hit on the second layer of the detector

  ClassDef(Tracklet,1)
};


#endif
