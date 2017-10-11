#include <Riostream.h>
#include "MyClass.h"
#include "TString.h"

ClassImp(MyClass)
  ///////////////////////////////////////////////////////
  // 
  // This is a trivial example
  // 
  //
  ////////////////////////////////////////////////////////
//_________________________________________________________________
  MyClass::MyClass(): TObject(),
fHeight(0.),
fWeight(0.),
fAge(0),
fMale(kFALSE),
fSize(0),
fInfo(NULL)
{
  //Default constructor
  cout<<"Default Constructor - this: "<<this<<endl;
}

//_________________________________________________________________
  MyClass::MyClass(Double_t s, Double_t p, Int_t e, Bool_t sex): TObject(),
fHeight(s),
fWeight(p),
fAge(e),
fMale(sex),
fSize(0),
fInfo(NULL)
{
  //Standard constructor
  cout<<"Standard Constructor - this: "<<this<<endl;
}

//_________________________________________________________________
MyClass::MyClass(const MyClass &source):
  TObject(source),
  fHeight(source.fHeight),
  fWeight(source.fWeight),
  fAge(source.fAge),
  fMale(source.fMale),
  fSize(source.fSize)
{
  // copy constructor
  cout<<"COPY CONSTRUTOR - source = "<<&source<<" destinazione: "<<this<<endl;
  if(fSize>0){
      fInfo = new Int_t[fSize];
      for(Int_t i=0;i<fSize;i++)fInfo[i]=source.fInfo[i];
  }
  else {
    fInfo=NULL;
  }
}

//_________________________________________________________________
MyClass::~MyClass() {
  // Default destructor
  cout<<"Destructor - this = "<<this<<endl;
  if(fSize>0) delete []fInfo;
}
/*
//________________________________________________________
MyClass& MyClass::operator=(const MyClass& source)
{
  // Assignment operator
  cout<<"ASSIGNMENT OPERATOR "<<this<<endl;
  if(this != &source){
    // clean up allocated memory
    if(fSize>0)delete []fInfo;
    TObject::operator=(source);
    fHeight = source.fHeight;
    fWeight = source.fWeight;
    fAge = source.fAge;
    fMale = source.fMale;
    fSize = source.fSize;
    if(fSize>0){
      fInfo = new Int_t[fSize];
      for(Int_t i=0;i<fSize;i++)fInfo[i]=source.fInfo[i];
    }
    else {
      fInfo = NULL;
    }
  }
  return *this;
}
*/
//______________________________________________________________________
MyClass& MyClass::operator=(const MyClass& source){
  // Assignment operator
  if(this == &source) return *this;
  cout<<"ASSIGNMENT OPERATOR "<<this<<endl;
  this->~MyClass();
  new(this) MyClass(source);
  cout<<"ASSIGNMENT OPERATOR 2 "<<this<<endl;
  return *this;
}

//_________________________________________________________________
Double_t MyClass::GetHeight() const {
  // returns height
  return fHeight;
}

//_________________________________________________________________
Double_t MyClass::GetWeight() const {
  // returns Weight
  return fWeight;
}

//_________________________________________________________________
void MyClass::PrintStatus() const {
  // printout
  cout<<"\n Funzione PrintStatus di MyClass\n";
  cout<<"======================================================\n";
  TString sex = "F";
  if(this->IsMale())sex="M";
  cout<<"Eta'= "<<fAge<<", sesso = "<<sex.Data()<<", statura = "<<fHeight;
  cout<<", Peso= "<<fWeight<<endl;
  cout<<"Dimensione del vettore con informazioni aggiuntive "<<fSize<<endl;
  if(fSize>0){
    for(int i=1;i<=fSize;i++){
      cout<<fInfo[i-1]<<" ";
      if(i%3 == 0 )cout<<endl;
    }
    cout<<endl<<endl<<endl;
  }
}
//_________________________________________________________________
  void MyClass::SetArray(Int_t *vt, Int_t sz){
    // initialization of the array
    if(fSize>0)delete []fInfo; // clean memory
    fInfo = new Int_t[sz];
    fSize=sz;
    for(Int_t i=0;i<fSize;i++)fInfo[i]=vt[i];
}



