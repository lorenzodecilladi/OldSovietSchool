#include "TFile.h"
#include <Riostream.h>

void provaStruct();
void leggiStruct();

void provaStruct(){

  TFile file("provaFile.root","RECREATE");

  struct VTX : TObject{
    Double_t X, Y, Z;
  };

  VTX* point = new VTX();

  point->X = 1.5;
  point->Y = 2.5;
  point->Z = 3.5;

  cout << point->X << "\t" << point->Y << "\t" << point->Z << endl;
  
  point->Write("point"); //object point
  //  file.Write();
  file.ls();
  VTX* copy = (VTX*)file.Get("point");
  cout << copy->X << "\t" << copy->Y << "\t" << copy->Z << endl;
  file.Close();
  
}


void leggiStruct(){

  struct VTX : TObject{
    Double_t X, Y,Z;
  };
  
  TFile file("provaFile.root");
  VTX *p = (VTX*)file.Get("point");

  cout << p->X << "\t" << p->Y << "\t" << p->Z << endl;
  
  file.Close();
}
