#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TH1D.h>
#include <TFile.h>
#include <TCanvas.h>
#endif


void ioexample(const char *fimpName, const char *histName){
  ifstream in(fimpName);
  if(!in){
    cout<<"Il file "<<fimpName<<" non esiste "<<endl;
    return;
  }
  
  Double_t xmin=0.,xmax=0.;
  Double_t x;
  in>>x;
  xmin=xmax=x;
 
  while((in>>x)){
    if(x<xmin){
      xmin=x;
    }
    else if(x>xmax) {
      xmax=x;
    }
  }

  Double_t tolerance = (xmax-xmin)*0.01;  // 1% del range
  TH1D *hist = new TH1D("hist","Istogramma",100,xmin-tolerance,xmax+tolerance);
   
  in.clear();
  in.seekg(0,ios::beg);
    
  Int_t count = 0;
  while((in>>x)){
    count++;
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

