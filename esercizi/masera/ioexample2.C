#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TH1D.h>
#include <TFile.h>
#include <TCanvas.h>
#endif

void ioexample(const char *fimpName, const char *histName){
  // legge dati2.dat
  ifstream in(fimpName);
  if(!in){
    cout<<"Il file "<<fimpName<<" non esiste "<<endl;
    return;
  }
  TH1D *hist = new TH1D("hist","Istogramma",100,-7.,7.);
  int count = 0;
  double x;
  while((in>>x)){
    count++;
    hist->Fill(x);
  }
  cout<<"Dati letti: "<<count<<endl;
  in.close();
  hist->Draw();
  TFile file(histName,"recreate");
  hist->Write();
  file.Close();
}

// la funzione che segue e' una variante della precedente
// da notare l'uso di TH1::DrawCopy e di TFile::Write

void ioexbis(const char *fimpName, const char *histName){
  // legge dati2.dat
  ifstream in(fimpName);
  if(!in){
    cout<<"Il file "<<fimpName<<" non esiste "<<endl;
    return;
  }
  TFile file(histName,"recreate");
  TH1D hist("hist","Istogramma",100,-7.,7.);
  int count = 0;
  double x;
  while((in>>x)){
    count++;
    hist.Fill(x);
  }
  cout<<"Dati letti: "<<count<<endl;
  in.close();
  hist.DrawCopy();
  file.Write();
  file.Close();
}

