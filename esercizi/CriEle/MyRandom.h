#ifndef MYRANDOM_H
#define MYRANDOM_H

#include "TObject.h"
#include "TRandom3.h"

Class MyRandom : public TRandom3{
  //
 public:

  MyRandom(); //! costruttore vuoto
  MyRandom(Int_t nestrazioni, Double_t parametroa); //! costruttore standard
  MyRandom( const MyRandom& source); //! copyconstructor
  virtual ~MyRandom(); //! distruttore

  MyRandom& operator=(const MyRandom& source); //! operatore =

  SetEstrazioni(Int_t nestrazioni);
  Int_t GetEstrazioni() const;
  SetA(Double_t parametroa);
  Double_t GetA() const;
 




 private:

  Int_t fNestrazioni;
  Double_t fParametroa;
  
  ClassDef(MyRandom,1)
};

#endif
