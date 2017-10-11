#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TH1D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <vector>
#endif

using std::vector;

void ioexample(const char *fimpName, const char *histName){
  ifstream in(fimpName);
  if(!in){
    cout<<"Il file "<<fimpName<<" non esiste "<<endl;
    return;
  }
  
  Double_t xmin=0.,xmax=0.;
  Double_t x;
  in>>x;    // si noti che si assume che ci sia almeno un dato nel file
  xmin=xmax=x;
  Int_t count = 1;
  vector <Double_t> v;
  v.push_back(x);
  Bool_t toomuch = kFALSE;
  const UInt_t limit = 10000;

  while((in>>x) && !toomuch){
    count++;
    v.push_back(x);

    if(x<xmin) xmin=x;
    if(x>xmax) xmax=x;

    if(v.size()>=limit){
      cout<<"warning: dimensione del vettore > "<<limit<<endl;
      toomuch = kTRUE;
    }
  }

  TH1D *hist;
  hist = new TH1D("hist","Istogramma",100,xmin-1,xmax+1);

  for(int i=0;i<count;i++){
    x=v[i];
    hist->Fill(x);
  }

  cout<<"Dati letti: "<<count<<endl;
  cout<<"Il dato piu' piccolo e': "<<xmin<<endl;
  cout<<"Il dato piu' grande e': "<<xmax<<endl;

  in.close();
  hist->Draw();
  TFile file(histName,"recreate");
  hist->Write();
  file.Close();
}

