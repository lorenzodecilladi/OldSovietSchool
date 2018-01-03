#ifndef Vertex_h
#define Vertex_h

#include "Point.h"
#include "TString.h"


class Vertex : public Point {

  //serve accettanza su eta? se si includi Constans.h
 public:
  
  Vertex();
  Vertex(TString multOpt, UInt_t mult, Double_t zVert); //multOption: option for specifying the generation distribution for the muliplicity
  Vertex(TString multOpt, Double_t par1, Double_t par2, Double_t zVert);
  
  virtual ~Vertex();


  //multiplicity generation
  void genUniformMult(Double_t minMult = 0., Double_t maxMult = 50.);
  void genGausMult(Double_t mult = 20., Double_t sMult = 5.);
  void genFixedMult(UInt_t mult = 20);

  //get functions
  Point getPoint() const {return fVertex;}
  UInt_t getMult() const {return fMult;}
  


  
  
 private:

  Point fVertex;
  UInt_t fMult;

  
  ClassDef(Vertex, 1)
  
};

#endif
