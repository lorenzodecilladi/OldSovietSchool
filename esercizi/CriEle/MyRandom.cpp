#include <Riostream.h>
#include "MyRandom.h"
#include "TString.h"

ClassImp(MyRandom)

MyRandom::MyRandom():
  TRandom(),
  fMaggiorante(0.),
  fParametroa(0.),
  fPi(0.),
  fRadiceParametro(0.)
{}

MyRandom::MyRandom(Double_t parametroa):
  TRandom(),
  fMaggiorante(0.),
  fParametroa(parametroa),
  fPi(0.),
  fRadiceParametro(0.)
{
  SetName("MyRandom");
  SetTitle("Random number generator: Mersenne Twister");

  Inizializzazione();
}

MyRandom::Inizializzazione():
{
  fPi = TMath::Pi();
  if(fParametroa <= 0. || fParametroa > 1.){
    Warning("Inizializzazione","Parametro a non valido = %f8.3 \n",fParametroa);
    Warning("Init","Bisognerebbe inizializzarlo appropriatamente\n");
    fParametroa = 0.;
    fMaggiorante = 0.;
    fRadiceParametro = 0.;
  }
  else {
    fMaggiorante = 1/fParametroa;
    fRadiceParametro = TMath::Sqrt(fParametroa);
  }
}
  
MyRandom::MyRandom(const MyRandom &source):
  TRandom(source),
  fMaggiorante(source.fMaggiorante),
  fParametroa(source.fParametroa),
  fPi(source.fPi),
  fRadiceParametro(source.fRadiceParametro)
{}

MyRandom::~MyRandom()
{}

MyRandom& MyRandom::operator=(const MyRandom& source){
  if(this != &source){
    TRandom::operator=(source);
    fMaggiorante = source.fMaggiorante;
    fParametroa = source.fParametroa;
    fPi = source.fPi;
    fRadiceParametro = source.fRadiceParametro;
  }

  return *this;
}

MyRandom::SetA(Double_t parametroa){
  fParametroa = parametroa;
}

Double_t MyRandom::GetA(){
  return fParametroa;
}

Double_t Funzione1(double teta)
{
  
}

Double_t Funzione2(double teta)
{}

Double_t F1Reiezione1()
{}

Double_t F1Reiezione2()
{}

Double_t F1Inversione1()
{}

Double_t F1Inversione2()
{}
