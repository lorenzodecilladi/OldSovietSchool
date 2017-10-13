#ifndef DISTGEN_H
#define DISTGEN_H

#include <TRandom3.h>
#include <TMath.h>

class DistGen : public TRandom3{

public:

DistGen();
DistGen(double alpha, double xmin=0., double xmax=2*TMath::Pi(), double seed=65349);
virtual ~DistGen();
DistGen& operator=(const DistGen& source); //& prima di operator: non crea una

double func(double xx);

double inversion();
double rejection();


private:

double fParam;
double fXmin;
double fXmax;
unsigned int fSeed;


};


#endif
