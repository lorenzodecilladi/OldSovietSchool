#ifndef TDOCTOR_H
#define TDOCTOR_H

#include <iostream>
#include "TString.h"
#include "TLorentzVector.h"

class TDoctor : public TLorentzVector{
  
 public:
  
  TDoctor();
  //TDoctor(Bool_t tesiFiga = true, unsigned Int_t voto = 110, Bool_t conLode = true);
  virtual ~TDoctor();
  
  void domandeDiscussione();
  
  void proclamazione();
  
  int messaggio(bool laureato);
  
 private:

  bool fDottore;
  unsigned int fVoto;
  bool fLode;
  string fLaurea;
  
   ClassDef(TDoctor, 1)
    
    };

#endif
