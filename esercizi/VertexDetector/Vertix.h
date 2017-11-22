#ifndef Vertix_h
#define Vertix_h

#include "TMath.h"

class Vertix{

  //serve che erediti da TObject ??
  //serve accettanza su eta? se si includi Constans.h
 public:
  
  Vertix();
  //Vertix(Double_t _phi, Double_t _eta);
  //Vertix(const Vertix& source); ci serve??

  virtual ~Vertix();

  
 private:
  
  ClassDef(Vertix, 1)
  
};

#endif
