#include <Riostream.h>
#include "MyRandom.h"
#include "TString.h"
#include "TMath.h"

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
  double senquadro = TMath::Sin(teta) * TMath::Sin(teta);
  double cosquadro = TMath::Cos(teta) * TMath::Cos(teta);

  return 1/(senquadro + fParametroa*cosquadro);
}

Double_t Funzione2(double teta)
{
  double senquadro = TMath::Sin(teta) * TMath::Sin(teta);
  double tetaquadro = teta*teta;

  return senquadro/tetaquadro;
}

Double_t F1Reiezione1()
{
  double x, y;

  do{
    x = 2 * fPi * Rndm();
    y = Rndm() * fMaggiorante;
  }while(Funzione1(x) >= y);

  return x;
}

Double_t F1Reiezione2()
{
  double x = 2. * Rndm() * fPi;
  double y = Rndm() * fMaggiorante;
  
  if(Funct1(x) >= y)
    return x;
  else
    return F1Reiezione2();
}

Double_t F1Inversione()
{
  double u = Rndm();
  double teta = TMath::ATan(fRadiceParametro * TMath::Tan(fPi * u - fPi/2));

  double w = Rndm();
  if(w < 0.5){
    teta = teta + fPi;
  }
  else if(teta < 0){
    teta = teta + 2*fPi;
  }

  return teta;
}

