#include <Riostream.h>
#include "MyClass.h"
#include "TString.h"

ClassImp(MyClass) //istruzione x Root: serve x creare streamer, dizionari... la devo mettere x integrare classe in Root


//DEFAULT CONSTRUCTOR

MyClass::MyClass(): //:: scope operator; 
TObject(), //poi invoco il costruttore di TObject perchè eredita da esso
  fHeight(0.), //valori iniziali di tutti i data member
  fWeight(0.),
  fAge(0),
  fMale(kFALSE),
  fSize(0),
  fInfo(NULL){
  //default constructor
  //ora eventuali altre istruzioni (qui stampa a scopi didattici)
  cout << "Default Constructor - this: " << this << endl; //this: ptatore che c'è sempre e pta a questo oggetto (quello che sto creando invocando il costruttore)
}


//STANDARD CONSTRUCTOR

MyClass::MyClass(Double_t s, Double_t p, Int_t e, Bool_t sex)://costruttore standard: modo per dare io valori iniziali di tutti i data member
  TObject(),
  fHeight(s), 
  fWeight(p),
  fAge(e),
  fMale(sex),
  fSize(0),
  fInfo(NULL){
  
  cout << "Standard Constructor - this: " << this << endl; //this: ptatore che c'è sempre e pta a questo oggetto (quello che sto creando invocando il costruttore)
}

MyClass::MyClass(const MyClass &source): //const: non decve alterare source
  TObject(source),
  fHeight(source.fHeight), //posso accedere ad un data member privato perchè sono nell? IMPLEMENTATION file
  fWeight(source.fWeight),
  fAge(source.fAge),
  fMale(source.fMale),
  fSize(source.fSize){
  cout << "COPY CONSTRUCTOR - source = " << &source<< "destinazione: " << this <<endl; //&-> qui sta per address code
  //fInfo: non posso inizializzarlo con gli altri
  if(fSize>0){
    fInfo=new Int_t[fSize];
    for(Int_t i=0; i<fSize; i++) fInfo[i] = source.fInfo[i]; //così non creo una shallow copy!! se non ci fosse questo data memebr potevo non creare questa classe e usare il copyconstr di default
  }
  else fInfo = NULL;
}


//DISTRUTTORE

MyClass::~MyClass(){
  cout << "Destructor - this = " << this << endl;
  if(fSize>0) delete []fInfo; //evito memory leak
}


//ASSIGNMENT OPERATOR

MyClass& MyClass::operator=(const MyClass& source){
  cout<<"ASSIGNMENT OPERATOR "<< this << endl;
  if(this != &source){ //verifico indirizzo source diverso ptatore di questo oggetto di destinaZIONE; evito copia di un oggetto su se stesso
    if(fSize>0) delete []fInfo; //clean up allocated memory
    TObject::operator=(source);//deoveguagliare data member; uso scope operator, decve usare l = del genitore
    fHeight = source.fHeight;
    fWeight = source.fWeight;
    fAge = source.fAge;
    fMale = source.fMale;
    fSize = source.fSize;
    //...
    if(fSize>0){
      fInfo = new Int_t[fSize];
      for(Int_t i=0; i<fSize; i++) fInfo[i] = source.fInfo[i];
    }
    else fInfo = NULL;
  } 
  return *this; //qui * dereferenziazione => *this è un oggetto
}
/*

//quando ho decine data member non posso usare questo =operator!! tropppo lungo, già il distruttore è lungo
//codice ripetuto è il male della programmazione

//=> MODO ALTERNATIVO

//ASSIGNMENT OPERATOR 2

MyClass& MyClass::operator=(const MyClass& source){
  if(this == &source) return *this;
  cout<<"ASSIGNMENT OPERATOR " << this << endl;
  this -> ~MyClass(); //si suicida, invoca distruttore su se stesso, dealloca memoria a lui riservata
  //il ptatore this rimane, muore solo la memoria (oggetto) a cui pta
  new(this) MyClass(source); //crea nuovo oggetto su memoria già allocata e puntata da this (RIPOPOLA, RICICLA)
  //NON DEVO RISCIVERE CODICE, USO COPYCONSTRUCTOR
  // invece MyClass *ptr = new MyClass(source) //alloca NUOVA memoria sdella size of MyClass, e lì costruisci (popola memoria)un nuovo  oggetto e quindi il ptatore this 
  cout<<"ASSIGNMENT OPERATOR 2 " << this << endl;
  return *this;
}
*/

//HEIGHT GETTER

Double_t MyClass::GetHeight() const {
  return fHeight;
}


//WEIGHT GETTER

Double_t MyClass::GetWeight() const {
  return fWeight;
}


//STATUS PRINTER
void MyClass::PrintStatus() const{

  TString sex = "F";
  if(IsMale()) sex = "M"; //anche this->IsMale() nell'if va bene
  cout << "Età: " << fAge << ";\t Statura: " << fHeight << ";\tPeso: " << fWeight << ";\t Sesso (M/F): " << sex.Data() << "." <<  endl; //sex.Data() function di TString
  cout << "Dimensione vettore con info aggiuntive: " << fSize << endl;
  if(fSize>0){
    for(Int_t i=1; i <=fSize; i++){
      cout << fInfo[i-1] << " ";
      if(i%3 == 0) cout << endl;
    }
    cout << "\n" << endl;
  }
}


//ARRAY SETTER

void MyClass::SetArray(Int_t *vt, Int_t sz){ //popola fInfo
  if(fSize>0) delete []fInfo; //clean up; se  non lo faccio creo memory leak
  fInfo = new Int_t[sz];
  fSize=sz;
  for(Int_t i=0; i<fSize; i++) fInfo[i] = vt[i];
}
  
