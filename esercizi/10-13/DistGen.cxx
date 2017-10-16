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
DistGen::DistGen(double alpha, double xmin, double xmax, unsigned int seed):
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

//INVERSE of CUMULATIVE FUNCTION for f(x)
double DistGen::invCumFunc(double xx){
  double alpha = fParam;

  return TMath::ATan( TMath::Sqrt(alpha)*TMath::Tan(TMath::Pi()*xx - 0.5) );
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

  //risurltato in [-pi/2, pi/2]
  double x = invCumFunc(u);
  
  //traspongo in [0, 2pi]
  double w = gRandom -> Rndm(fSeed);
  if     (w<0.5)        x = x + TMath::Pi(); //II e III quadrante
  else if(w>0.5 && x<0) x = x + 2*TMath::Pi(); // IV quadrante
  else if(w>0.5 && x>0) x = x; //I quadrante (riga superflua)
  
  return x;
}

