#ifndef MYRANDOM3_H
#define MYRANDOM3_H


#include "TRandom3.h"

class MyRandom3 : public TRandom3 {
////////////////////////////////////////////////////////////////////////
// Class used to generate random numbers.
// New function(s) to be sampled are added w.r.t. TRandom3
// Origin: M.Masera 17/10/2002
// Last mod. 16/10/2017
////////////////////////////////////////////////////////////////////////
 public:
  //
  MyRandom3();
  MyRandom3(double alpha, UInt_t seed=65539);
  virtual ~MyRandom3();
  // Funct1(theta,alpha) returns the value of f(x,a)=1/(sin(x)**2+a*cos(x)**2)
  double Funct1(double theta);
  // Funct2(double x) returns (sin(x)/x)^2
    static double Funct2(double x);

  // returns a random number distributed according to Funct1
  // with the inversion method
  double Funct1RndmByInversion();

  // returns a random number distributed according to Funct1
  // with the inversion method (another implementation)
  double Funct1RndmByInversion2();

  // returns a random number distributed according to Funct1
  // with the rejection method
  double Funct1RndmByRejection();
  double Funct1RndmByRejection2();
    
  // returns a random number distributed according to Funct2
  // with the importance sampling method
  double RndmFunct2(double xmin, double xmax,const double v1, const double v2, const double x2, const double x3);

  // returns theta and phi according to an isotropic distribution
  void SphereIso(double & th, double & phi);
 // returns theta and phi according to an isotropic distribution (but
 // with memory allocation !!!
  double* SphereIso();
  void SphereIso(double dire[]);
  //
 private:
  // private methods
  void Init();  // set alpha parameter
    
  // data members
  double fAlpha;      //! parameter of the function
  double fPi;         //! PI
  double fBig;        //! used by rejection method
  Double_t fSqrtAlpha;  //! sqrt(fAlpha)

  ClassDef(MyRandom3,1) 
};



#endif
