#ifndef MYCLASS_H
#define MYCLASS_H


#include "TObject.h"

class MyClass : public TObject {
////////////////////////////////////////////////////////////////////////
// Class just for example
////////////////////////////////////////////////////////////////////////
 public:
  //
  MyClass();
  MyClass(Double_t s, Double_t p, Int_t e, Bool_t sex);
  MyClass(const MyClass& source);
  virtual ~MyClass();

  MyClass& operator=(const MyClass& source);

  void ChangeAge(Int_t age){fAge = age;}
  Double_t GetHeight() const;
  Double_t GetWeight() const;
  Int_t GetAge() const {return fAge;} 
  Bool_t IsMale() const {return fMale;}
  void PrintStatus() const; 
  Int_t GetArray(Int_t i) const {return (i>=0 && i<fSize) ? fInfo[i] : -1;}
  void SetArray(Int_t *vt, Int_t sz);
  Double_t & altezza()  {return fHeight;}

  //
 private:
  //
  Double_t fHeight;      // statura
  Double_t fWeight;      // peso
  Int_t fAge;            // eta'
  Bool_t fMale;  // vero se maschio
  Int_t fSize; // dimensione del vettore fInfo
  Int_t *fInfo; //[fSize] vettore con varie informazioni numeriche

  ClassDef(MyClass,1) 
};


#endif
