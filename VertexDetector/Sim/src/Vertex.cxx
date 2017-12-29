#include "Vertex.h" //VertexDetector/Sim/include
#include "Rootils.h" //VertexDetector/Utils
using namespace rootils;
#include "VertexResolution.h" //VertexDetector/Geometry
using namespace vres;
#include "Math.h" //VertexDetector/Utils
#include "Riostream.h"


ClassImp(Vertex)

//default constructor
Vertex::Vertex(){

  fVertex.setX(rndmGaus(0., sXv));
  fVertex.setY(rndmGaus(0., sYv));
  fVertex.setZ(rndmGaus(0., sZv));

  genFixedMult();
}


//standard constructor (TString, UInt_t)
Vertex::Vertex(TString multOpt, UInt_t mult){
  
  fVertex.setX(rndmGaus(0., sXv));
  fVertex.setY(rndmGaus(0., sYv));
  fVertex.setZ(rndmGaus(0., sZv));
  fVertex.setsX(sXv);
  fVertex.setsY(sYv);
  fVertex.setsZ(sZv);
  
  if(multOpt == "fixed") genFixedMult(mult);
  else cout << "Invalid multiplicity option" << endl;
  
}


//standard constructor (TString, Double_t, Double_t)
Vertex::Vertex(TString multOpt, Double_t par1, Double_t par2){
  
  fVertex.setX(rndmGaus(0., sXv));
  fVertex.setY(rndmGaus(0., sYv));
  fVertex.setZ(rndmGaus(0., sZv));

  if(multOpt == "uniform") genUniformMult(par1, par2);
  else if(multOpt == "gaus") genGausMult(par1, par2);
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
  while(temp<0);
  fMult = static_cast<UInt_t>(temp);
}

void Vertex::genFixedMult(UInt_t mult){
  fMult = mult;
}
