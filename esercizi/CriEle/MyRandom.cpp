#include <Riostream.h>
#include "MyRandom.h"
#include "TString.h"

ClassImp(MyRandom)

MyRandom::MyRandom():
  TRandom(),
  fNestrazioni(0),
  fParametroa(0.)
{}
  
MyRandom::MyRandom(Int_t nestrazioni, Double_t parametroa):
  TRandom(),
  fNestrazioni(nestrazioni),
  fParametroa(parametroa)
{}
  
MyRandom::MyRandom(const MyRandom &source):
  TRandom(source),
  fNestrazioni(source.fNestrazioni),
  fParametroa(source.fParametroa)
{}

MyRandom::~MyRandom()
{}

MyRandom& MyRandom::operator=(const MyRandom& source){
  if(this != &source){
    TRandom::operator=(source);
    fNestrazioni = source.fNestrazioni;
    fParametroa = source.fParametroa;
  }

  return *this;
}

MyRandom::SetEstrazioni(Int_t nestrazioni){
  fNestrazioni = nestrazioni;
}

Int_t MyRandom::GetEstrazioni(){
  return fNestrazioni;
}

MyRandom::SetA(Double_t parametroa){
  fParametroa = parametroa;
}

Double_t MyRandom::GetA(){
  return fParametroa;
}
