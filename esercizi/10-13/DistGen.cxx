#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
//#include <TRandom3.h>

#include "DistGen.h"


ClassImp(DistGen)


//DEFAULT CONSTRUCTOR
DistGen::DistGen():
TRandom3()
{
  fParam = 0.5;
  fXmin = 0.;
  fXmax = 2*TMath::Pi();
  fSeed = 65349;
}

//STANDARD CONSTRUCTOR
DistGen::DistGen(double alpha, double xmin=0., double xmax=2*TMath::Pi(), double seed=65349):
  TRandom3()
{
  fParam = alpha;
  fXmin = xmin;
  fXmax = xmax;
  fSeed = seed;
}

//DESTRUCTOR
DistGen::~DistGen(){}


//ASSIGNMENT OPERATOR
DistGen& DistGen::operator=(const DistGen& source){
  if(this != &source){
    TRandom3::operator=(source);
    fParam = source.fParam;
    fXmin = source.fXmin;
    fXmax = source.fXmax;
    fSeed = source.fSeed;
  }
  return *this;
}


//FUNCTION f(x)
double DistGen::func(double xx){
  double theta = xx;
  double alpha = fParam; //posso accedere direttamente ai data member privati
                         //di DistGen perché ho specificato che la funzione
                         //è una member function della classe DistGen (DistGen::func)
  return 1/(TMath::Sin(theta)*TMath::Sin(theta) + alpha * TMath::Cos(theta)*TMath::Cos(theta));
}


//REJECTION TECHNIQUE
double DistGen::rejection(){
  //fXmin, fXmax
  
  double u1, u2, xT, yT;
  double yBig = fParam<1 ? 1/fParam : 1;
  
  do{
    u1 = gRandom->Rndm(fSeed);
    u2 = gRandom->Rndm(fSeed);
    //cout << u1 << " != " << u2 << endl;
    xT = fXmin+(fXmax-fXmin)*u1;
    yT = yBig*u2;
  }while(func(xT)<yT);
  
  return xT;
}


//INVERSION TECHNIQUE
double DistGen::inversion(){

  double u = gRandom->Rndm(fSeed);
  return 0.;
}
