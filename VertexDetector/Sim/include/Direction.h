#ifndef DIRECTION_H
#define DIRECTION_H

#include "TObject.h"
#include "TH1F.h"

/**
 * Direction class. Used to initialise a direction in the 3-dimensional space.
 */
class Direction : public TObject{

 public:

  /**
   * Default constructor.
   * Uniform extraction of &phi; in [0, 2*&pi;]
   * Uniform extraction of pseudorapidity &eta; in [-2., 2.]
   */
  Direction();
  
  /**
   * Standard constructor.
   * Uniform extraction of &phi; in [0, 2*&pi;]
   * Pseudorapidity (&eta;) distribution passed as argument through input histogram (heta, stored in kinem.root)
   */
  Direction(TH1F* histEta);
  
  Direction(Double_t theta, Double_t phi);           /**< Standard constructor. Polar and azimutal angles passed as arguments. */
  Direction(Double_t c1, Double_t c2, Double_t c3);  /**< Standard constructor. %Direction cosines passed as arguments. */
  Direction(const Direction& source);                ///< Copy constructor.
  virtual ~Direction();                              ///< Default destructor.
  Direction& operator= (const Direction& source);    ///< Assignment operator.

  Double_t thetaToEta(); ///< Performs conversion from polar angle &theta; to preudorapidity &eta;. Operates on data members.
   
  Double_t etaToTheta(); ///< Performs conversion from preudorapidity &eta; to polar angle &theta;. Operates on data members.


//evaluate c1, c2, c3 from theta, phi. And viceversa.
  Double_t evalC1();     ///< Evaluates 1st direction cosine from (&theta;, &phi;)
  Double_t evalC2();     ///< Evaluates 2nd direction cosine from (&theta;, &phi;)
  Double_t evalC3();     ///< Evaluates 3rd direction cosine from (&theta;, &phi;)
  Double_t evalTheta();  ///< Evaluates polar angle &theta; from direction cosines
  Double_t evalPhi();    ///< Evaluates azimutal angle &phi; from direction cosines
  
  // getter funtions
  Double_t theta() const {return fTheta;} ///< Returns fTheta
  Double_t   phi() const {return fPhi;}   ///< Returns fPhi
  Double_t   eta() const {return fEta;}   ///< Returns fEta
  Double_t    c1() const {return fC1;}    ///< Returns fC1
  Double_t    c2() const {return fC2;}    ///< Returns fC2
  Double_t    c3() const {return fC3;}    ///< Returns fC3
  

 private:
  
  Double_t fEta;   ///< Pseudorapidity
  Double_t fTheta; ///< Polar angle &theta;
  Double_t fPhi;   ///< Azimutal angle &phi;
  Double_t fC1;    ///< 1st direction cosine
  Double_t fC2;    ///< 2nd direction cosine
  Double_t fC3;    ///< 3rd direction cosine

  
  ClassDef(Direction,1)
    };

#endif
