#include "Vertex.h"
#include "Rootils.h"
using namespace rootils;
#include "VertexResolution.h"
using namespace vres;
#include "Math.h"
#include "Riostream.h"


ClassImp(Vertex)

//default constructor
Vertex::Vertex(){

  fVertex.setX(rndmGaus(0., sXv));
  fVertex.setY(rndmGaus(0., sYv));
  fVertex.setZ(rndmGaus(0., sZv));

  genFixedMult();
}


//standard constructor
Vertex::Vertex(TString multOpt, UInt_t mult, Double_t zVert){
  
  fVertex.setX(rndmGaus(0., sXv));
  fVertex.setY(rndmGaus(0., sYv));
  fVertex.setZ(rndmGaus(zVert, sZv));
  fVertex.setsX(sXv);
  fVertex.setsY(sYv);
  fVertex.setsZ(sZv);
  
  if(multOpt == "fixed") genFixedMult(mult);
  else cout << "Invalid multiplicity option" << endl;
  
}


//standard constructor
Vertex::Vertex(TString multOpt, Double_t par1, Double_t par2, Double_t zVert){
  
  fVertex.setX(rndmGaus(0., sXv));
  fVertex.setY(rndmGaus(0., sYv));
  fVertex.setZ(rndmGaus(zVert, sZv));

  if(multOpt == "uniform") genUniformMult(par1, par2);
  else if(multOpt == "gaus") genGausMult(par1, par2);
  else cout << "Invalid multiplicity option" << endl;
  
}



//standard constructor
Vertex::Vertex(TString multOpt, TH1F* histMult, Double_t zVert)
{
  fVertex.setX(rndmGaus(0., sXv));
  fVertex.setY(rndmGaus(0., sYv));
  fVertex.setZ(rndmGaus(zVert, sZv));
  
  if(multOpt == "hist") genHistMult(histMult);
  else cout << "Invalid multiplicity option" << endl;
}


//destructor
Vertex::~Vertex(){}


//multiplicity generation
void Vertex::genUniformMult(Double_t minMult, Double_t maxMult){
  fMult = static_cast<UInt_t>(rootils::rndmUniform(minMult, maxMult));
}

void Vertex::genGausMult(Double_t mult, Double_t sMult){
  Int_t temp;
  do{temp = static_cast<Int_t>(rootils::rndmGaus(mult, sMult));}
  while(temp<0 || temp>100);  // multiplicity: lower limit = 0
                              //               upper limit = 100 (see also TClonesArray size in sim.C and reco.C)
  fMult = static_cast<UInt_t>(temp);
}

void Vertex::genFixedMult(UInt_t mult){
  fMult = mult;
}

void Vertex::genHistMult(TH1F* histMult){
  fMult = histMult -> GetRandom();
}
