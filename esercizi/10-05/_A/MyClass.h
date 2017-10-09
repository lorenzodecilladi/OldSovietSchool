#ifndef MYCLASS_H //serve perchè quando includo myclass più volte, il compilatore compila questo codice una sola volta!! evita inclusioni multiple
#define MYCLASS_H

#include "TObject.h"


class MyClass : public TObject{ 

 public: //se è private, solo le memb funct di MyClass possono vederle (uso interno)
         //protected: possono accedere solo le classi figlie

  MyClass();
  MyClass(Double_t s, Double_t p, Int_t e, Bool_t sex);
  MyClass(const MyClass &source); //è il CopyConstructor: so che sto facendo una copia
  virtual ~MyClass(); //distruttore; funz vrtuale permette di usare ptatore generico della classe madre (evenualmente astratta) e usare la memb funct della classe figlia

  MyClass& operator=(const MyClass& source); //& prima di operator: non crea una copia, ma modifica la source

  void ChangeAge(Int_t age){fAge = age;} // cambia il data member
                                         //la implemento qui => è una inline function: il compilatore  cerca di compilarla qui
  Double_t GetHeight() const; //const: non altero il datamember; è un meccanismo di controllo/garanzia ed è più chiaro per l'utilizzatore
  Double_t GetWeight() const;
  Int_t    GetAge()    const {return fAge;}
  Bool_t   IsMale()    const {return fMale;}

  void      PrintStatus()     const;
  Int_t     GetArray(Int_t i) const {return (i>=0 && i<fSize) ? fInfo[i] : -1;}
  void      SetArray(Int_t *vt, Int_t sz);
  Double_t& altezza() {return fHeight;}
  //non ha senso avere setter e getter di tutti i data member, altrimenti tanto vale renderli pubblici!!
  
 private:
  
  Double_t fHeight; //convenzione di Root: data member f+Capital letter
  Double_t fWeight;
  Int_t    fAge;
  Bool_t   fMale;
  Int_t    fSize;
  Int_t *  fInfo; //[fSize] vettore con varie info. il complatore sa che ha dimensione fSize
                //alloca memoria
                

  ClassDef(MyClass, 1)//classe dentro il FRAMEWORK: istruzione che serve a root
                      // dice che questa classe è la prima versione (in versioni succ potrei aggiungere data member, se dichiaro la versione che uso sulle vecchie mi dà valore nullo su quel d.m.)
                      //nessuno stream; classe transiente, non consistente => metti 0
}; //unico caso in cui ; è richiesto dopo chiusura di una graffa

#endif
