#include "TDoctor.h"

ClassImp(TDoctor)

TDoctor::TDoctor():TLorentzVector(){
  fDottore = true;
  fVoto = 110;
  fLode = true;
  fLaurea = "Fisica";
  bool tesiFiga = true;
  if(tesiFiga){
    cout << "Lorenzo " << " è proclamato Dottore in " << fLaurea << " con punteggio " << fVoto;
    if(fVoto == 110 && fLode)
      cout << " e lode!!" << endl;
    else cout << endl; 
  }
}
/*
TDoctor::TDoctor(Bool_t tesiFiga, unsigned Int_t voto, Bool_t conLode):TLorentzVector(){
  fDottore = true;
  fVoto = voto;
  fLode = conLode;
  fLaurea = "Fisica";
  if(fDottore){
    cout << "Lorenzo " << " è proclamato Dottore in " << fLaurea << " con punteggio " << fVoto;
    if(fVoto == 110 && fLode)
      cout << " e lode!!" << endl;
    else cout << endl; 
  }
 }
*/
TDoctor::~TDoctor(){
}

void TDoctor::domandeDiscussione(){
  cout << "Fatti i c**** tuoi, stai zitto e ascolta" << endl;
}

void TDoctor::proclamazione(){
  fDottore = true; //ce l'hai fatta!!
  fVoto = 110;
  fLode = true;
  int a = messaggio(fDottore);
}

int TDoctor::messaggio(bool laureato){
  if(laureato) cout << "AUGURI DOTTOREEEEE!!!" << endl;
  else cout << "Ti voglio bene lo stesso" << endl;
  return 0;
}
